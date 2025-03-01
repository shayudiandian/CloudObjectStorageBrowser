#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <QString>


class FileHelper
{
public:
    FileHelper();
    static QString readAllTxt(const QString& filePath);
    static QVariant readAllJson(const QString& filePath);

    static QList<QStringList> readAllCsv(const QString& filePath);
    static void generateExceptionFile(const QString& filePath);
    static void writeFlie(const QStringList lines, const QString& filePath);

    static QString joinPath(const QString& path1, const QString& path2);  // 拼接路径
    static bool mkPath(const QString& path);   // 创建目录
};

#endif // FILEHELPER_H
