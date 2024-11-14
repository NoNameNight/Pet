#ifndef ANIMATION_H
#define ANIMATION_H

#include "Util.h"
#include "Timer.h"
#include "Atlas.h"
#include "Vector2.h"
#include "Graphics.h"

#include <vector>
#include <functional>

class Animation
{
public:
    enum class AnchorMode
    {
        Centered,
        BottomCentered
    };
public:
    Animation()
    {
        m_timer.setOneShot(false);
        m_timer.setOnTimeout(
            [&]() {
                ++m_idx_frame;
                if (m_idx_frame >= m_frame_list.size())
                {
                    m_idx_frame = m_is_loop ? 0 : m_frame_list.size() - 1;
                    if (!m_is_loop && m_on_finished) { m_on_finished(); }
                }
            }
            );
    }
    ~Animation() = default;

    void reset()
    {
        m_timer.restart();
        m_idx_frame = 0;
    }

    void setAnchorMode(AnchorMode mode) { m_anchor_mode = mode; }

    void setPosition(const Vector2& position) { m_position = position; }

    void setLoop(bool is_loop) { m_is_loop = is_loop; }

    void setInterval(float interval) { m_timer.setWaitTime(interval); }

    void setOnFinished(std::function<void()> on_finished)
    {
        m_on_finished = on_finished;
    }

    void addFrame(IMAGE* image, int num_h)
    {
        int width = image->width();
        int height = image->height();
        int width_frame = width / num_h;

        for (int i = 0; i < num_h; ++i)
        {
            Rect rect_src;
            rect_src.x = i * width_frame, rect_src.y = 0;
            rect_src.w = width_frame, rect_src.h = height;

            m_frame_list.emplace_back(image, rect_src);
        }
    }

    void addFrame(Atlas* atlas)
    {
        for (int i = 0; i < atlas->getSize(); ++i)
        {
            IMAGE* image = atlas->getImage(i);
            int width = image->width();
            int height = image->height();

            Rect rect_src;
            rect_src.x = 0, rect_src.y = 0;
            rect_src.w = width, rect_src.h = height;

            m_frame_list.emplace_back(image, rect_src);
        }
    }

    void onUpdate(float delta)
    {
        m_timer.onUpdate(delta);
    }

    void onRender()
    {
        const Frame& frame = m_frame_list[m_idx_frame];

        Rect rect_dst = { 0 };
        rect_dst.x = 0, rect_dst.y = 0;
        rect_dst.w = frame.rect_src.w, rect_dst.h = frame.rect_src.h;

        QPainter& painter = Graphics::instance()->getPainter();
        painter.drawPixmap(rect_dst.x, rect_dst.y, rect_dst.w, rect_dst.h, *frame.image);
    }
private:
    struct Frame
    {
        Rect rect_src;
        IMAGE* image = nullptr;

        Frame() = default;
        Frame(IMAGE* image, const Rect& rect_src)
            : image(image), rect_src(rect_src)
        { }

        ~Frame() = default;
    };
private:
    Timer m_timer;
    Vector2 m_position;
    bool m_is_loop = true;
    size_t m_idx_frame = 0;
    std::vector<Frame> m_frame_list;
    std::function<void()> m_on_finished;
    AnchorMode m_anchor_mode = AnchorMode::Centered;
};

#endif // ANIMATION_H
