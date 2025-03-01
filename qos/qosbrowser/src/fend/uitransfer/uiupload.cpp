#include "uiupload.h"
#include "src/config/common.h"
#include "src/fend/uidelegates/uitableitemdelegate.h"
#include "ui_uiupload.h"
#include "src/fend/uicom/uiprogresswidget.h"

#include <QFileInfo>


UiUpload::UiUpload(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UiUpload)
{
    ui->setupUi(this);
    initHeader();
    connect(MG->mSignal, &ManSignals::startUpload, this, &UiUpload::onStartUpload);
    connect(MG->mSignal, &ManSignals::uploadProcess, this, &UiUpload::onUploadProcess);
    connect(MG->mSignal, &ManSignals::uploadSuccess, this, &UiUpload::onUploadSuccess);
    connect(MG->mSignal, &ManSignals::error, this, &UiUpload::onError);

    ui->tableWidget->setItemDelegate(new UiTableItemDelegate(ui->tableWidget));
}

UiUpload::~UiUpload()
{
    delete ui;
}

void UiUpload::onStartUpload(const QString &jobId, const QString &key, const QString &localPath)
{
    ui->tableWidget->insertRow(0);
    ui->tableWidget->setRowHeight(0, 40);
    QTableWidgetItem* item = new QTableWidgetItem(key);
    item->setData(Qt::UserRole, jobId);
    // 第一列 文件名，key   第二列  本地路径
    ui->tableWidget->setItem(0, 0, item);
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(localPath));

    QFileInfo info(localPath);
    UiProgressWidget *bar = new UiProgressWidget();
    bar->setRange(0, info.size());  // 调用 UiProgressWidget 的 setRange 方法
    ui->tableWidget->setCellWidget(0, 2, bar);
}

void UiUpload::onUploadProcess(const QString &jobId, qulonglong transferedSize, qulonglong totalSize)
{
    UiProgressWidget* w = findTableWidgetItem(jobId);
    // 设置已传输的字节数，更新进度
    w->setValue(transferedSize);
}

void UiUpload::onUploadSuccess(const QString &jobId)
{
    UiProgressWidget* w = findTableWidgetItem(jobId);
    w->setFinished(QString("上传成功"));       // 调用 UiProgressWidget 的 setFinished 方法
}

void UiUpload::onError(int api, const QString &msg, const QJsonValue &req)
{
    if (api != API::OBJECTS::PUT)
        return;
    UiProgressWidget* w = findTableWidgetItem(req["jobId"].toString());
    w->setError(QString("上传失败"));
    w->setToolTip(msg);
}

UiProgressWidget* UiUpload::findTableWidgetItem(const QString &jobId)
{
    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        QTableWidgetItem* item = ui->tableWidget->item(i, 0);
        QString itemId = item->data(Qt::UserRole).toString();
        if (itemId == jobId)
        {
            return dynamic_cast<UiProgressWidget*>(ui->tableWidget->cellWidget(i, 2));
        }
    }
    return nullptr;
}

void UiUpload::initHeader()
{
    QStringList headers;
    headers << QString("云端路径")
            << QString("本地路径")
            << QString("上传状态");
    ui->tableWidget->setColumnCount(headers.size());
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(1);
}
