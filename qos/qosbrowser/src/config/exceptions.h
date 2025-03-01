#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <QMap>
#include <QString>


typedef QMap<QString, QString> ErrorMap;

class BaseException {
public:
    BaseException(const QString& code, const QString& msg);

    static ErrorMap parseErrorCode(const QString& csvPath);     // 解析，static只执行一次
    static void generateErrorCodeHFile(const QString& csvPath, const QString &targetPath);  // 错误码生成-errorcode.h

    QString msg() const;
    QString code() const;

private:
    QString m_code;
    QString m_msg;
};

#endif // EXCEPTIONS_H
