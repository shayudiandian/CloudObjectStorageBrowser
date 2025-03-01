#include "uiqosdialog.h"
#include "src/config/globals.h"
#include "ui_uiqosdialog.h"
#include "ui_uibasedialog.h"

UiQosDialog::UiQosDialog(QWidget *parent) :
    UiBaseDialog(parent),
    ui(new Ui::UiQosDialog)
{
    ui->setupUi(body());  // UiBaseDialog 的 body 方法返回 QWidget*
    setLogo(GLOBAL::PATH::LOGO_PATH);   // 这里为什么用 GLOBAL，而 UiBaseDialog 用的样式表（写死的），各自定位不同，UiBaseDialog 不止针对 qos 项目，不可使用框架中的
    setTitle("Qos");
    m_ui->labelLogo->setFixedSize(32, 24);
    m_ui->labelTitle->setProperty("style_font", "h4");
    resize(400, 50);
}

UiQosDialog::~UiQosDialog()
{
    delete ui;
}
