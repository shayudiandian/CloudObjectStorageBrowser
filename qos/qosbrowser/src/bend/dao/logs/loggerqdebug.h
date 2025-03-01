#ifndef LOGGERQDEBUG_H
#define LOGGERQDEBUG_H

#include "basiclogger.h"

class LoggerQDebug : public BasicLogger
{
    Q_OBJECT
public:
    explicit LoggerQDebug(QObject *parent = nullptr);
    ~LoggerQDebug();

protected:
    virtual void print(const QString& file, int line, const QString& func, void* tid,
                       int level, const QVariant& var, bool up);

private:
    // qDebug 拦截器，通常qDebug是打印到控制台的，而我们需要打印到日志文件中
    static void handle(QtMsgType type, const QMessageLogContext &contex, const QString &msg);
    QThread* m_td = nullptr;
};

#endif // LOGGERQDEBUG_H
