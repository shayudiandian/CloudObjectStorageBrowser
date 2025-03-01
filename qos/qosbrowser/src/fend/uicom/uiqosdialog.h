#ifndef UIQOSDIALOG_H
#define UIQOSDIALOG_H

#include "uibasedialog.h"

namespace Ui {
class UiQosDialog;
}

class UiQosDialog : public UiBaseDialog   // 继承
{
    Q_OBJECT

public:
    explicit UiQosDialog(QWidget *parent = nullptr);
    ~UiQosDialog();

private:
    Ui::UiQosDialog *ui;
};

#endif // UIQOSDIALOG_H
