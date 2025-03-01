#include "loggerqdebug.h"
#include "src/config/globals.h"
#include <QDateTime>
#include <iostream>

LoggerQDebug::LoggerQDebug(QObject *parent): BasicLogger(parent)
{
    qInstallMessageHandler(handle);      // 安装拦截器
}

LoggerQDebug::~LoggerQDebug() {}

void LoggerQDebug::print(const QString &file, int line, const QString &func, void* tid,
                         int level, const QVariant &var, bool up)
// 这里没有打印 函数名 和 线程id，因为太长了，后期可以加上去
{
    // 日志的前部分格式，如   2024-05-25T15:57:26[INFO] qosbrowser\main.cpp:21 -
    QDateTime dt;
    QString dtStr = dt.currentDateTime().toString(Qt::ISODate);
    QString front = QString("%1[%2] %3:%4 -").arg(dtStr, GLOBAL::LOG_NAMES[level], file).arg(line);
    front = front.replace("..\\", "");       // 将前面的 ..\ 删除
    // qDebug() << var 若 var 实际是 QString 类型，会打印 QVariant(QString, "hello")
    //                 若 var 实际是 int 类型，会打印 QVariant(int, 42)
    qDebug() << front.toLocal8Bit().data() << var;  // 使用qDebug而不是直接存文件，是为了打印 QVariant 类型
}

void LoggerQDebug::handle(QtMsgType type, const QMessageLogContext& context , const QString& msg)
{
    QFile file(BasicLogger::filePath());

    QString message = msg;

    QString key("QVariant(");
    message.replace(msg.indexOf(key), key.size(), "").chop(1);   // 把打印信息中的 QVariant() 去除，chop是去掉右边的)

    if (file.open(QIODevice::WriteOnly|QIODevice::Append))
    {
        // 输入到文件流中
        QTextStream stream(&file);
        stream << message << Qt::endl;
        file.close();
    }
    // 用于控制台输出
    std::cout << message.toLocal8Bit().data() << std::endl;
}
