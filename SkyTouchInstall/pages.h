#ifndef PAGES_H
#define PAGES_H

#include <QWidget>
#include <QtWidgets>
#include <QDebug>
#include <vector>
#include <QtNetwork/QNetworkAccessManager>


#include "network.h"
#include "installconfirmation.h"
#include "global.h"
//#include<pair>

using std::vector;
using std::pair;


class SoftwareDownloadPage : public QWidget {
    Q_OBJECT
public:
    SoftwareDownloadPage(QWidget *parent = 0);
    void initPage(vector<SoftwareInfo*> &softwareL, Network *network);

   // ~SoftwareInstallationPage();

public slots:
    void downloadButtonCliked();
    void searchForLocalFiles();
    void viewDownloadProg();
    void showReadyToInstall();
    void backToSoftwareList();

private:
    bool readyToInstall;
    bool downloadConfirmed;
    bool firstLoad;

    QVBoxLayout *mainLayout;
    Network *network;

    QPushButton *viewDownloadProgButton;
    QPushButton *readyToInstallButton;
    QPushButton *stopDownloadBtn;


    vector<SoftwareInfo*> softwareList;
    vector<QNetworkReply*> replys;

    void showDownloadProgress();
    void startDownloads();
    void stopDownloads();
    bool isDownloadInProgress();



};



class ConfigurationPage : public QWidget{
public:
    ConfigurationPage(QWidget *parent = 0);
    //~ConfigurationPage();
};

void clearWidgetsAndLayouts(QLayout * layout);



#endif // PAGES_H
