#ifndef PAGES_H
#define PAGES_H

#include <QWidget>
#include <QtWidgets>
#include <QDebug>
#include <vector>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

#include "network.h"
#include "installconfirmation.h"
//#include<pair>

using std::vector;
using std::pair;


class SoftwareInstallationPage : public QWidget {
    Q_OBJECT
public:
    SoftwareInstallationPage(QWidget *parent = 0);
   // ~SoftwareInstallationPage();
    void setMainLayout(bool firstTimeLoad);


public slots:
    void onStartInstallationButtonCliked();

private:
    QRadioButton *installCRERadioBtn;
    QRadioButton *installCRE64RadioBtn;
    QPushButton *startInstallationButton;
    //QPushButton *stopDownload;
    //QProgressBar *pBar;
    QVBoxLayout *mainLayout;
    QVBoxLayout *mainLayout2;

    InstallConfirmation *confirmWindow;
    Network network;


    vector<pair<QGroupBox *,QString>> installGroups;
    vector<QString> getURLs;
    vector<QProgressBar*> pBars;
    vector<QNetworkReply*> replys;
    vector<ProgressListenner*> pListeners;

    void showDownloadProgress();
    void startDownloads();
    void stopDownloads();
};



class ConfigurationPage : public QWidget{
public:
    ConfigurationPage(QWidget *parent = 0);
    //~ConfigurationPage();
};

void clearWidgetsAndLayouts(QLayout * layout);



#endif // PAGES_H
