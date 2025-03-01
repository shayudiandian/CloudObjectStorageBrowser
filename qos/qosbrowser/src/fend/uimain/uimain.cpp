#include "uimain.h"
#include "qpushbutton.h"
#include "ui_uimain.h"
#include "src/config/common.h"
#include <QMessageBox>
#include "src/fend/uicom/uimessagebox.h"
#include "src/fend/uitransfer/uitransfer.h"

UiMain::UiMain(QWidget *parent) :
    UiQosDialog(parent),
    ui(new Ui::UiMain)
{
    ui->setupUi(body());
    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 4);
    // 传输列表按钮
    QPushButton* transBtn = addButton(GLOBAL::PATH::TRANS, GLOBAL::PATH::TRANS_HOVER);  // uibasedialog 的方法
    connect(transBtn, &QPushButton::clicked, this, &UiMain::showTransfer);
    // 退出登录按钮
    QPushButton* quitBtn = addButton(GLOBAL::PATH::QUIT, GLOBAL::PATH::QUIT_HOVER);   // uibasedialog 的方法
    connect(quitBtn, &QPushButton::clicked, MG->mSignal, &ManSignals::unLogin);
    // 标题栏添加分割线（最小化最大化关闭与传输退出 按钮之间的 小竖线）
    addTitleLine();                    // uibasedialog 的方法
    // 最小化最大化按钮
    addMinButton(GLOBAL::PATH::MIN_PATH, GLOBAL::PATH::MIN_HOVER_PATH);
    addMaxButton(GLOBAL::PATH::MAX_PATH, GLOBAL::PATH::MAX_HOVER_PATH, GLOBAL::PATH::NORMAL_PATH, GLOBAL::PATH::NORMAL_HOVER_PATH);

    setTitle("Qos Browser");
    resize(1080, 640);
    setKeyDisabled();  // 禁用esc或回车，导致窗口关闭

    connect(MG->mSignal, &ManSignals::loginSuccess, this, &UiMain::show);
    connect(MG->mSignal, &ManSignals::unLogin, this, &UiMain::onUnLogin);
    connect(MG->mSignal, &ManSignals::bucketsSuccess, this, &UiMain::onBucketsSuccess);
    connect(MG->mSignal, &ManSignals::objectsSuccess, this, &UiMain::onObjectsSuccess);
    connect(MG->mSignal, &ManSignals::error, this, &UiMain::onError);

    m_transfer = new UiTransfer(this);
}

UiMain::~UiMain()
{
    delete ui;
}

void UiMain::onUnLogin()
{
    hide();
}

void UiMain::onBucketsSuccess(const QList<MyBucket> &buckets)
{
    ui->stackedWidget->setCurrentIndex(0);
}

void UiMain::onObjectsSuccess(const QList<MyObject> &objects)
{
    ui->stackedWidget->setCurrentIndex(1);
}

void UiMain::showTransfer()
{
    m_transfer->show();
}

void UiMain::onError(int api, const QString &msg, const QJsonValue &req)
{
    if (isVisible() && api > API::BUCKETS::BASE) {
        UiMessageBox().showMessage("错误", msg);
    }
}
