#ifndef UIBUCKETSTABLEWIDGET_H
#define UIBUCKETSTABLEWIDGET_H

#include <QWidget>
#include "src/middle/models/cloudmodels.h"

namespace Ui {
class UiBucketsTableWidget;
}

class UiBucketsTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UiBucketsTableWidget(QWidget *parent = nullptr);
    ~UiBucketsTableWidget();

private slots:
    // 双击桶表格详情界面时，若是第一列（桶名称），进入该桶的对象详情界面
    void on_tableView_doubleClicked(const QModelIndex &index);

    void onBucketsSuccess(const QList<MyBucket> &buckets);
    // 翻页
    void onPageNumChanged(int start, int maxLen);
    // 创建桶
    void on_btnCreateBucket_clicked();
    // 删除桶
    void onDelBucket();
    // 刷新（即重新显示桶列表）（例如我们在控制台创建，在客户端刷新）
    void on_btnRefresh_clicked();

private:
    Ui::UiBucketsTableWidget *ui;
};

#endif // UIBUCKETSTABLEWIDGET_H
