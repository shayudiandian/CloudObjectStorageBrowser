#include "manglobal.h"
#include "src/bend/gateway.h"
#include "src/bend/man/mancloud.h"
#include "src/bend/man/mandb.h"
#include "src/middle/manmodels.h"
#include "src/middle/signals/mansignals.h"
#include "src/plugins/manplugin.h"

#include <QApplication>


Q_GLOBAL_STATIC(ManGlobal, ins)

ManGlobal::ManGlobal(QObject *parent)
    : QObject{parent}
{
    mLog = new LoggerProxy(this);
    mCloud = new ManCloud(this);
    mDb = new ManDB(this);
    mSignal = new ManSignals(this);
    mPlugin = new ManPlugin(this);
    mGate = new GateWay(this);
    // mModels = new ManModels(this);        放这里会崩溃，放 init 方法中
}

ManGlobal::~ManGlobal()
{

}

ManGlobal *ManGlobal::instance()
{
    return ins();
}

void ManGlobal::init(int argc, char *argv[])
{
    mModels = new ManModels(this);

    FileHelper::mkPath(GLOBAL::PATH::LOG_DIR);
    FileHelper::mkPath(GLOBAL::PATH::TMP);

    mPlugin->installPlugins(argc, argv);

    QString qssStr = FileHelper::readAllTxt(":/static/qss/default.qss");
    qApp->setStyleSheet(qssStr);    // 头文件 <QApplication> QApplication是单例，qApp指向它

    mDb->init();
}

