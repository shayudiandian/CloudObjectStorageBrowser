#include "daocloudscos.h"
#include "src/config/exceptions.h"
#include "src/config/errorcode.h"
#include "cos_api.h"

#include <QCoreApplication>
#include <QDir>

using namespace qcloud_cos;

DaoCloudsCos::DaoCloudsCos()
{
    m_config = new CosConfig("./cosconfig.json");
}

DaoCloudsCos::~DaoCloudsCos()
{
    delete m_config;
    m_config = nullptr;
}


QList<MyBucket> DaoCloudsCos::buckets()
{
    QList<MyBucket> res;

    GetServiceReq req;
    GetServiceResp resp;

    CosAPI cos = CosAPI(*m_config);

    CosResult result = cos.GetService(req, &resp);

    if (!result.IsSucc()) throwError(EC_211000, result);

    std::vector<Bucket> bs = resp.GetBuckets();
    for (std::vector<Bucket>::const_iterator itr = bs.begin(); itr != bs.end(); ++itr)
    {
        const Bucket& v = *itr;

        MyBucket b;
        b.name = QString(v.m_name.c_str());
        b.location = QString(v.m_location.c_str());
        b.createDate = QString(v.m_create_date.c_str());
        res.append(b);
    }
    return res;
}

QList<MyBucket> DaoCloudsCos::login(const QString &secretId, const QString &secretKey)
{
    m_config->SetAccessKey(secretId.toStdString());
    m_config->SetSecretKey(secretKey.toStdString());
    m_config->SetRegion("ap-shanghai");

    return buckets();
}

bool DaoCloudsCos::isBucketExists(const QString &bucketName)
{
    MyBucket bucket = getBucketByName(bucketName);
    return bucket.isValid();
}

QString DaoCloudsCos::getBucketLocation(const QString &bucketName)
{
    CosAPI cos = CosAPI(*m_config);
    QString location(cos.GetBucketLocation(bucketName.toStdString()).c_str());
    if (location != "") return location;
    MyBucket bucket = getBucketByName(bucketName);
    if (bucket.isValid()) return bucket.location;
    throw BaseException(EC_332000, QString("获取桶位置失败 %1").arg(bucketName));
}

void DaoCloudsCos::putBucket(const QString &bucketName, const QString &location)
{
    if (isBucketExists(bucketName)) return;

    PutBucketReq req(bucketName.toLocal8Bit().data());
    PutBucketResp resp;

    m_config->SetRegion(location.toStdString());
    CosAPI cos(*m_config);

    CosResult result = cos.PutBucket(req, &resp);

    if (!result.IsSucc()) throwError(EC_331100, result);
}

void DaoCloudsCos::deleteBucket(const QString &bucketName)
{
    if (!isBucketExists(bucketName)) return;

    DeleteBucketReq req(bucketName.toLocal8Bit().data());
    DeleteBucketResp resp;

    QString location = getBucketLocation(bucketName);
    m_config->SetRegion(location.toStdString());
    CosAPI cos(*m_config);

    CosResult result = cos.DeleteBucket(req, &resp);

    if (!result.IsSucc()) throwError(EC_331300, result);
}

QList<MyObject> DaoCloudsCos::getObjects(const QString &bucketName, const QString &dir)
{
    GetBucketReq req(bucketName.toLocal8Bit().data());
    if (dir != "") req.SetPrefix(dir.toLocal8Bit().data());
    req.SetDelimiter("/");

    GetBucketResp resp;

    QString location = getBucketLocation(bucketName);
    m_config->SetRegion(location.toStdString());

    CosAPI cos(*m_config);
    CosResult result = cos.GetBucket(req, &resp);

    if (!result.IsSucc()) throwError(EC_331200, result);

    return getDirList(resp, dir) + getFileList(resp, dir);
}

bool DaoCloudsCos::isObjectExists(const QString &bucketName, const QString &key)
{
    QString location = getBucketLocation(bucketName);
    m_config->SetRegion(location.toStdString());
    CosAPI cos(*m_config);

    return cos.IsObjectExist(bucketName.toStdString(), key.toStdString());
}

void DaoCloudsCos::putObject(const QString &bucketName, const QString &key, const QString &localPath, const TransProgressCallback &callback)
{
    // 初始化上传
    SharedAsyncContext context;
    // 异步上传
    AsyncPutObjectReq put_req(bucketName.toLocal8Bit().data(), key.toLocal8Bit().data(), localPath.toLocal8Bit().data());
    // 设置上传进度回调
    if (callback)
        put_req.SetTransferProgressCallback(callback);

    QString location = getBucketLocation(bucketName);
    m_config->SetRegion(location.toStdString());
    CosAPI cos(*m_config);

    // 开始上传
    context = cos.AsyncPutObject(put_req);
    context->WaitUntilFinish();  // 等待上传结束
    CosResult result = context->GetResult();

    if (!result.IsSucc()) {
        throwError(EC_332400, result);
    }
}

void DaoCloudsCos::getObject(const QString &bucketName, const QString &key, const QString &localPath, const TransProgressCallback &callback)
{
    // 下载初始化
    SharedAsyncContext context;
    // 异步下载
    AsyncGetObjectReq get_req(bucketName.toLocal8Bit().data(), key.toLocal8Bit().data(), localPath.toLocal8Bit().data());
    // 设置下载进度回调
    if (callback)
        get_req.SetTransferProgressCallback(callback);

    QString location = getBucketLocation(bucketName);
    m_config->SetRegion(location.toStdString());
    CosAPI cos(*m_config);

    // 开始下载对象
    context = cos.AsyncGetObject(get_req);
    context->WaitUntilFinish();  // 等待下载结束
    CosResult result = context->GetResult();

    if (!result.IsSucc()) {
        throwError(EC_332500, result);
    }
}

QList<MyObject> DaoCloudsCos::getDirList(qcloud_cos::GetBucketResp &resp, const QString &dir)
{
    QList<MyObject> res;
    // 获取目录列表
    std::vector<std::string> cs = resp.GetCommonPrefixes();
    for (int i = 0; i < cs.size(); i++)
    {
        QString key = QString::fromStdString(cs[i]);
        // qDebug() << "dir: " << key;
        MyObject object;
        object.dir = dir;
        object.name = key.mid(dir.size());   // 例如 test/bll/ 需要获取 bll/，mid方法以dir的大小为起点
        object.lastmodified = "-";    // 修改时间为空
        object.key = key;
        res.append(object);
        // qDebug() << "dirName: " << object.name;
    }
    return res;
}

QList<MyObject> DaoCloudsCos::getFileList(qcloud_cos::GetBucketResp &resp, const QString &dir)
{
    QList<MyObject> res;
    // 获取文件列表
    const std::vector<Content>& contents = resp.GetContents();
    for (std::vector<Content>::const_iterator itr = contents.begin(); itr != contents.end(); ++itr)
    {
        const Content& content = *itr;
        QString key = QString::fromStdString(content.m_key);     // 防止乱码
        // qDebug() << "file: " << key;
        QString name = key.mid(dir.size());
        if (key != dir)
        {
            MyObject object;
            object.name = name;
            object.lastmodified = QString::fromStdString(content.m_last_modified);
            object.size = QString::fromStdString(content.m_size).toULongLong();
            object.dir = dir;
            object.key = key;
            res.append(object);
            // qDebug() << "fileName: " << name;
        }
    }
    return res;
}

void DaoCloudsCos::throwError(const QString& code, qcloud_cos::CosResult& result)
{
    QString msg = QString("腾讯云错误码【%1】： %2").arg(result.GetErrorCode().c_str(), result.GetErrorMsg().c_str());
    qDebug() << msg;
    throw BaseException(code, msg);
}

MyBucket DaoCloudsCos::getBucketByName(const QString &bucketName)
{
    QList<MyBucket> bs = buckets();        // 调用前面的DaoCloudsCos::buckets()方法
    for (const auto& b: qAsConst(bs)) {
        if (b.name == bucketName) {
            return b;
        }
    }
    return MyBucket();
}

