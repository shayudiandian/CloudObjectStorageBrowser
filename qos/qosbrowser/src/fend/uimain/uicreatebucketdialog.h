#ifndef UICREATEBUCKETDIALOG_H
#define UICREATEBUCKETDIALOG_H

#include <QWidget>
#include "src/fend/uicom/uiqosdialog.h"
#include "src/middle/models/cloudmodels.h"

namespace Ui {
class UiCreateBucketDialog;
}

class UiCreateBucketDialog : public UiQosDialog   // 继承 UiQosDialog （风格一致）
{
    Q_OBJECT

public:
    explicit UiCreateBucketDialog(QWidget *parent = nullptr);
    ~UiCreateBucketDialog();

    MyBucket getBucket();  // 获取需要创建的桶的有关信息（桶的名称和位置）

private:
    Ui::UiCreateBucketDialog *ui;
};

#endif // UICREATEBUCKETDIALOG_H
