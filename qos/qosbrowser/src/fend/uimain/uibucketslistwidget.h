#ifndef UIBUCKETSLISTWIDGET_H
#define UIBUCKETSLISTWIDGET_H

#include "src/middle/models/cloudmodels.h"
#include <QWidget>

namespace Ui {
class UiBucketsListWidget;
}

class UiBucketsListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UiBucketsListWidget(QWidget *parent = nullptr);
    ~UiBucketsListWidget();

private slots:
    void onBucketsSuccess(const QList<MyBucket>& buckets);
    // 双击桶列表里的一个桶
    void on_listView_doubleClicked(const QModelIndex& index);
    // 搜索框搜索一个桶，选择它时，显示这个桶里的对象详情表格界面
    void showBucketObjects(const QString& bucketName);
    // 搜索框点击时，出现好多桶，在输入框逐渐输入时，筛选桶
    void onTextEdited(const QString& text);

private:
    Ui::UiBucketsListWidget *ui;

};

#endif // UIBUCKETSLISTWIDGET_H
