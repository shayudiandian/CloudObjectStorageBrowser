#include "daologininfosqlite.h"
#include "src/config/globals.h"

DaoLoginInfoSqlite::DaoLoginInfoSqlite() {}

bool DaoLoginInfoSqlite::exists(const QString &secretId)
{
    QString sql = QString(
                      "SELECT id FROM %1 WHERE secret_id = '%2';")
                      .arg(GLOBAL::TABLES::LOGIN_INFO, secretId);
    return m_db.exists(sql);
}

void DaoLoginInfoSqlite::insert(const LoginInfo &info)
{
    QString sql = QString(
                      "INSERT INTO %1 (name, secret_id, secret_key, remark, timestamp) "
                      "VALUES (?, ?, ?, ?, ?);")
                      .arg(GLOBAL::TABLES::LOGIN_INFO);              // 表名不能用占位符
    QVariantList varList;
    varList << info.name
            << info.secret_id
            << info.secret_key
            << info.remark
            << info.timestamp;
    m_db.exec(sql, varList);
}

void DaoLoginInfoSqlite::update(const LoginInfo &info)
{
    QString sql = QString(
                      "UPDATE %1 SET "
                      "name = ?, "
                      "secret_key == ?, "
                      "remark = ?, "
                      "timestamp = ? "
                      "WHERE secret_id = ?;")
                      .arg(GLOBAL::TABLES::LOGIN_INFO);
    QVariantList varList;
    varList << info.name
            << info.secret_key
            << info.remark
            << info.timestamp
            << info.secret_id;
    m_db.exec(sql, varList);
}

void DaoLoginInfoSqlite::remove(const QString &secretId)
{
    QString sql = QString(
                      "DELETE FROM %1 WHERE secret_id = ?;")
                      .arg(GLOBAL::TABLES::LOGIN_INFO);
    QVariantList varList;
    varList << secretId;
    m_db.exec(sql, varList);
}

QList<LoginInfo> DaoLoginInfoSqlite::select()
{
    QString sql = QString(
                      "SELECT name, secret_id, secret_key, remark FROM %1 ORDER BY timestamp DESC;")
                      .arg(GLOBAL::TABLES::LOGIN_INFO);

    QList<LoginInfo> retList;
    QList<RECORD> recordList = m_db.select(sql);
    for (const auto& record: recordList)
    {
        LoginInfo info;

        info.name = record["name"].toString();
        info.secret_id = record["secret_id"].toString();
        info.secret_key = record["secret_key"].toString();
        info.remark = record["remark"].toString();

        retList.append(info);
    }
    return retList;
}


void DaoLoginInfoSqlite::connect()
{
    m_db.connect(GLOBAL::SQLite::NAME);
}

void DaoLoginInfoSqlite::createTable()
{
    QString sql = FileHelper::readAllTxt(GLOBAL::SQL::LOGIN_INFO_TABLE);
    m_db.exec(sql);
}
