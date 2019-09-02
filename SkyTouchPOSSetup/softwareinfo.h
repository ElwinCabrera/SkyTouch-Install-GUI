#ifndef SOFTWAREINFO_H
#define SOFTWAREINFO_H

#include "global.h"

class SoftwareInfo : public QObject
{
    Q_OBJECT
public:
    explicit SoftwareInfo(QString softwareName, QString url32BitVer, QString url64BitVer, QObject *parent = nullptr);


    /***************Getters*************/
    QString getSoftwareName(){return softwareName;}
    QString get32BitURL(){return url32BitVer;}
    QString get64BitURL(){return url64BitVer;}

    QString getFileName64() {return fileName64;}
    QString getFileName32() {return fileName32;}
    QString getFilePath() {return filePath;}

    bool getDownloadMarked() {return markedForDownlaod;}
    bool downloadInProgress() {return downloadInProg;}
    bool getDownloadSuccess() {return downloadSuccess;}
    bool downloadInterrupted() {return downloadInterrupt;}

    bool getInstallReadyState(){return readyForInstall;}
    bool getInstallMarked() {return markedForDownlaod;}

    bool getVersionSelect32() {return version32BitSelect;}
    bool getVersionSelect64() {return version64BitSelect;}

    ProgressListenner* getProgressListener() {return pl;}
    QNetworkReply* getNetworkReply() {return reply;}



    /****************Setters**********/
    void setSoftwareName(QString name) {softwareName = name;}
    void set32BitURL(QString url) {url32BitVer = url;}
    void set64BitURL(QString url) {url64BitVer = url;}

    void setFilePath(QString path) {filePath = path;}

    /*void setDownloadMarked(bool state){markedForDownlaod = marked;}
    void setDownloadInProgress(bool inProg) {downloadInProg = inProg; }
    void setDownloadSuccess(bool success) {downloadSuccess = success;}
    void setDownloadInterrupted(bool interrupted) {downloadInterrupt = interrupted;}

    void setInstallReadyState(bool ready) {readyForInstall = ready;}
    void setInstallMarkedState(bool marked) {markedForDownlaod = marked;}*/

    void setProgressListener(ProgressListenner *progL) {pl = progL;}
    void setNetworkReply(QNetworkReply *r) {reply = r;}



    void debugInfo(){
        qDebug() <<"\n" <<softwareName <<" marked for download"<<markedForDownlaod;
        qDebug() << softwareName <<" marked for Install"<<markedForInstall;
        qDebug() << "32Bit  = " << version32BitSelect ;
        qDebug() << "64Bit  = " << version64BitSelect ;
    }


public slots:
    void onDownloadCheckBoxClicked() {markedForDownlaod = !markedForDownlaod; }
    void onInstallCheckBoxClicked() {markedForInstall = !markedForInstall; }

    void onVersionSelect() {
        version32BitSelect = !version32BitSelect;
        version64BitSelect = !version64BitSelect;

        //if(version32BitSelect) filePath = QDir::toNativeSeparators(QDir::homePath() + QDir::separator() +"Downloads" + QDir::separator() +fileName32);
        //if(version64BitSelect) filePath = QDir::toNativeSeparators(QDir::homePath() + QDir::separator() +"Downloads" + QDir::separator() +fileName64);

        if(version32BitSelect) filePath = QDir::toNativeSeparators(QDir::currentPath() + QDir::separator() + fileName32);
        if(version64BitSelect) filePath = QDir::toNativeSeparators(QDir::currentPath() + QDir::separator() + fileName64);
    }
    void downloadStart() { markedForDownlaod = false; downloadInProg = true; readyForInstall = false; downloadInterrupt = false; downloadSuccess = false;}
    void stopDownload() {
        if(!downloadInProg) return ;
        downloadSuccess = false; downloadInterrupt = true; downloadInProg = false; readyForInstall = false;
    }

    void finishedFileIO(void){
      qDebug() << "finished file I/O";
    }

    void fileIO(void){

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

    void finishedDownload(){
      qDebug() << "finished Downloading in software info";
      QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

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


private:


    QString softwareName = "";
    QString url32BitVer = "";
    QString url64BitVer = "";

    QString fileName32 = "";
    QString fileName64 = "";
    QString filePath = "";

    //bool readyForDownload;
    bool markedForDownlaod = false;
    bool downloadInProg = false;
    bool downloadSuccess = false;
    bool downloadInterrupt = false;

    bool readyForInstall = false;
    bool markedForInstall = false;

    bool version64BitSelect = true;
    bool version32BitSelect = false;

    ProgressListenner *pl = nullptr;
    QNetworkReply *reply = nullptr;
};

#endif // SOFTWAREINFO_H
