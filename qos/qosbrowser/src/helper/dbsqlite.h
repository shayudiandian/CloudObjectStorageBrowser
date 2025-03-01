#ifndef DBSQLITE_H
#define DBSQLITE_H

#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>

using RECORD = QMap<QString, QVariant>;

class DbSqlite
{
public:
    DbSqlite();
    ~DbSqlite();

    void connect(const QString& dbpath);
    QSqlQuery exec(const QString& sql);                // 执行sql语句
    QSqlQuery exec(const QString& sql, const QVariantList &variantList);
    bool exists(const QString& sql);
    QList<RECORD> select(const QString& sql);

private:
    QSqlDatabase m_db;
};

#endif // DBSQLITE_H
