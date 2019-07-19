#ifndef GLOBAL_H
#define GLOBAL_H

#include<QWidget>

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
    }


  QString softwareName;
  QString url32BitVersion;
  QString url64BitVersion;
  bool markedForDownlaod;
  bool markedForInstall;
  bool version64Bit ;
  bool version32Bit ;

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
