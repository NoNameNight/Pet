#include "widget.h"
#include <QPainter>

#include <QTimer>
#include "CharacterManager.h"
#include "ResourcesManager.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::Tool);
    this->setContextMenuPolicy(Qt::DefaultContextMenu);

    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    Qt::WindowFlags m_flags = this->windowFlags();
    this->setWindowFlags(m_flags | Qt::WindowStaysOnTopHint);
    IMAGE *rtmp = ResourcesManager::instance()->findImage("pic");
    this->resize(rtmp->width(), rtmp->height());
    qDebug() << rtmp->width() << " " << rtmp->height();
    // this->resize(300, 241);

    // 设置帧率为60 FPS
    int fps = 60;
    std::chrono::milliseconds frame_duration(1000 / fps);
    m_last_tick = std::chrono::steady_clock::now();
    // 开始游戏循环
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::updateGame);
    timer->start(frame_duration);  // approximately 60 FPS
}

void Widget::setMenu(QMenu* menu)
{
    m_menu = menu;
}

Widget::~Widget() {}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter& painter = Graphics::instance()->getPainter();
    painter.begin(this);

    CharacterManager::instance()->getPet()->onRender();

    painter.end();
}

void Widget::mousePressEvent(QMouseEvent *ev)
{
    //代表鼠标左键按下
    if(ev->button() & Qt::LeftButton)
    {
        m_last_mouse_press_pos = ev->pos();
        m_last_mouse_press_time = std::chrono::steady_clock::now();
        m_is_mouse_press_move_first = true;
        // CharacterManager::instance()->getPet()->setGravityEnabled(false);
        // CharacterManager::instance()->getPet()->setVelocity(Vector2(0,0));
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *ev)
{
    using namespace std::chrono;
    if((ev->button() & Qt::LeftButton))
    {
        Character* pet = CharacterManager::instance()->getPet();
        steady_clock::time_point now_time = steady_clock::now();
        duration<float, std::milli> delta = duration<float, std::milli>(now_time - m_last_mouse_press_time);
        if(!m_is_mouse_press_move_first)
        {
            pet->switchState("relax");
        }
        else if(delta.count() < 200.f)
        {
            pet->switchState("interact");
        }
    }
    else if(ev->button() & Qt::RightButton)
    {
        // QMenu* menu;
    }
}

void Widget::mouseMoveEvent(QMouseEvent *ev)
{
    if(ev->buttons() & Qt::MouseButton::LeftButton)
    {
        Character* pet = CharacterManager::instance()->getPet();
        if(m_is_mouse_press_move_first)
        {
            pet->switchState("carry");
            m_is_mouse_press_move_first = false;
        }
        // w->move(e->globalPosition().toPoint()-m_pos);
        QPoint pos = ev->globalPosition().toPoint() - m_last_mouse_press_pos;
        Vector2 postion(pos.x() + this->size().width() / 2, pos.y() + this->size().height());
        pet->setPosition(postion);
    }
}

void Widget::updateGame()
{
    using namespace std::chrono;

    // 取得当前时间
    steady_clock::time_point frameStart = steady_clock::now();
    duration<float> delta = duration<float>(frameStart - m_last_tick);

    // m_animation.onUpdate(delta.count());
    // m_pet.onUpdate(delta.count());
    CharacterManager::instance()->getPet()->onUpdate(delta.count());

    Vector2 postion = CharacterManager::instance()->getPet()->getPosition();
    this->move(postion.x - this->size().width() / 2, postion.y - this->size().height());


    this->update();
    m_last_tick = frameStart;
}

void Widget::contextMenuEvent(QContextMenuEvent *event)
{
    if(m_menu != nullptr)
    {
        m_menu->exec(QCursor::pos());
    }
}
