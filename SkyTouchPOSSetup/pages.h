#ifndef PAGES_H
#define PAGES_H



#include "network.h"
#include "installconfirmation.h"
#include "editregistry.h"
#include "registryhandler.h"
#include "global.h"


class SoftwareDownloadPage : public QWidget {
    Q_OBJECT
public:
    SoftwareDownloadPage(QWidget *parent = 0);
    ~SoftwareDownloadPage();
    void initPage(vector<SoftwareInfo*> &softwareL, Network *network);



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
    ~ConfigurationPage();
    QStandardItem* getUserEntryItem() {return customPolicies;}

public slots:
    void itemDoubleClicked(const QModelIndex &index);
    void restoreDefault();
    void applySettings();


private:
    void buildPolicyTree();
    void populatePolicies();


    RegistryHandler regHan;
    //UserEditReg userReg;
    QMap<QString, QStandardItem*> policyNameToItemValue;


    QVBoxLayout *mainLayout = nullptr;
    QTreeView *policyTree = nullptr;

    QStandardItem *recommendedPolicies = nullptr;
    QStandardItem *controlPanelPolicies = nullptr;
    QStandardItem *systemPolicies = nullptr;
    QStandardItem *personalizationPolicies = nullptr;
    QStandardItem *customPolicies = nullptr;


};

void clearLayotAndWidgets(QLayout * layout);
void startProcess(QObject *parent, QString programPath, QString fileName );

#endif // PAGES_H
