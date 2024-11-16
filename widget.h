#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QMenu>

// #include "Animation.h"
// #include "Pet.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    void setMenu(QMenu* menu);
    ~Widget();
protected:
    void paintEvent(QPaintEvent* event) override;

    void mousePressEvent(QMouseEvent* ev) override;
    void mouseReleaseEvent(QMouseEvent* ev) override;
    void mouseMoveEvent(QMouseEvent* ev) override;

    void contextMenuEvent(QContextMenuEvent *event) override;
private:
    void updateGame();
private:
    QMenu* m_menu;

    std::chrono::steady_clock::time_point m_last_tick;
    bool m_is_mouse_press_move_first = true;
    QPoint m_last_mouse_press_pos = {0, 0};
    std::chrono::steady_clock::time_point m_last_mouse_press_time;
};
#endif // WIDGET_H
