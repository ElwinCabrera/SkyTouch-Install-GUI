#include "softwareinfo.h"

SoftwareInfo::SoftwareInfo(QString softwareName, QString url32BitVer, QString url64BitVer, QObject *parent) : QObject(parent)
{
    this->softwareName = softwareName;
    this->url32BitVer = url32BitVer;
    this->url64BitVer = url64BitVer;

    fileName64 = softwareName + "_x64.exe";
    fileName32 = softwareName + ".exe";

    //filePath = QDir::toNativeSeparators(QDir::homePath() + QDir::separator() +"Downloads" + QDir::separator() + fileName64);
    filePath = QDir::toNativeSeparators(QDir::currentPath() + QDir::separator() + fileName64);

}
