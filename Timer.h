#ifndef TIMER_H
#define TIMER_H

#include <functional>

class Timer
{
public:
    Timer() = default;
    ~Timer() = default;

    void restart() { m_pass_time = 0; m_shotted = false; }

    void setWaitTime(float val) { m_wait_time = val; }

    void setOneShot(bool flag) { m_one_shot = flag; }

    void setOnTimeout(std::function<void()> on_timeout)
    { m_on_timeout = on_timeout; }

    void pause() { m_paused = true; }
    void resume(){ m_paused = false; }

    float getPassTime() const { return m_pass_time; }
    bool getShotted() const { return m_shotted; }
    void onUpdate(float delta)
    {
        if (m_paused) { return; }

        m_pass_time += delta;
        if (m_pass_time >= m_wait_time)
        {
            bool can_shot = (!m_one_shot || (m_one_shot && !m_shotted));
            m_shotted = true;
            if (can_shot && m_on_timeout) { m_on_timeout(); }
            m_pass_time -= m_wait_time;
        }
    }
private:
    float m_pass_time = 0;
    float m_wait_time = 0;
    bool m_paused = false;
    bool m_shotted = false;
    bool m_one_shot = false;
    std::function<void()> m_on_timeout;
};

#endif // TIMER_H
