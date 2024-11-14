#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "Animation.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    void paintEvent(QPaintEvent* event) override;
private:
    void updateGame();
private:
    std::chrono::steady_clock::time_point m_last_tick;

    Animation m_animation;
};
#endif // WIDGET_H
