#ifndef PAGES_H
#define PAGES_H



#include "network.h"
#include "installconfirmation.h"
#include "usereditregistry.h"
#include "registryhandler.h"
#include "global.h"
#include "softwareinfo.h"

class SoftwareDownloadPage : public QWidget {
    Q_OBJECT
public:
    SoftwareDownloadPage(QSet<SoftwareInfo*> &softwareList, Network *network = nullptr, QStatusBar *statusBar = nullptr, QWidget *parent = nullptr);
    ~SoftwareDownloadPage();
    void initPage();

    void addToList(SoftwareInfo *si);
    void removeFromList(SoftwareInfo *si);

    void addToLocalFileMap(QString fileName,LocalFile *newLf);
    void removeFromLocalFileMap(QString fileName);




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
    bool readyToInstall = false;
    bool localFilesInInstallQ = false;
    bool hasLocalFiles = false;
    bool onMainPage = false;
    bool onLocalFilesPage = false;

    QVBoxLayout *mainLayout = nullptr;
    Network *network = nullptr;

    QStatusBar *statusBar = nullptr;

    QPushButton *viewDownloadProgButton = nullptr;
    QPushButton *readyToInstallButton = nullptr;
    QPushButton *stopDownloadBtn = nullptr;
    QPushButton *searchForLocalButton = nullptr;


    QSet<SoftwareInfo*> softwareList;
    QMap<QString,LocalFile*> localFilesMap;
    QMap<QString,bool> localFileDeletedMap;

    void activeDownloadsPage();
    void startDownloads();
    bool downloadsInProg();
    void stopDownloads();
    bool isDownloadInProgress();
    bool isReadyForInstall();
    void clearGlobalWidgets();

    void populateLocalFilesMap();
    void updateLocalFilesMap();



};



class ConfigurationPage : public QWidget{
    Q_OBJECT
public:
    ConfigurationPage(RegistryHandler *regHan = nullptr, QStatusBar *statusBar = nullptr, QWidget *parent = nullptr);
    ~ConfigurationPage();
    QStandardItem* getUserEntryItem() {return customPolicies;}

public slots:
    void itemDoubleClicked(const QModelIndex &index);
    void restoreDefault();
    void applySettings();


private:
    void buildPolicyTree();
    void populatePolicies();


    RegistryHandler *regHan = nullptr;
    QStatusBar *statusBar = nullptr;
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
