#include "uipushbutton.h"

UiPushButton::UiPushButton(QWidget* parent): QPushButton(parent)
{

}

void UiPushButton::enterEvent(QEnterEvent *event)
{
    setCursor(Qt::PointingHandCursor);  // 帮助文档  Qt::PointingHandCursor是小手
}

void UiPushButton::leaveEvent(QEvent *event)
{
    setCursor(Qt::ArrowCursor);  // Qt::ArrowCursor是鼠标箭头
}
