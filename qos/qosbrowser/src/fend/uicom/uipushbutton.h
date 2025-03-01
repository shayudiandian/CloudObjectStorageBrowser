#ifndef UIPUSHBUTTON_H
#define UIPUSHBUTTON_H

#include <QPushButton>

class UiPushButton : public QPushButton  // 继承于 QPushButton
{
    Q_OBJECT
public:
    UiPushButton(QWidget* parent=nullptr);

protected:
    virtual void enterEvent(QEnterEvent *event);       // Qt6 必须 QEnterEvent，不能 QEvent
    virtual void leaveEvent(QEvent *event);
};

#endif // UIPUSHBUTTON_H
