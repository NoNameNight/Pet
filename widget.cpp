#include "widget.h"
#include "ResourcesManager.h"
#include <QPainter>

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
}

Widget::~Widget() {}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    IMAGE* img = ResourcesManager::instance()->findImage("pic");
    painter.drawPixmap(0, 0, *img);
}
