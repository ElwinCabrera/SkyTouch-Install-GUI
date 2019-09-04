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

SoftwareInfo::~SoftwareInfo()
{
    qDebug() << "SoftwareInfo Destructor";
    if(pl) {
        delete pl;
        pl= nullptr;
    }
    /*if(reply && !reply->isFinished()) {
        delete reply;
        reply = nullptr;
    }*/

}

void SoftwareInfo::debugInfo(){
    qDebug() <<"\n" <<softwareName <<" marked for download"<<markedForDownlaod;
    qDebug() << softwareName <<" marked for Install"<<markedForInstall;
    qDebug() << "32Bit  = " << version32BitSelect ;
    qDebug() << "64Bit  = " << version64BitSelect ;
}

void SoftwareInfo::onDownloadCheckBoxClicked() {
    markedForDownlaod = !markedForDownlaod;
}

void SoftwareInfo::onInstallCheckBoxClicked() {
    markedForInstall = !markedForInstall;
}

void SoftwareInfo::onVersionSelect() {
    version32BitSelect = !version32BitSelect;
    version64BitSelect = !version64BitSelect;

    //if(version32BitSelect) filePath = QDir::toNativeSeparators(QDir::homePath() + QDir::separator() +"Downloads" + QDir::separator() +fileName32);
    //if(version64BitSelect) filePath = QDir::toNativeSeparators(QDir::homePath() + QDir::separator() +"Downloads" + QDir::separator() +fileName64);

    if(version32BitSelect) filePath = QDir::toNativeSeparators(QDir::currentPath() + QDir::separator() + fileName32);
    if(version64BitSelect) filePath = QDir::toNativeSeparators(QDir::currentPath() + QDir::separator() + fileName64);
}

void SoftwareInfo::downloadStart() {
    markedForDownlaod = false;
    downloadInProg = true;
    readyForInstall = false;
    downloadInterrupt = false;
    downloadSuccess = false;
}

void SoftwareInfo::stopDownload() {
    if(!downloadInProg) return ;
    if(reply) {
        disconnect(reply, &QNetworkReply::downloadProgress, pl, &ProgressListenner::onDownloadProgress);
        disconnect(reply,0,0,0);
        reply->abort();
        reply->deleteLater();
    }
    downloadSuccess = false;
    downloadInterrupt = true;
    downloadInProg = false;
    readyForInstall = false;
}

void SoftwareInfo::finishedFileIO(){
    qDebug() << "finished file I/O";
}

void SoftwareInfo::fileIO(){

    if(reply == nullptr) return;

    QFile *mFile = new QFile(filePath);
    // Trying to open the file
    if (!mFile->open(QIODevice::WriteOnly)){
        qDebug() << "Could not open file";
        delete mFile;
        mFile = nullptr;
    }

    if(mFile) {
        qDebug() << "file is open attempting to write";
        mFile->write(reply->readAll());
        //QByteArray arr = reply->readAll();
        mFile->write(reply->read(reply->size()));
        mFile->flush();
        mFile->close();
        qDebug() << "Finished writing to file. file closed.";

    }
    if(reply) reply->deleteLater();
}

void SoftwareInfo::finishedDownload(){
    qDebug() << "finished Downloading in software info";
    //QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());


    markedForDownlaod = false;
    downloadInProg = false;
    downloadSuccess = true;
    downloadInterrupt  = false;
    readyForInstall = true;

    if(pl) {
        delete pl;
        pl = nullptr;
    }

    QFutureWatcher<void> futureWatcher;
    connect(&futureWatcher, SIGNAL(finished()), this, SLOT(finishedFileIO()));


    QFuture<void> future = QtConcurrent::run(this, &SoftwareInfo::fileIO);

    futureWatcher.setFuture(future);


}
