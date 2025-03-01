#ifndef TESTCOS_H
#define TESTCOS_H

#include "src/bend/dao/clouds/daocloudscos.h"
#include <QtTest>

class TestCos : public QObject
{
    Q_OBJECT

public:
    TestCos();
    ~TestCos();

private slots:
// 调用所有测试用例之前，会先调用一次该函数 initTestCase()
    void initTestCase();
// 调用所有测试用例之后，会先调用一次该函数 cleanupTestCase()
    void cleanupTestCase();
    void test_buckets();

    void test_isBucketExists();
    void test_getBucketLocation();

    void test_putBucket();
    void test_deleteBucket();

    void test_getObjects();
    void test_getObjects2_data();
    void test_getObjects2();

    void test_getObjectError();

    void test_putObject();
    void test_getObject();

private:
    DaoCloudsCos m_cos;

    // QString 创建自己的 m_secretId
    // QString 创建自己的 m_secretKey

    QString m_bucketName = "file-1317524568";  // 替换成自己的测试桶名称

    QString m_uploadLocalPath = "./upload.txt";
    QString m_downloadLocalPath = "./download.txt";
    QString m_updownKey = "test/bll/newupload.txt";
};

#endif  // TESTCOS_H
