#include "widget.h"
#include <QPainter>

#include <QTimer>
#include "CharacterManager.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // m_animation.setLoop("true");
    // m_animation.setInterval(0.03f);
    // m_animation.setAnchorMode(Animation::AnchorMode::BottomCentered);
    // m_animation.addFrame(ResourcesManager::instance()->findAtlas("skadi_skill_2_loop_right"));

    // m_pet.setAnimation("skill_2_loop");
    // m_pet.setGravityEnabled(false);
    CharacterManager::instance()->getPet()->setAnimation("skill_2_loop");
    CharacterManager::instance()->getPet()->setGravityEnabled(false);

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

    // m_animation.onRender();
    // m_pet.onRender();
    CharacterManager::instance()->getPet()->onRender();

    painter.end();
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

    this->update();
    m_last_tick = frameStart;
}
