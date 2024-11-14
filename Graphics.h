#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QPainter>

class Graphics
{
public:
    static Graphics* instance()
    {
        static Graphics graphics;
        return &graphics;
    }

    QPainter& getPainter()
    {
        return m_painter;
    }
private:
    Graphics() {}
    ~Graphics() {}
private:
    QPainter m_painter;
};

#endif // GRAPHICS_H
