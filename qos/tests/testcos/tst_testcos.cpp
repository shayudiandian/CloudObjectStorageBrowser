#include "tst_testcos.h"
#include "src/config/exceptions.h"
#include "src/helper/filehelper.h"

TestCos::TestCos() {}

TestCos::~TestCos() {}

void TestCos::initTestCase()
{
    m_cos.login(m_secretId, m_secretKey);    // 登录
    FileHelper::writeFlie(QStringList() << "abc" << "def", m_uploadLocalPath);  // 在m_uploadLocalPath创建本地文件以及内容
}

void TestCos::cleanupTestCase()
{
    QFile::remove(m_uploadLocalPath);
    // QFile::remove(m_downloadLocalPath);
}

void TestCos::test_buckets()
{
    QList<MyBucket> bs = m_cos.buckets();
    QVERIFY(bs.size() > 0); // QVERIFY进行bool表达式的判断，如果为真则表示通过，否则表示失败
    QCOMPARE(bs.size(), 1);  // QCOMPARE进行恒等的比较
}

// 去腾讯云对象存储控制台查看某个存储桶的名称及它所属地域
void TestCos::test_isBucketExists()
{
    bool exists = m_cos.isBucketExists(m_bucketName);
    QVERIFY(exists);
}

void TestCos::test_getBucketLocation()
{
    QString location = m_cos.getBucketLocation(m_bucketName);
    QCOMPARE(location, "ap-shanghai");
}

void TestCos::test_putBucket()
{
    // 创建存储桶时，必须以-appid结尾，去控制台的账号信息查看自己的 appid，1317524568
    QSKIP("SKIP test_putBucket");   // 跳过测试用例
    QString bucketName = "test3-1317524568";
    m_cos.putBucket(bucketName, "ap-shanghai");
    bool exists = m_cos.isBucketExists(bucketName);
    QVERIFY(exists);
}

void TestCos::test_deleteBucket()
{
    QSKIP("SKIP test_deleteBucket");
    QString bucketName = "test-1317524568";
    m_cos.deleteBucket(bucketName);
    bool notexists = !m_cos.isBucketExists(bucketName);
    QVERIFY(notexists);
}

void TestCos::test_getObjects()
{
    QSKIP("test_getObjects");
    QList<MyObject> objList = m_cos.getObjects(m_bucketName, "");
    QCOMPARE(objList.size(), 3);

    objList = m_cos.getObjects(m_bucketName, "test/");
    QCOMPARE(objList.size(), 4);

    objList = m_cos.getObjects(m_bucketName, "test/bll/");
    QCOMPARE(objList.size(), 0);
}

void TestCos::test_getObjects2_data()
{
    // 数据驱动：第一阶段，准备测试数据，函数名称需要 _data 结尾
    QTest::addColumn<QString>("dir");
    QTest::addColumn<int>("expected");

    QTest::newRow("root") << "" << 3;
    QTest::newRow("subdir") << "test/" << 4;
    QTest::newRow("leaf") << "test/bll/" << 0;
}

void TestCos::test_getObjects2()
{
    // 数据驱动：第二阶段，从数据表读取数据，并执行比较
    QFETCH(QString, dir);
    QFETCH(int, expected);

    QList<MyObject> objList = m_cos.getObjects(m_bucketName, dir);

    QCOMPARE(objList.size(), expected);
}

void TestCos::test_getObjectError()
{
    // QVERIFY_EXCEPTION_THROWN 捕获预期异常
    QVERIFY_EXCEPTION_THROWN(m_cos.getObjects("bucketname", ""), BaseException);
}

void TestCos::test_putObject()
{
    m_cos.putObject(m_bucketName, m_updownKey, m_uploadLocalPath, nullptr);
    QVERIFY(m_cos.isObjectExists(m_bucketName, m_updownKey));
}

void TestCos::test_getObject()
{
    m_cos.getObject(m_bucketName, m_updownKey, m_downloadLocalPath, nullptr);
    QVERIFY(QFile::exists(m_downloadLocalPath));
}




