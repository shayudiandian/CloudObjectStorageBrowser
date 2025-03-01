#ifndef LOGGERPROXY_H
#define LOGGERPROXY_H

#include "src/bend/dao/logs/basiclogger.h"
#include "src/config/globals.h"

// 日志代理类  单例
class LoggerProxy : public QObject
{
    Q_OBJECT
public:
    explicit LoggerProxy(QObject *parent = nullptr);
    ~LoggerProxy();

    const LoggerProxy& reset(const QString& file, int line, const QString& func);

    void total(const QVariant& var, bool up = false) const;
    void debug(const QVariant& var, bool up = false) const;
    void info(const QVariant& var, bool up = false) const;
    void warning(const QVariant& var, bool up = false) const;
    void error(const QVariant& var, bool up = true) const;
    void fatal(const QVariant& var, bool up = true) const;

    void setLevel(GLOBAL::LOG_LEVEL newLevel);
    void setLogger(BasicLogger *newLogger);

private:
    BasicLogger* m_logger = nullptr;
    GLOBAL::LOG_LEVEL m_level;

    QString m_file;
    int m_line;
    QString m_func;

    void doLog(GLOBAL::LOG_LEVEL level, const QVariant& var, bool up) const;

signals:
    void sigLog(const QString& file, int line, const QString& func, void* tid,
                int level, const QVariant& var, bool up) const;
};

#endif // LOGGERPROXY_H
