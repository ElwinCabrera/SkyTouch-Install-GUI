#ifndef PAGES_H
#define PAGES_H



#include "network.h"
#include "installconfirmation.h"
#include "warningbox.h"
#include "registryhandler.h"
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
    void startInstalls();


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

    void populateLocalFilesMap();



};



class ConfigurationPage : public QWidget{
    Q_OBJECT
public:
    ConfigurationPage(QWidget *parent = 0);
    //~ConfigurationPage();
public slots:
    void itemDoubleClicked(const QModelIndex &index);

public:
    QTreeView* buildPolicyTree();
    void addRecommendedPolicies(QStandardItem *recommendedPolicies);

    RegistryHandler regHan;
    QVBoxLayout *mainLayout = nullptr;
    QStandardItemModel *model = nullptr;
    QTreeView *policyTree = nullptr;



    QMap<QString, QStandardItem*> policyNameToItemValue;
    //QMap<QString, >
};

void clearPage(QLayout * layout);
void startProcess(QObject *parent, QString programPath, QString fileName );

#endif // PAGES_H
