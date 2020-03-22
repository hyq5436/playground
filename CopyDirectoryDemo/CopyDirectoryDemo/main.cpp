#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QtCore/QCoreApplication>

bool copyDirectory(const QDir& fromDir,
                   const QDir& toDir,
                   bool bCoverIfFileExists) {
    QDir fromDir_ = fromDir;
    QDir toDir_ = toDir;

    if (!toDir_.exists()) {
        if (!toDir_.mkdir(toDir.absolutePath()))
            return false;
    }

    QFileInfoList fileInfoList = fromDir_.entryInfoList();

    foreach (QFileInfo fileInfo, fileInfoList) {
        if (fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;
        //拷贝子目录
        if (fileInfo.isDir()) {
            if (!copyDirectory(fileInfo.filePath(),
                               toDir_.filePath(fileInfo.fileName()), true)) {
                return false;
            }
        }
        //拷贝子文件
        else {
            if (bCoverIfFileExists && toDir_.exists(fileInfo.fileName())) {
                toDir_.remove(fileInfo.fileName());
            }
            if (!QFile::copy(fileInfo.filePath(),
                             toDir_.filePath(fileInfo.fileName()))) {
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    QCoreApplication a(argc, argv);

    QString workPath = "C:/Users/Page/AppData/Local/SuningIM/IMLog/";
    QString destDir =
        "PC-LIVE-" + QDateTime::currentDateTime().toString("yyyyMMddhhmmss");

    copyDirectory(workPath + "Live", workPath + destDir, true);
    return a.exec();
}
