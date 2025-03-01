#ifndef DAOLOGININFO_H
#define DAOLOGININFO_H

#include "src/middle/models/dbmodels.h"

class DaoLoginInfo           // 抽象类，方便继承
{
public:
    DaoLoginInfo();

    virtual bool exists(const QString& secretId) = 0;
    virtual void insert(const LoginInfo& info) = 0;
    virtual void update(const LoginInfo& info) = 0;
    virtual void remove(const QString& secretId) = 0;
    virtual QList<LoginInfo> select() = 0;


    virtual void connect() = 0;
    virtual void createTable() = 0;
};

#endif // DAOLOGININFO_H
