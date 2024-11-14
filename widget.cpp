#include "widget.h"
#include "ResourcesManager.h"
#include <QPainter>

#include <QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    try
    {
        ResourcesManager::instance()->load();
    }
    catch (const QString id)
    {
        char err_msg[512] = { 0 };
        sprintf_s(err_msg, ("无法加载: %s"), id.toStdString().c_str());
        qDebug() << err_msg;
        // return -1;
    }

    m_animation.setLoop("true");
    m_animation.setInterval(0.03f);
    m_animation.setAnchorMode(Animation::AnchorMode::BottomCentered);
    m_animation.addFrame(ResourcesManager::instance()->findAtlas("skadi_skill_2_loop_right"));

    // 设置帧率为60 FPS
    int fps = 60;
    // m_frame_duration = std::chrono::nanoseconds(1000000000 / fps);
    std::chrono::milliseconds frame_duration(1000 / fps);
    m_last_tick = std::chrono::steady_clock::now();
    // 开始游戏循环
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::updateGame);
    timer->start(frame_duration);  // approximately 60 FPS
}

Widget::~Widget() {}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter& painter = Graphics::instance()->getPainter();
    painter.begin(this);

    m_animation.onRender();

    painter.end();
}

void Widget::updateGame()
{
    using namespace std::chrono;

    // 取得当前时间
    steady_clock::time_point frameStart = steady_clock::now();
    duration<float> delta = duration<float>(frameStart - m_last_tick);

    m_animation.onUpdate(delta.count());

    this->update();
    m_last_tick = frameStart;
}
