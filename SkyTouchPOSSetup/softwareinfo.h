#ifndef SOFTWAREINFO_H
#define SOFTWAREINFO_H

#include "global.h"

class SoftwareInfo : public QObject
{
    Q_OBJECT
public:
    explicit SoftwareInfo(QString softwareName, QString url32BitVer, QString url64BitVer, QObject *parent = nullptr);
    ~SoftwareInfo();


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



    void debugInfo();


public slots:
    void onDownloadCheckBoxClicked();
    void onInstallCheckBoxClicked();

    void onVersionSelect();
    void downloadStart();
    void stopDownload();

    void finishedFileIO(void);

    void fileIO(void);

    void finishedDownload();


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
