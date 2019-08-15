#ifndef PAGES_H
#define PAGES_H



#include "network.h"
#include "installconfirmation.h"
#include "global.h"


class SoftwareDownloadPage : public QWidget {
    Q_OBJECT
public:
    SoftwareDownloadPage(QWidget *parent = 0);
    void initPage(vector<SoftwareInfo*> &softwareL, Network *network);

   // ~SoftwareInstallationPage();

public slots:
    void downloadButtonCliked();
    void localFilesPage();
    void viewDownloadProg();
    void readyToInstallPage();
    void backToInitPage();
    void finishedDownloading();
    void addFileToInstallList();


private:
    bool readyToInstall;
    bool downloadConfirmed;
    bool localFilesInInstallQ;

    QVBoxLayout *mainLayout = nullptr;
    Network *network = nullptr;

    QPushButton *viewDownloadProgButton = nullptr;
    QPushButton *readyToInstallButton = nullptr;
    QPushButton *stopDownloadBtn = nullptr;


    vector<SoftwareInfo*> softwareList;
    QMap<QString,LocalFile*> localFilesMap;

    void activeDownloadsPage();
    void startDownloads();
    void stopDownloads();
    bool isDownloadInProgress();
    bool isReadyForInstall();
    void clearGlobalWidgets();



};



class ConfigurationPage : public QWidget{
public:
    ConfigurationPage(QWidget *parent = 0);
    //~ConfigurationPage();
};

void clearPage(QLayout * layout);



#endif // PAGES_H
