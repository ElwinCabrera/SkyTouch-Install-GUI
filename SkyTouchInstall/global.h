#ifndef GLOBAL_H
#define GLOBAL_H

#include<QWidget>
#include <QtWidgets>
#include <QtNetwork/QNetworkReply>

class ProgressListenner : public QObject
{
    //Q_OBJECT
public:
   ProgressListenner() : _lastKnownReceived(0), _lastKnownTotal(0){}

   qint64 _lastKnownReceived;
   qint64 _lastKnownTotal;
   QProgressBar *pBar;

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

    SoftwareInfo(QString softwareName,
                 QString url32BitVersion,
                 QString url64BitVersion,
                 bool markedForDownlaod ,
                 bool markedForInstall )
    {
        this->softwareName = softwareName;
        this->url32BitVersion = url32BitVersion;
        this->url64BitVersion = url64BitVersion;
        this->markedForDownlaod = markedForDownlaod;
        this->markedForInstall = markedForInstall;
        this->version64Bit = true;
        this->version32Bit = false;
        downloadInProg = false;
        downloadSuccess = false;
        downloadInterrupted = false;
    }


  QString softwareName;
  QString url32BitVersion;
  QString url64BitVersion;
  bool markedForDownlaod;
  bool markedForInstall;
  bool downloadInProg ;
  bool downloadSuccess;
  bool downloadInterrupted;
  bool version64Bit ;
  bool version32Bit ;

  ProgressListenner *pl;
  QNetworkReply *reply;

public slots:
  void onDownloadCheckBoxClicked() {markedForDownlaod = !markedForDownlaod; debugInfo();}
  void onInstallCheckBoxClicked() {markedForInstall = !markedForInstall; debugInfo();}
  void onVersionSelect() {version32Bit = !version32Bit; version64Bit = !version64Bit; debugInfo();}

  void debugInfo(){
      qDebug() <<"\n" <<softwareName <<" marked for download"<<markedForDownlaod;
      qDebug() << softwareName <<" marked for Install"<<markedForInstall;
      qDebug() << "32Bit  = " << version32Bit ;
      qDebug() << "64Bit  = " << version64Bit ;
  }

};



#endif // GLOBAL_H
