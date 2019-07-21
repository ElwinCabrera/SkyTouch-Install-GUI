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
#include "global.h"
//#include<pair>

using std::vector;
using std::pair;


class SoftwareDownloadPage : public QWidget {
    Q_OBJECT
public:
    SoftwareDownloadPage(QWidget *parent = 0);
    void initPage(vector<SoftwareInfo*> softwareL, Network *network);

   // ~SoftwareInstallationPage();

public slots:
    void downloadButtonCliked();

private:

    QVBoxLayout *mainLayout;
    Network *network;


    vector<SoftwareInfo*> softwareList;
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
