#ifndef GLOBAL_H
#define GLOBAL_H

#include <QWidget>
#include <QtWidgets>
#include <QDebug>
#include <QDialog>
#include <QObject>
#include<QAction>

#include <QSet>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QAuthenticator>
#include <QtNetwork/QNetworkProxy>

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>




using std::vector;
using std::pair;
using std::unordered_set;
using std::set;
using std::unordered_map;


class ProgressListenner : public QObject
{
    //Q_OBJECT
public:
   ProgressListenner() : _lastKnownReceived(0), _lastKnownTotal(0){}

   qint64 _lastKnownReceived;
   qint64 _lastKnownTotal;
   QProgressBar *pBar= nullptr;

public slots:
     void onDownloadProgress( qint64 bytesReceived, qint64 bytesTotal )
      {
          _lastKnownReceived = bytesReceived;
          _lastKnownTotal = bytesTotal;

          pBar->setRange(0,bytesTotal);
          pBar->setValue(bytesReceived);
          if(bytesTotal < 0) pBar->setValue(0);
      }
};

class SoftwareInfo : public QObject{ // holds the software name and its 32 and 64 bit version URLs


public:
    SoftwareInfo(QString softwareName, QString url32BitVer, QString url64BitVer){
        this->softwareName = softwareName;
        this->url32BitVer = url32BitVer;
        this->url64BitVer = url64BitVer;

        fileName64 = softwareName + "_x64.exe";
        fileName32 = softwareName + ".exe";

        filePath = QDir::toNativeSeparators(QDir::homePath() + QDir::separator() +"Downloads" + QDir::separator() + fileName64);
        //filePath = QDir::toNativeSeparators(QDir::currentPath() + QDir::separator() + fileName64);

    }

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

  //void setDownloadMarked(bool state){markedForDownlaod = marked;}
  //void setDownloadInProgress(bool inProg) {downloadInProg = inProg; }
  //void setDownloadSuccess(bool success) {downloadSuccess = success;}
  //void setDownloadInterrupted(bool interrupted) {downloadInterrupt = interrupted;}

  //void setInstallReadyState(bool ready) {readyForInstall = ready;}
  //void setInstallMarkedState(bool marked) {markedForDownlaod = marked;}

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

      if(version32BitSelect) filePath = QDir::toNativeSeparators(QDir::homePath() + QDir::separator() +"Downloads" + QDir::separator() +fileName32);
      if(version64BitSelect) filePath = QDir::toNativeSeparators(QDir::homePath() + QDir::separator() +"Downloads" + QDir::separator() +fileName64);

      //if(version32BitSelect) filePath = QDir::toNativeSeparators(QDir::currentPath() + QDir::separator() + fileName32);
      //if(version64BitSelect) filePath = QDir::toNativeSeparators(QDir::currentPath() + QDir::separator() + fileName64);
  }
  void downloadStart() { markedForDownlaod = false; downloadInProg = true; readyForInstall = false; downloadInterrupt = false; downloadSuccess = false;}
  void stopDownload() {
      if(!downloadInProg) return ;
      downloadSuccess = false; downloadInterrupt = true; downloadInProg = false; readyForInstall = false;
  }

  void finishedDownload(){
    qDebug() << "finished Downloading in software info";

    markedForDownlaod = false;
    downloadInProg = false;
    downloadSuccess = true;
    downloadInterrupt  = false;
    readyForInstall = true;

    if(pl) {
        delete pl;
        pl = nullptr;
    }

    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

    if(reply == NULL) return;



    //QString targetFolder = QDir::homePath() + QDir::separator()+ "Downloads";
    //QString targetFolder = QDir::currentPath();

    //QString fileName = softwareName;
    //if(version64BitSelect) fileName += "_x64";
    //fileName += ".exe";

    //QString filePath = targetFolder + QDir::separator() + fileName;
    //filePath = QDir::toNativeSeparators(filePath);

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
        //mFile->write(reply->read(reply->size()));
        mFile->flush();
        mFile->close();
        qDebug() << "Finished writing to file. file closed.";

    }


    if(reply) reply->deleteLater();
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

class LocalFile: public QObject{

public:
    LocalFile(QString fileName, QString filePath, bool readyForInstall){
        this->fileName = fileName;
        this->filePath = filePath;
        this->readyForInstall = readyForInstall;
    }

    QString getFileName() {return fileName;}
    QString getFilePath() {return filePath;}
    bool getInstallState() {return markedForInstall;}
    bool getReadyState() {return readyForInstall;}

    void setInstallState(bool install){this->markedForInstall = install;}
    void setReadyState(bool ready) {readyForInstall = ready;}

public slots:
    void changeReadyState(){ readyForInstall = !readyForInstall; markedForInstall = false;}
    void changeInstallState(){ markedForInstall = true; readyForInstall = false; }

private:
    QString fileName = "";
    QString filePath = "";
    bool markedForInstall = false;
    bool readyForInstall = false;


};

int messageBox(QString text, QString moreDetails);



#endif // GLOBAL_H
