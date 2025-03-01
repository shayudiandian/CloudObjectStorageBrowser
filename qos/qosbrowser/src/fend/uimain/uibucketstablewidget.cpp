#include <QStandardItemModel>
#include <QJsonObject>
#include <QAction>
#include <QMessageBox>
#include "uibucketstablewidget.h"
#include "src/fend/uidelegates/uitableitemdelegate.h"
#include "ui_uibucketstablewidget.h"
#include "uicreatebucketdialog.h"
#include "src/config/common.h"

UiBucketsTableWidget::UiBucketsTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UiBucketsTableWidget)
{
    ui->setupUi(this);
    ui->tableView->setModel(MG->mModels->modelBuckets());
    // 设置列宽度
    ui->tableView->setColumnWidth(0, 200);
    ui->tableView->setColumnWidth(1, 120);
    ui->tableView->horizontalHeader()->setStretchLastSection(true); //设置最后一列占满整个表
    // 隐藏垂直标题
    ui->tableView->verticalHeader()->setHidden(true);
    // 设置鼠标点击排序
    ui->tableView->setSortingEnabled(true);
    // 初始化翻页按钮
    ui->widgetPage->setMaxRowList(QList<int>() << 10 << 50 << 100);


    connect(ui->widgetPage, &UiPageWidget::pageNumChanged, this, &UiBucketsTableWidget::onPageNumChanged);
    connect(MG->mSignal, &ManSignals::bucketsSuccess, this, &UiBucketsTableWidget::onBucketsSuccess);

    // 右键点击时，会显示一个包含删除选项的上下文菜单
    ui->tableView->setContextMenuPolicy(Qt::ActionsContextMenu);
    QAction* delAction = new QAction(QString("删除"), this);
    connect(delAction, &QAction::triggered, this, &UiBucketsTableWidget::onDelBucket);
    ui->tableView->addAction(delAction);

    ui->tableView->setItemDelegate(new UiTableItemDelegate(ui->tableView));
    ui->btnCreateBucket->setProperty("style_button", "main");
}

UiBucketsTableWidget::~UiBucketsTableWidget()
{
    delete ui;
}


void UiBucketsTableWidget::on_tableView_doubleClicked(const QModelIndex &index)
{
    if (index.column() == 0) {
        QJsonObject params;
        params["bucketName"] = index.data().toString() ;
        params["dir"] = "";
        MG->mGate->send(API::OBJECTS::LIST, params);
    }
}

void UiBucketsTableWidget::onBucketsSuccess(const QList<MyBucket> &buckets)
{
    ui->widgetPage->setTotalRow(buckets.size());
    QStandardItemModel *model = MG->mModels->modelBuckets();
    for (int i = 0; i < model->rowCount(); ++i) {
        ui->tableView->setRowHeight(i, 40);       // 每行高度
    }
}

void UiBucketsTableWidget::onPageNumChanged(int start, int maxLen)
{
    QStandardItemModel *model = MG->mModels->modelBuckets();
    for (int i = 0; i < model->rowCount(); ++i) {
        bool hidden = (i < start || i >= (start + maxLen));
        ui->tableView->setRowHidden(i, hidden);
    }
}

void UiBucketsTableWidget::on_btnCreateBucket_clicked()
{
    UiCreateBucketDialog dialog(this);    // 创建桶的对话框
    int ret = dialog.exec();
    if (ret == QDialog::Accepted) {
        MyBucket bucket = dialog.getBucket();  // 获取需要创建的桶的信息
        if (bucket.isValid()) {
            QJsonObject params;
            params["bucketName"] = bucket.name;
            params["location"] = bucket.location;
            MG->mGate->send(API::BUCKETS::PUT, params); // 点这个方法进去看，有刷新（创建桶之后更新页面）
        }
    }
}

void UiBucketsTableWidget::onDelBucket()
{
    QModelIndex idx = ui->tableView->currentIndex();
    if (idx.isValid()) {
        QString name = idx.data().toString();
        QMessageBox box(           // 删除桶跳出的对话框
            QMessageBox::Question,
            QString("删除桶"),
            QString("是否真的删除桶【%1】？").arg(name),
            QMessageBox::Yes|QMessageBox::No
        );
        // 原来yes，no按钮改为中文的删除，取消
        box.setButtonText(QMessageBox::Yes, QString("删除"));
        box.setButtonText(QMessageBox::No, QString("取消"));
        int ret = box.exec();
        if (ret == QMessageBox::Yes) {
            QJsonObject params;
            params["bucketName"] = name;
            MG->mGate->send(API::BUCKETS::DEL, params); // 点这个方法进去看，有刷新（删除桶之后更新页面）
        }
    }
}

void UiBucketsTableWidget::on_btnRefresh_clicked()
{
    MG->mGate->send(API::BUCKETS::LIST);
}

