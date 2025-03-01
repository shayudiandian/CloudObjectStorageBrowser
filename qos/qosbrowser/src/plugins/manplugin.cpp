#include "manplugin.h"
#include "src/bend/dao/clouds/daocloudscos.h"
#include "src/bend/dao/clouds/daocloudsmock.h"
#include "src/bend/dao/configs/versioncmd.h"
#include "src/bend/dao/configs/versionjson.h"
#include "src/bend/dao/logs/loggerqdebug.h"
#include "src/config/globals.h"
#include "src/middle/manglobal.h"



ManPlugin::ManPlugin(QObject *parent)
    : QObject{parent}
{

}


ManPlugin::~ManPlugin()
{
    delete m_clouds;
    delete m_version;
}

DaoClouds *ManPlugin::clouds() const
{
    return m_clouds;
}

void ManPlugin::installPlugins(int argc, char *argv[])
{
    // 如果输入命令行，则命令行参数优先级最高，否则直接加载配置文件中的配置信息
    VersionCmd version(argc, argv);
    if (version.isValid()) {
        m_version = new VersionCmd(argc, argv);
    }
    else {
        m_version = new VersionJson(GLOBAL::VERSION::JSON_PATH);
    }
    m_version->setVersion();

    // 安装日志插件   mLogIns 相当于 MG->mLog  mLog 是 LoggerProxy类
    mLogIns->setLogger(new LoggerQDebug());

    // 安装云存储插件
    if (m_version->major() == GLOBAL::VERSION::MAJOR_BUSINESS) {           // 商业版
        m_clouds = new DaoCloudsCos();
    }
    else {
        m_clouds = new DaoCloudsMock(":/static/testing/custom.json");
    }
}
