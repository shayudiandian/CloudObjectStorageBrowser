#ifndef UIOBJECTSTABLEWIDGET_H
#define UIOBJECTSTABLEWIDGET_H

#include "src/middle/models/cloudmodels.h"
#include <QWidget>

namespace Ui {
class UiObjectsTableWidget;
}

class UiObjectsTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UiObjectsTableWidget(QWidget *parent = nullptr);
    ~UiObjectsTableWidget();

private slots:
    // 返回至桶的界面
    void on_btnBuckets_clicked();
    // 双击文件夹才能进入
    void on_tableView_doubleClicked(const QModelIndex &index);
    // 获取对象列表成功
    void onObjectsSuccess(const QList<MyObject>& objects);
    // 面包屑 对象路径改变
    void onPathChanged(const QString& newPath);
    // 翻页
    void onPageNumChanged(int start, int maxLen);
    // 刷新
    void on_btnRefresh_clicked();
    // 上传
    void on_btnUpload_clicked();
    // 上传成功弹出提示信息
    void onUploadSuccess(const QString& jobId);
    // 下载
    void on_btnDownload_clicked();
    // 下载成功弹出提示信息
    void onDownloadSuccess(const QString& jobId);


    void showMessage(const QString& title, const QString& info);

private:
    Ui::UiObjectsTableWidget *ui;
};

#endif // UIOBJECTSTABLEWIDGET_H
