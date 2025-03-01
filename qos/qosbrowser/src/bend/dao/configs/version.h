#ifndef VERSION_H
#define VERSION_H
#include <QString>
#include <QJsonObject>

class Version
{
public:
    Version();
    virtual void setVersion() = 0;

    QString version();
    QString versionNum();
    QString major() const;

protected:
    QString m_major;   // business-商用版 custom-个人版
    QString m_env;     // dev alpha beta prod  （内测、公测、...）

    int m_v1;          // 1.2.6 等等数字版本号
    int m_v2;
    int m_v3;
};

#endif // VERSION_H

