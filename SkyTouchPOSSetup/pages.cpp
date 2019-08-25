

#include "pages.h"




SoftwareDownloadPage::SoftwareDownloadPage(QWidget *parent) : QWidget(parent){
    downloadConfirmed = false;
    readyToInstall = false;
    localFilesInInstallQ = false;

    populateLocalFilesMap();

}

void SoftwareDownloadPage::initPage(vector<SoftwareInfo*> &softwareL, Network *network)
{
    if(network) this->network = network;
    if(!softwareL.empty()) this->softwareList = softwareL;

    if(mainLayout) {
        clearPage(mainLayout);
        clearGlobalWidgets();
    }
    mainLayout = new QVBoxLayout;


    QScrollArea *scrollArea = new QScrollArea;

    scrollArea->setFixedSize(QSize(350, 325));

    mainLayout = new QVBoxLayout;
    QWidget *scrollAreaWidget = new QWidget;
    QVBoxLayout *scrollAreaLayout = new QVBoxLayout;

    for(SoftwareInfo *si :  softwareList){

        auto it32 = localFilesMap.find(si->getFileName32());
        auto it64 = localFilesMap.find(si->getFileName64());
        auto itEnd = localFilesMap.end();

        QGroupBox *downloadGroup = new QGroupBox("Download "+si->getSoftwareName());
        downloadGroup->setFixedWidth(312.5);
        downloadGroup->setCheckable(true);
        downloadGroup->blockSignals(true);
        downloadGroup->setChecked(si->getDownloadMarked());

        if(si->downloadInProgress() || si->getDownloadSuccess()
          || (it32 != itEnd && it32.value()->getReadyState() && it64 != itEnd && it64.value()->getReadyState()) ){

            downloadGroup->setChecked(false);
            downloadGroup->setDisabled(true);
        }

        downloadGroup->blockSignals(false);


        QRadioButton *downloadRadioBtn = new QRadioButton("32 Bit");
        QRadioButton *download64RadioBtn = new QRadioButton("64 Bit");
        download64RadioBtn->setChecked(true);

        QHBoxLayout *downloadLayout = new QHBoxLayout;
        //downloadLayout->addStretch(1);
        downloadLayout->addWidget(downloadRadioBtn);
        downloadLayout->addWidget(download64RadioBtn);
        downloadGroup->setLayout(downloadLayout);

        if( si->get32BitURL() == "" || (it32 != itEnd && it32.value()->getReadyState())) {
            downloadRadioBtn->setCheckable(false);
            downloadRadioBtn->setDisabled(true);
            downloadRadioBtn->setText("32 Bit Ready");

        } else downloadRadioBtn->setChecked(si->getVersionSelect32());

        if( si->get64BitURL() == "" || (it64 != itEnd && it64.value()->getReadyState()) ) {
            download64RadioBtn->setCheckable(false);
            download64RadioBtn->setDisabled(true);

        } else download64RadioBtn->setChecked(si->getVersionSelect64());


        scrollAreaLayout->addWidget(downloadGroup);

        connect(downloadGroup, &QGroupBox::toggled, si, &SoftwareInfo::onDownloadCheckBoxClicked);
        connect(download64RadioBtn, &QRadioButton::toggled,si, &SoftwareInfo::onVersionSelect);

    }
    scrollAreaWidget->setLayout(scrollAreaLayout);
    scrollArea->setWidget(scrollAreaWidget);



    QPushButton *searchForLocalButton = new QPushButton(tr("Search For Local Files"));


    viewDownloadProgButton = new QPushButton(tr("Show Downlaod Progress"));




    readyToInstallButton = new QPushButton(tr("Ready to Install"));

    if(!isReadyForInstall()) readyToInstallButton->setDisabled(true);
    else readyToInstallButton->setStyleSheet("QPushButton{background-color:green}");



    QPushButton *downloadButton = new QPushButton(tr("Start Download(s)"));
    downloadButton->setDefault(true);



    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(searchForLocalButton);
    buttonsLayout->addWidget(viewDownloadProgButton);




    //
    mainLayout->addWidget(scrollArea);
    mainLayout->addLayout(buttonsLayout);
    mainLayout->addWidget(downloadButton);
    mainLayout->addWidget(readyToInstallButton);

    mainLayout->addStretch(1);
   // mainLayout->addSpacing(200);
    setLayout(mainLayout);

    connect(downloadButton, &QPushButton::clicked, this, &SoftwareDownloadPage::downloadButtonCliked);
    connect(searchForLocalButton, &QPushButton::clicked, this , &SoftwareDownloadPage::localFilesPage);
    connect(viewDownloadProgButton, &QPushButton::clicked, this, &SoftwareDownloadPage::viewDownloadProg);
    connect(readyToInstallButton, &QPushButton::clicked, this, &SoftwareDownloadPage::readyToInstallPage);


}




void SoftwareDownloadPage::downloadButtonCliked(){
    qDebug() <<  "startDownloadClicked";
    bool minimumOneChecked = false;

    for(SoftwareInfo *si: softwareList){
        if(si->getDownloadMarked()) {minimumOneChecked = true; break;}
    }

    if(minimumOneChecked){
        InstallConfirmation confirmWindow(this, softwareList);
        confirmWindow.setModal(true);
        confirmWindow.exec();

        if(confirmWindow.getConfirmation()) {
            downloadConfirmed = true;
            qDebug() << "download confirmed";
            activeDownloadsPage();
            startDownloads();
            stopDownloadBtn->setDisabled(false);

            //if all downloads are done then return to installation screen
        } else qDebug() << "download  NOT confirmed";

    }
}

void SoftwareDownloadPage::localFilesPage(){

    if(mainLayout) {
        clearPage(mainLayout);
        clearGlobalWidgets();
    }
    mainLayout = new QVBoxLayout;


    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setFixedSize(QSize(350, 325));
    QWidget *scrollAreaWidget = new QWidget;
    QVBoxLayout *scrollAreaLayout = new QVBoxLayout;


    for(LocalFile *lf: localFilesMap) {

        QGroupBox *gBox= new QGroupBox;
        gBox->setFixedWidth(312.5);

        gBox->setCheckable(true);
        if(lf->getInstallState()) {
            gBox->setTitle("Marked For Install");
            gBox->setDisabled(true);
        }

        gBox->setChecked(lf->getReadyState() || lf->getInstallState());

        QLabel *label = new QLabel(lf->getFileName());
        QHBoxLayout *layout = new QHBoxLayout;

        layout->addWidget(label);
        //layout->addStretch(1);
        gBox->setLayout(layout);
        scrollAreaLayout->addWidget(gBox);

        connect(gBox, &QGroupBox::clicked, lf, &LocalFile::changeReadyState);

    }
    scrollAreaWidget->setLayout(scrollAreaLayout);
    scrollArea->setWidget(scrollAreaWidget);

    QPushButton *backButton = new QPushButton(tr("Back"));


    QPushButton *addToInstallListBtn= new QPushButton(tr("Apply Changes"));
    addToInstallListBtn->setDefault(true);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(backButton);
    buttonLayout->addWidget(addToInstallListBtn);


    mainLayout->addWidget(scrollArea);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch(1);
    setLayout(mainLayout);

    connect(addToInstallListBtn, &QPushButton::clicked, this, &SoftwareDownloadPage::addFileToInstallList);
    connect(backButton, &QPushButton::clicked, this, &SoftwareDownloadPage::backToInitPage);


}

void SoftwareDownloadPage::populateLocalFilesMap(){

    QString path = QDir::toNativeSeparators(QDir::homePath() + QDir::separator() + "Downloads");
    //QString path = QDir::toNativeSeparators(QDir::currentPath());
    QDirIterator dirIt(path,QDirIterator::Subdirectories);
    while (dirIt.hasNext()) {
        dirIt.next();
        if (QFileInfo(dirIt.filePath()).isFile()) {
            if(QFileInfo(dirIt.filePath()).suffix() == "exe") {

                qDebug()<< dirIt.filePath();

                QMap<QString,LocalFile*>::iterator it = localFilesMap.find(dirIt.fileName());


                if(it == localFilesMap.end()) {
                    LocalFile *lf = new LocalFile(dirIt.fileName(), dirIt.filePath(),false);
                    localFilesMap.insert(dirIt.fileName(),lf);
                }

            }
        }
    }
}

void SoftwareDownloadPage::viewDownloadProg(){
    activeDownloadsPage();
}

void SoftwareDownloadPage::readyToInstallPage(){

    if(mainLayout) {
        clearPage(mainLayout);
        clearGlobalWidgets();
    }
    mainLayout = new QVBoxLayout;

    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setFixedSize(QSize(350, 325));
    QWidget *scrollAreaWidget = new QWidget;
    QVBoxLayout *scrollAreaLayout = new QVBoxLayout;

    for(SoftwareInfo *si: softwareList){
        if(si->getInstallReadyState()){

            QGroupBox *gBox= new QGroupBox;
            gBox->setFixedWidth(312.5);

            gBox->setCheckable(true);

            gBox->setChecked(false);


            QLabel *label = new QLabel(si->getSoftwareName());
            QHBoxLayout *layout = new QHBoxLayout;

            layout->addWidget(label);
            //layout->addStretch(1);
            gBox->setLayout(layout);
            scrollAreaLayout->addWidget(gBox);

            connect(gBox, &QGroupBox::toggled, si, &SoftwareInfo::onInstallCheckBoxClicked);
        }
    }

    if(localFilesInInstallQ){
        //QGroupBox *gb = new QGroupBox;
        //gb->setFixedWidth(312.5);
        //gb->setDisabled(true);

        QLabel *l = new QLabel("From Local Files");
        l->setAlignment(Qt::AlignCenter);
        l->setFixedWidth(312.5);
        QHBoxLayout *lay = new QHBoxLayout;

        //lay->addWidget(l);
        l->setLayout(lay);
        //gb->setLayout(lay);
        scrollAreaLayout->addWidget(l);

        for(LocalFile *lf: localFilesMap){
            if(lf->getReadyState() || lf->getInstallState()){
                QGroupBox *gBox = new QGroupBox;
                gBox->setFixedWidth(312.5);
                gBox->setCheckable(true);
                gBox->setChecked(lf->getInstallState());

                QLabel *l = new QLabel(lf->getFileName());
                QHBoxLayout *layout = new QHBoxLayout;

                layout->addWidget(l);
                gBox->setLayout(layout);
                scrollAreaLayout->addWidget(gBox);

                connect(gBox, &QGroupBox::toggled, lf, &LocalFile::changeInstallState);
            }
        }


    }

    scrollAreaWidget->setLayout(scrollAreaLayout);
    scrollArea->setWidget(scrollAreaWidget);

    QPushButton *backButton = new QPushButton(tr("Back"));


    QPushButton *startInstallsBtn= new QPushButton(tr("Install"));
    startInstallsBtn->setDefault(true);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(backButton);
    buttonLayout->addWidget(startInstallsBtn);


    mainLayout->addWidget(scrollArea);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch(1);
    setLayout(mainLayout);

    connect(startInstallsBtn, &QPushButton::clicked, this, &SoftwareDownloadPage::startInstalls);
    connect(backButton, &QPushButton::clicked, this, &SoftwareDownloadPage::backToInitPage);





}

void SoftwareDownloadPage::backToInitPage(){


    downloadConfirmed = false;

    for(SoftwareInfo *si: softwareList) {
        if(si->getNetworkReply() && si->downloadInProgress() )
            disconnect(si->getNetworkReply(), &QNetworkReply::downloadProgress, si->getProgressListener(), &ProgressListenner::onDownloadProgress);
    }
    vector<SoftwareInfo*> tmp;
    initPage(tmp, NULL);
}

void SoftwareDownloadPage::finishedDownloading(){
    qDebug() << "finished Downloading in SoftwareDownloadsPage";


    if(readyToInstallButton != nullptr ) {
        readyToInstallButton->setDisabled(false);
        readyToInstallButton->setStyleSheet("QPushButton{background-color:green}");

    }

}

void SoftwareDownloadPage::addFileToInstallList(){
    //show warning label

    WarningBox warning("Are you sure you want to add the selected files to the install queue?");
    warning.setModal(true);
    warning.exec();
    if(warning.actionConfirmed()) {
        localFilesInInstallQ = false;

        for(LocalFile *lf: localFilesMap){

            if(lf->getReadyState()) {
                qDebug() << lf->getFileName()<<" is ready to be installed";
                localFilesInInstallQ = true;
                //break;
            }
        }

    }
}

void SoftwareDownloadPage::startInstalls(){

    for(SoftwareInfo *si: softwareList){
        if(si->getInstallMarked()) startProcess(this,si->getFilePath(), si->getSoftwareName());

    }

    for(LocalFile *lf: localFilesMap){
        if(lf->getInstallState()) startProcess(this, lf->getFilePath(), lf->getFileName());
    }

}




void SoftwareDownloadPage::activeDownloadsPage(){

    if(mainLayout) {
        clearPage(mainLayout);
        clearGlobalWidgets();
    }
    mainLayout = new QVBoxLayout;

    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setFixedSize(QSize(350, 325));
    QWidget *scrollAreaWidget = new QWidget;
    QVBoxLayout *scrollAreaLayout = new QVBoxLayout;

    stopDownloadBtn = new QPushButton(tr("Stop Download"));
    if(!isDownloadInProgress()) stopDownloadBtn->setDisabled(true);

    for(SoftwareInfo *si: softwareList){

        if(si->getDownloadMarked()  || si->downloadInProgress()){

            QNetworkReply *replyPtr = si ->getNetworkReply();

            QString s = "Downloading " + si->getSoftwareName();
            QGroupBox *groupBox = new QGroupBox(s);
            //groupBox->setFixedWidth(312.5);

            if(!si->downloadInProgress()){
                si->setProgressListener(new ProgressListenner);
            } else {
                if(replyPtr && si->getProgressListener())
                    connect(replyPtr, &QNetworkReply::downloadProgress, si->getProgressListener() ,&ProgressListenner::onDownloadProgress);
            }

            if(si->getProgressListener()){
                si->getProgressListener()->pBar = new QProgressBar;
                si->getProgressListener()->pBar->setFixedWidth(300);

                QHBoxLayout *layout = new QHBoxLayout;
                layout->addWidget(si->getProgressListener()->pBar);
                layout->addStretch(1);
                groupBox->setLayout(layout);
                scrollAreaLayout->addWidget(groupBox);
            }



        }
    }
    scrollAreaWidget->setLayout(scrollAreaLayout);
    scrollArea->setWidget(scrollAreaWidget);

    QPushButton *backButton = new QPushButton(tr("Back"));




    QPalette pal = stopDownloadBtn->palette();
    pal.setColor(QPalette::Button, QColor(Qt::red));
    stopDownloadBtn->setAutoFillBackground(true);
    stopDownloadBtn->setPalette(pal);
    stopDownloadBtn->update();

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(backButton);
    buttonLayout->addWidget(stopDownloadBtn);


    mainLayout->addWidget(scrollArea);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch(1);
    setLayout(mainLayout);

    connect(stopDownloadBtn, &QPushButton::clicked, this, &SoftwareDownloadPage::stopDownloads);
    connect(backButton, &QPushButton::clicked, this, &SoftwareDownloadPage::backToInitPage);

}

void SoftwareDownloadPage::startDownloads()
{
    for(SoftwareInfo *si : softwareList){

        QString fileName = si->getSoftwareName();
        if(si->getVersionSelect64()) fileName += "_x64";
        fileName += ".exe";
        auto it = localFilesMap.find(fileName);

        if(si->getDownloadMarked() && it == localFilesMap.end()) {

            if(si->getVersionSelect32()) network->get(si->get32BitURL());
            if(si->getVersionSelect64()) network->get(si->get64BitURL());

            QNetworkReply *reply = network->getLastReply();
            si->setNetworkReply(reply);
            si->downloadStart();


            if(si->getProgressListener()) connect(reply, &QNetworkReply::downloadProgress, si->getProgressListener(), &ProgressListenner::onDownloadProgress);
            connect(reply, &QNetworkReply::finished, this, &SoftwareDownloadPage::finishedDownloading);
            connect(reply, &QNetworkReply::finished, si, &SoftwareInfo::finishedDownload);

        } else if (si->getDownloadMarked() && it != localFilesMap.end()){

            ProgressListenner *plPtr = si->getProgressListener();
            if(plPtr && plPtr->pBar) {
                plPtr->pBar->setMinimum(0);
                plPtr->pBar->setMaximum(1);
                plPtr->pBar->setValue(1);
            }
            si->downloadStart();
            si->finishedDownload();
            si->setFilePath(it.value()->getFilePath());
            localFilesMap.erase(it);
        }
    }

}

void SoftwareDownloadPage::stopDownloads()
{
    WarningBox warningbox("Are you sure you want to cancel ALL downloads?");
    warningbox.setModal(true);
    warningbox.exec();
    if(warningbox.actionConfirmed()) {

        for(SoftwareInfo *si: softwareList) si->stopDownload();

        //clearPage(mainLayout);
        vector<SoftwareInfo*> a;
        initPage(a, NULL);

    }

}

bool SoftwareDownloadPage::isDownloadInProgress(){

    for(SoftwareInfo *si: softwareList){
        if(!si->getProgressListener()) continue;
        if(si->getProgressListener()->_lastKnownReceived < si->getProgressListener()->_lastKnownTotal) return true;
    }
    return false;
}

bool SoftwareDownloadPage::isReadyForInstall(){
    if(localFilesInInstallQ) return true;
    for(SoftwareInfo *si: softwareList) if(si->getInstallReadyState()) return true;
    return false;
}

void SoftwareDownloadPage::clearGlobalWidgets(){
    viewDownloadProgButton = nullptr;
    readyToInstallButton = nullptr;
    stopDownloadBtn = nullptr;
}



ConfigurationPage::ConfigurationPage(QWidget *parent) : QWidget(parent){
    mainLayout = new QVBoxLayout;
    regHan.setDefaultValues();


    policyTree = buildPolicyTree();
    policyTree->resizeColumnToContents(0);
    policyTree->setModel(model);

    QPushButton *restoreDefaultBtn = new QPushButton("Restore Default");
    QPushButton *applyBtn = new QPushButton("Apply");

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addWidget(restoreDefaultBtn);
    btnLayout->addWidget(applyBtn);


    mainLayout->addWidget(policyTree);
    mainLayout->addItem(btnLayout);
    setLayout(mainLayout);

    connect(policyTree, &QTreeView::doubleClicked, this, &ConfigurationPage::itemDoubleClicked);
    connect(restoreDefaultBtn, &QPushButton::clicked, this, &ConfigurationPage::restoreDefault);
    connect(applyBtn, &QPushButton::clicked, this, &ConfigurationPage::applySettings);


}

QTreeView* ConfigurationPage::buildPolicyTree(){
    model = new QStandardItemModel;
    //model->setHorizontalHeaderLabels({"Policy","Value"});
    QStandardItem *policyHeaderItem = new QStandardItem("Policy");
    QStandardItem *valueHeaderItem = new QStandardItem("Value");
    model->setHorizontalHeaderItem(0,policyHeaderItem);
    model->setHorizontalHeaderItem(1, valueHeaderItem);


    recommendedPolicies = new QStandardItem("Recommended Policies");
    recommendedPolicies->setColumnCount(2);
    recommendedPolicies->setEditable(false);

    controlPanelPolicies = new QStandardItem("Control Panel");
    controlPanelPolicies->setEditable(false);

    systemPolicies = new QStandardItem("System");
    systemPolicies->setEditable(false);

    personalizationPolicies = new QStandardItem("Personalization");
    personalizationPolicies->setEditable(false);

    populatePolicies();



    model->appendRow(recommendedPolicies);
    model->appendRow(controlPanelPolicies);
    model->appendRow(systemPolicies);
    model->appendRow(personalizationPolicies);


    QTreeView *tv = new QTreeView(this);
    tv->setModel(model);
    return tv;

}

void ConfigurationPage::populatePolicies(){

    QList<QStandardItem*> row;

    QStandardItem *autoStartProgram = new QStandardItem("Autostart a Program");
    QStandardItem *autoStartProgramRegVal = new QStandardItem(regHan.getCurrRegDataVal("CashRegisterExpressRun"));
    QStandardItem *autoStartProgramRegKeyName = new QStandardItem("CashRegisterExpressRun");
    QStandardItem *autoStartProgramDataType = new QStandardItem("Path");

    autoStartProgram->setCheckable(true);
    autoStartProgram->setCheckState(Qt::Checked);
    autoStartProgram->setEditable(false);
    autoStartProgramRegVal->setEditable(false);

    row.clear();
    row.append(autoStartProgram);
    row.append(autoStartProgramRegVal);
    row.append(autoStartProgramRegKeyName);
    row.append(autoStartProgramDataType);
    recommendedPolicies->appendRow(row);
    systemPolicies->appendRow(row);


    QStandardItem *noControlPanel = new QStandardItem("Prohibit access to Control Panel and PC Settings");
    QStandardItem *noControlPanelRegVal = new QStandardItem(regHan.getCurrRegDataVal("NoControlPanel"));
    QStandardItem *noControlPanelRegKeyName = new QStandardItem("NoControlPanel");
    QStandardItem *noControlPanelDataType = new QStandardItem("");

    noControlPanel->setCheckable(true);
    noControlPanel->setCheckState(Qt::Checked);
    noControlPanel->setEditable(false);
    noControlPanelRegVal->setEditable(false);

    row.clear();
    row.append(noControlPanel);
    row.append(noControlPanelRegVal);
    row.append(noControlPanelRegKeyName);
    row.append(noControlPanelDataType);
    recommendedPolicies->appendRow(row);
    systemPolicies->appendRow(row);
    controlPanelPolicies->appendRow(row);



    QStandardItem *hidePowerOptions = new QStandardItem("Remove and prevent access to the Shut Down, Restart, Sleep, and Hibernate commandss");
    QStandardItem *hidePowerOptionsRegVal = new QStandardItem(regHan.getCurrRegDataVal("HidePowerOptions"));
    QStandardItem *hidePowerOptionsRegKeyName = new QStandardItem("HidePowerOptions");
    QStandardItem *hidePowerOptionsDataType = new QStandardItem("");

    hidePowerOptions->setCheckable(true);
    hidePowerOptions->setCheckState(Qt::Checked);
    hidePowerOptions->setEditable(false);
    hidePowerOptionsRegVal->setEditable(false);

    row.clear();
    row.append(hidePowerOptions);
    row.append(hidePowerOptionsRegVal);
    row.append(hidePowerOptionsRegKeyName);
    row.append(hidePowerOptionsDataType);
    recommendedPolicies->appendRow(row);
    systemPolicies->appendRow(row);


    QStandardItem *noLogoff = new QStandardItem("Remove logoff");
    QStandardItem *noLogoffRegVal = new QStandardItem(regHan.getCurrRegDataVal("Nologoff"));
    QStandardItem *noLogoffRegKeyName = new QStandardItem("Nologoff");
    QStandardItem *noLogoffDataType = new QStandardItem("");

    noLogoff->setCheckable(true);
    noLogoff->setCheckState(Qt::Checked);
    noLogoff->setEditable(false);
    noLogoffRegVal->setEditable(false);

    row.clear();
    row.append(noLogoff);
    row.append(noLogoffRegVal);
    row.append(noLogoffRegKeyName);
    row.append(noLogoffDataType);
    recommendedPolicies->appendRow(row);
    systemPolicies->appendRow(row);



    QStandardItem *disableCMD = new QStandardItem("Prevent access to the command prompt");
    QStandardItem *disableCMDRegVal = new QStandardItem(regHan.getCurrRegDataVal("DisableCMD"));
    QStandardItem *disableCMDRegKeyName = new QStandardItem("DisableCMD");
    QStandardItem *disableCMDDataType = new QStandardItem("");

    disableCMD->setCheckable(true);
    disableCMD->setCheckState(Qt::Checked);
    disableCMD->setEditable(false);
    disableCMDRegVal->setEditable(false);

    row.clear();
    row.append(disableCMD);
    row.append(disableCMDRegVal);
    row.append(disableCMDRegKeyName);
    row.append(disableCMDDataType);
    recommendedPolicies->appendRow(row);
    systemPolicies->appendRow(row);



    QStandardItem *disabletaskMgr = new QStandardItem("Remove Task Manager");
    QStandardItem *disabletaskMgrRegVal = new QStandardItem(regHan.getCurrRegDataVal("DisabletaskMgr"));
    QStandardItem *disabletaskMgrRegKeyName = new QStandardItem("DisabletaskMgr");
    QStandardItem *disabletaskMgrDataType = new QStandardItem("");

    disabletaskMgr->setCheckable(true);
    disabletaskMgr->setCheckState(Qt::Checked);
    disabletaskMgr->setEditable(false);
    disabletaskMgrRegVal->setEditable(false);

    row.clear();
    row.append(disabletaskMgr);
    row.append(disabletaskMgrRegVal);
    row.append(disabletaskMgrRegKeyName);
    row.append(disabletaskMgrDataType);
    recommendedPolicies->appendRow(row);
    systemPolicies->appendRow(row);




    QStandardItem *disablelockWorkstation = new QStandardItem("Remove Lock Computer");
    QStandardItem *disablelockWorkstationRegVal = new QStandardItem(regHan.getCurrRegDataVal("DisablelockWorkstation"));
    QStandardItem *disablelockWorkstationRegKeyName = new QStandardItem("DisablelockWorkstation");
    QStandardItem *disablelockWorkstationDataType = new QStandardItem("");

    disablelockWorkstation->setCheckable(true);
    disablelockWorkstation->setCheckState(Qt::Checked);
    disablelockWorkstation->setEditable(false);
    disablelockWorkstationRegVal->setEditable(false);

    row.clear();
    row.append(disablelockWorkstation);
    row.append(disablelockWorkstationRegVal);
    row.append(disablelockWorkstationRegKeyName);
    row.append(disablelockWorkstationDataType);
    recommendedPolicies->appendRow(row);
    systemPolicies->appendRow(row);



    QStandardItem *removeChangePsswd = new QStandardItem("Remove Change Passoword");
    QStandardItem *removeChangePsswdRegVal = new QStandardItem(regHan.getCurrRegDataVal("Disablechangepassword"));
    QStandardItem *removeChangePsswdRegKeyName = new QStandardItem("Disablechangepassword");
    QStandardItem *removeChangePsswdDataType = new QStandardItem("");

    removeChangePsswd->setCheckable(true);
    removeChangePsswd->setCheckState(Qt::Checked);
    removeChangePsswd->setEditable(false);
    removeChangePsswdRegVal->setEditable(false);

    row.clear();
    row.append(removeChangePsswd);
    row.append(removeChangePsswdRegVal);
    row.append(removeChangePsswdRegKeyName);
    row.append(removeChangePsswdDataType);
    recommendedPolicies->appendRow(row);
    systemPolicies->appendRow(row);
    controlPanelPolicies->appendRow(row);



    QStandardItem *noAutoUpdate = new QStandardItem("Remove Windows automatic updates");
    QStandardItem *noAutoUpdateRegVal = new QStandardItem(regHan.getCurrRegDataVal("NoAutoUpdate"));
    QStandardItem *noAutoUpdateRegKeyName = new QStandardItem("NoAutoUpdate");
    QStandardItem *noAutoUpdateDataType = new QStandardItem("");

    noAutoUpdate->setCheckable(true);
    noAutoUpdate->setCheckState(Qt::Checked);
    noAutoUpdate->setEditable(false);
    noAutoUpdateRegVal->setEditable(false);

    row.clear();
    row.append(noAutoUpdate);
    row.append(noAutoUpdateRegVal);
    row.append(noAutoUpdateRegKeyName);
    row.append(noAutoUpdateDataType);
    recommendedPolicies->appendRow(row);
    systemPolicies->appendRow(row);
    controlPanelPolicies->appendRow(row);



    QStandardItem *taskbarNoNotification = new QStandardItem("Turn off all balloon notifications");
    QStandardItem *taskbarNoNotificationRegVal = new QStandardItem(regHan.getCurrRegDataVal("TaskbarNoNotification"));
    QStandardItem *taskbarNoNotificationRegKeyName = new QStandardItem("TaskbarNoNotification");
    QStandardItem *taskbarNoNotificationDataType = new QStandardItem("");

    taskbarNoNotification->setCheckable(true);
    taskbarNoNotification->setCheckState(Qt::Checked);
    taskbarNoNotification->setEditable(false);
    taskbarNoNotificationRegVal->setEditable(false);

    row.clear();
    row.append(taskbarNoNotification);
    row.append(taskbarNoNotificationRegVal);
    row.append(taskbarNoNotificationRegKeyName);
    row.append(taskbarNoNotificationDataType);
    recommendedPolicies->appendRow(row);
    systemPolicies->appendRow(row);





    QStandardItem *noballoonFeatureAds = new QStandardItem("Turn off all Balloon Featured Advertisements");
    QStandardItem *noballoonFeatureAdsRegVal = new QStandardItem(regHan.getCurrRegDataVal("NoballoonFeatureAdvertisements"));
    QStandardItem *noballoonFeatureAdsRegKeyName = new QStandardItem("NoballoonFeatureAdvertisements");
    QStandardItem *noballoonFeatureAdsDataType = new QStandardItem("");

    noballoonFeatureAds->setCheckable(true);
    noballoonFeatureAds->setCheckState(Qt::Checked);
    noballoonFeatureAds->setEditable(false);
    noballoonFeatureAdsRegVal->setEditable(false);

    row.clear();
    row.append(noballoonFeatureAds);
    row.append(noballoonFeatureAdsRegVal);
    row.append(noballoonFeatureAdsRegKeyName);
    row.append(noballoonFeatureAdsDataType);
    recommendedPolicies->appendRow(row);
    systemPolicies->appendRow(row);




    QStandardItem *noTileApplicationNoti = new QStandardItem("Turn off tile notifications");
    QStandardItem *noTileApplicationNotiRegVal = new QStandardItem(regHan.getCurrRegDataVal("NoTileApplicationNotification"));
    QStandardItem *noTileApplicationNotiRegKeyName = new QStandardItem("NoTileApplicationNotification");
    QStandardItem *noTileApplicationNotiDataType = new QStandardItem("");

    noTileApplicationNoti->setCheckable(true);
    noTileApplicationNoti->setCheckState(Qt::Checked);
    noTileApplicationNoti->setEditable(false);
    noTileApplicationNotiRegVal->setEditable(false);

    row.clear();
    row.append(noTileApplicationNoti);
    row.append(noTileApplicationNotiRegVal);
    row.append(noTileApplicationNotiRegKeyName);
    row.append(noTileApplicationNotiDataType);
    recommendedPolicies->appendRow(row);
    systemPolicies->appendRow(row);



    QStandardItem *NoCloudAppNoti = new QStandardItem("Turn off notifications network usage");
    QStandardItem *NoCloudAppNotiRegVal = new QStandardItem(regHan.getCurrRegDataVal("NoCloudApplicationNotification"));
    QStandardItem *NoCloudAppNotiRegKeyName = new QStandardItem("NoCloudApplicationNotification");
    QStandardItem *NoCloudAppNotiDataType = new QStandardItem("");

    NoCloudAppNoti->setCheckable(true);
    NoCloudAppNoti->setCheckState(Qt::Checked);
    NoCloudAppNoti->setEditable(false);
    NoCloudAppNotiRegVal->setEditable(false);

    row.clear();
    row.append(NoCloudAppNoti);
    row.append(NoCloudAppNotiRegVal);
    row.append(NoCloudAppNotiRegKeyName);
    row.append(NoCloudAppNotiDataType);
    recommendedPolicies->appendRow(row);
    systemPolicies->appendRow(row);



    QStandardItem *lockTaskbar = new QStandardItem("Lock the taskBar");
    QStandardItem *lockTaskbarRegVal = new QStandardItem(regHan.getCurrRegDataVal("LockTaskbar"));
    QStandardItem *lockTaskbarRegKeyName = new QStandardItem("LockTaskbar");
    QStandardItem *lockTaskbarDataType = new QStandardItem("");

    lockTaskbar->setCheckable(true);
    lockTaskbar->setCheckState(Qt::Checked);
    lockTaskbar->setEditable(false);
    lockTaskbarRegVal->setEditable(false);

    row.clear();
    row.append(lockTaskbar);
    row.append(lockTaskbarRegVal);
    row.append(lockTaskbarRegKeyName);
    row.append(lockTaskbarDataType);
    recommendedPolicies->appendRow(row);
    systemPolicies->appendRow(row);
    controlPanelPolicies->appendRow(row);



    QStandardItem *noMinimizingShortcuts = new QStandardItem("Turn off Aero Shake window minimizing mouse gesture");
    QStandardItem *noMinimizingShortcutsRegVal = new QStandardItem(regHan.getCurrRegDataVal("NoWindowMinimizingShortcuts"));
    QStandardItem *noMinimizingShortcutsRegKeyName = new QStandardItem("NoWindowMinimizingShortcuts");
    QStandardItem *noMinimizingShortcutsDataType = new QStandardItem("");

    noMinimizingShortcuts->setCheckable(true);
    noMinimizingShortcuts->setCheckState(Qt::Checked);
    noMinimizingShortcuts->setEditable(false);
    noMinimizingShortcutsRegVal->setEditable(false);

    row.clear();
    row.append(noMinimizingShortcuts);
    row.append(noMinimizingShortcutsRegVal);
    row.append(noMinimizingShortcutsRegKeyName);
    row.append(noMinimizingShortcutsDataType);
    recommendedPolicies->appendRow(row);
    personalizationPolicies->appendRow(row);




    QStandardItem *noChangestartMenu = new QStandardItem("Prevent users from customizing their start screen");
    QStandardItem *noChangestartMenuRegVal = new QStandardItem(regHan.getCurrRegDataVal("NoChangestartMenu"));
    QStandardItem *noChangestartMenuRegKeyName = new QStandardItem("NoChangestartMenu");
    QStandardItem *noChangestartMenuDataType = new QStandardItem("");

    noChangestartMenu->setCheckable(true);
    noChangestartMenu->setEditable(false);
    noChangestartMenuRegVal->setEditable(false);

    row.clear();
    row.append(noChangestartMenu);
    row.append(noChangestartMenuRegVal);
    row.append(noChangestartMenuRegKeyName);
    row.append(noChangestartMenuDataType);
    personalizationPolicies->appendRow(row);




    QStandardItem *noAddRemoveToolbar = new QStandardItem("Prevent users from adding or removing toolbars");
    QStandardItem *noAddRemoveToolbarRegVal = new QStandardItem(regHan.getCurrRegDataVal("TaskbarNoAddRemoveToolbar"));
    QStandardItem *noAddRemoveToolbarRegKeyName = new QStandardItem("TaskbarNoAddRemoveToolbar");
    QStandardItem *noAddRemoveToolbarDataType = new QStandardItem("");

    noAddRemoveToolbar->setCheckable(true);
    noAddRemoveToolbar->setEditable(false);
    noAddRemoveToolbarRegVal->setEditable(false);

    row.clear();
    row.append(noAddRemoveToolbar);
    row.append(noAddRemoveToolbarRegVal);
    row.append(noAddRemoveToolbarRegKeyName);
    row.append(noAddRemoveToolbarDataType);
    personalizationPolicies->appendRow(row);




    QStandardItem *noSetTaskbar = new QStandardItem("Prevent changes to Taskbar and start menu Settings");
    QStandardItem *noSetTaskbarRegVal = new QStandardItem(regHan.getCurrRegDataVal("NoSetTaskbar"));
    QStandardItem *noSetTaskbarRegKeyName = new QStandardItem("NoSetTaskbar");
    QStandardItem *noSetTaskbarDataType = new QStandardItem("");

    noSetTaskbar->setCheckable(true);
    noSetTaskbar->setEditable(false);
    noSetTaskbarRegVal->setEditable(false);

    row.clear();
    row.append(noSetTaskbar);
    row.append(noSetTaskbarRegVal);
    row.append(noSetTaskbarRegKeyName);
    row.append(noSetTaskbarDataType);
    personalizationPolicies->appendRow(row);



    QStandardItem *taskbarLockAll = new QStandardItem("Lock all taskbar settings");
    QStandardItem *taskbarLockAllRegVal = new QStandardItem(regHan.getCurrRegDataVal("taskbarLockAll"));
    QStandardItem *taskbarLockAllRegKeyName = new QStandardItem("taskbarLockAll");
    QStandardItem *taskbarLockAllDataType = new QStandardItem("");

    taskbarLockAll->setCheckable(true);
    taskbarLockAll->setEditable(false);
    taskbarLockAllRegVal->setEditable(false);

    row.clear();
    row.append(taskbarLockAll);
    row.append(taskbarLockAllRegVal);
    row.append(taskbarLockAllRegKeyName);
    row.append(taskbarLockAllDataType);
    personalizationPolicies->appendRow(row);



    QStandardItem *noMovingToolbars = new QStandardItem("Prohibit adjusting desktop toolbars");
    QStandardItem *noMovingToolbarsRegVal = new QStandardItem(regHan.getCurrRegDataVal("NoMovingBands"));
    QStandardItem *noMovingToolbarsRegKeyName = new QStandardItem("NoMovingBands");
    QStandardItem *noMovingToolbarsDataType = new QStandardItem("");

    noMovingToolbars->setCheckable(true);
    noMovingToolbars->setEditable(false);
    noMovingToolbarsRegVal->setEditable(false);

    row.clear();
    row.append(noMovingToolbars);
    row.append(noMovingToolbarsRegVal);
    row.append(noMovingToolbarsRegKeyName);
    row.append(noMovingToolbarsDataType);
    personalizationPolicies->appendRow(row);




    QStandardItem *noChangingWallPaper = new QStandardItem("Prevent changing desktop background/wallpaper");
    QStandardItem *noChangingWallPaperRegVal = new QStandardItem(regHan.getCurrRegDataVal("NoChangingWallPaper"));
    QStandardItem *noChangingWallPaperRegKeyName = new QStandardItem("NoChangingWallPaper");
    QStandardItem *noChangingWallPaperDataType = new QStandardItem("");

    noChangingWallPaper->setCheckable(true);
    noChangingWallPaper->setEditable(false);
    noChangingWallPaperRegVal->setEditable(false);

    row.clear();
    row.append(noChangingWallPaper);
    row.append(noChangingWallPaperRegVal);
    row.append(noChangingWallPaperRegKeyName);
    row.append(noChangingWallPaperDataType);
    personalizationPolicies->appendRow(row);



    QStandardItem *noChanginglockscreen = new QStandardItem("Prevent changing lock screen and logon image");
    QStandardItem *noChanginglockscreenRegVal = new QStandardItem(regHan.getCurrRegDataVal("NoChanginglockscreen"));
    QStandardItem *noChanginglockscreenRegKeyName = new QStandardItem("NoChanginglockscreen");
    QStandardItem *noChanginglockscreenDataType = new QStandardItem("");

    noChanginglockscreen->setCheckable(true);
    noChanginglockscreen->setEditable(false);
    noChanginglockscreenRegVal->setEditable(false);

    row.clear();
    row.append(noChanginglockscreen);
    row.append(noChanginglockscreenRegVal);
    row.append(noChanginglockscreenRegKeyName);
    row.append(noChanginglockscreenDataType);
    personalizationPolicies->appendRow(row);




    QStandardItem *nolockscreen = new QStandardItem("Do not display the lock screen");
    QStandardItem *nolockscreenRegVal = new QStandardItem(regHan.getCurrRegDataVal("Nolockscreen"));
    QStandardItem *nolockscreenRegKeyName = new QStandardItem("Nolockscreen");
    QStandardItem *nolockscreenDataType = new QStandardItem("");

    nolockscreen->setCheckable(true);
    nolockscreen->setEditable(false);
    nolockscreenRegVal->setEditable(false);

    row.clear();
    row.append(nolockscreen);
    row.append(nolockscreenRegVal);
    row.append(nolockscreenRegKeyName);
    row.append(nolockscreenDataType);
    personalizationPolicies->appendRow(row);
    systemPolicies->appendRow(row);



    QStandardItem *useDefaultTile = new QStandardItem("Apply the default account picture to all users");
    QStandardItem *useDefaultTileRegVal = new QStandardItem(regHan.getCurrRegDataVal("UseDefaultTile"));
    QStandardItem *useDefaultTileRegKeyName = new QStandardItem("UseDefaultTile");
    QStandardItem *useDefaultTileDataType = new QStandardItem("");

    useDefaultTile->setCheckable(true);
    useDefaultTile->setEditable(false);
    useDefaultTileRegVal->setEditable(false);

    row.clear();
    row.append(useDefaultTile);
    row.append(useDefaultTileRegVal);
    row.append(useDefaultTileRegKeyName);
    row.append(useDefaultTileDataType);
    personalizationPolicies->appendRow(row);
    systemPolicies->appendRow(row);


}

void ConfigurationPage::itemDoubleClicked(const QModelIndex &index){
    qDebug() << "Double Clicked" << index.data().toString() << "row" << index.row() << "col" << index.column();
    qDebug() << "Parent" << index.parent().data().toString() << "row"<< index.parent().row() << "col" << index.parent().column();

    if(index.column() == 0) return;




    QStandardItemModel *model = (QStandardItemModel*) policyTree->model();
    QStandardItem *parentItem = model->item(index.parent().row(), 0);

    QStandardItem *childValueItem = parentItem->child(index.row(),index.column());
    QString regKeyName = parentItem->child(index.row(), index.column()+1)->text();
    QString dataType = parentItem->child(index.row(), index.column()+2)->text();


    if(parentItem->child(index.row(),0)->checkState() == Qt::Checked){

        QMessageBox msgBox;
        int msgBoxReturn;
        bool ok = false;
        QString newInput = "";


        if(dataType == "Path"){
            newInput = QFileDialog::getOpenFileName(this, "Select Executable",QDir::homePath(),"Windows Executable Files (*.EXE, *.exe, *.DLL, *.dll)");

            if(newInput.isEmpty() || newInput.isNull()) return;
            ok = true;

        } else if(dataType == "Text"){
            newInput =  QInputDialog::getText(this,"Edit Message","Enter New Message", QLineEdit::Normal,"", &ok);
        }

        if(ok && !newInput.isEmpty()){
            msgBox.setText("Modifiying Value");
            msgBox.setInformativeText("Are you sure you want to modify this value to '"+newInput+"'");
            msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.setModal(true);
            msgBoxReturn = msgBox.exec();

            if(msgBoxReturn == QMessageBox::Ok) childValueItem->setText(newInput);
        }

    }

}

void ConfigurationPage::restoreDefault(){
    regHan.setDefaultValues();
    for(int row = 0; row < recommendedPolicies->rowCount(); ++row){
        QString policyName = recommendedPolicies->child(row,2)->text();
        recommendedPolicies->child(row,1)->setText(regHan.getCurrRegDataVal(policyName));
    }

    /*for(int row = 0; row < controlPanelPolicies->rowCount(); ++row){
        QString policyName = controlPanelPolicies->child(row,2)->text();
        controlPanelPolicies->child(row,1)->setText(regHan.getCurrRegDataVal(policyName));
    }

    for(int row = 0; row < systemPolicies->rowCount(); ++row){
        QString policyName = systemPolicies->child(row,2)->text();
        systemPolicies->child(row,1)->setText(regHan.getCurrRegDataVal(policyName));
    }

    for(int row = 0; row < personalizationPolicies->rowCount(); ++row){
        QString policyName = personalizationPolicies->child(row,2)->text();
        personalizationPolicies->child(row,1)->setText(regHan.getCurrRegDataVal(policyName));
    }*/
}

void ConfigurationPage::applySettings(){
    for(int row = 0; row < recommendedPolicies->rowCount(); ++row){
        QString policyName = recommendedPolicies->child(row, 2)->text();
        QString type = recommendedPolicies->child(row, 3)->text();
        if(recommendedPolicies->child(row,0)->checkState() == Qt::Checked){

            if(type == "Path" || type == "Text"){
                QString pathOrText = recommendedPolicies->child(row, 1)->text();
                regHan.setPolicyVal(policyName, pathOrText);
            } else {
                regHan.setPolicyVal(policyName, 1);
            }

        } else {
            if(type != "Path" && type != "Text") regHan.setPolicyVal(policyName, 0);
        }
        recommendedPolicies->child(row,1)->setText(regHan.getCurrRegDataVal(policyName));
    }


    /*for(int row = 0; row < controlPanelPolicies->rowCount(); ++row){
        QString policyName = controlPanelPolicies->child(row, 2)->text();
        QString type = controlPanelPolicies->child(row, 3)->text();
        if(controlPanelPolicies->child(row,0)->checkState() == Qt::Checked){

            if(type == "Path" || type == "Text"){
                QString pathOrText = controlPanelPolicies->child(row, 1)->text();
                regHan.setPolicyVal(policyName, pathOrText);
            } else {
                regHan.setPolicyVal(policyName, 1);
            }

        } else {
            if(type != "Path" && type != "Text") regHan.setPolicyVal(policyName, 0);
        }
        controlPanelPolicies->child(row,1)->setText(regHan.getCurrRegDataVal(policyName));
    }


    for(int row = 0; row < systemPolicies->rowCount(); ++row){
        QString policyName = systemPolicies->child(row, 2)->text();
        QString type = systemPolicies->child(row, 3)->text();
        if(systemPolicies->child(row,0)->checkState() == Qt::Checked){

            if(type == "Path" || type == "Text"){
                QString pathOrText = systemPolicies->child(row, 1)->text();
                regHan.setPolicyVal(policyName, pathOrText);
            } else {
                regHan.setPolicyVal(policyName, 1);
            }

        } else {
            if(type != "Path" && type != "Text") regHan.setPolicyVal(policyName, 0);
        }
        systemPolicies->child(row,1)->setText(regHan.getCurrRegDataVal(policyName));
    }

    for(int row = 0; row < personalizationPolicies->rowCount(); ++row){
        QString policyName = personalizationPolicies->child(row, 2)->text();
        QString type = personalizationPolicies->child(row, 3)->text();
        if(personalizationPolicies->child(row,0)->checkState() == Qt::Checked){

            if(type == "Path" || type == "Text"){
                QString pathOrText = personalizationPolicies->child(row, 1)->text();
                regHan.setPolicyVal(policyName, pathOrText);
            } else {
                regHan.setPolicyVal(policyName, 1);
            }

        } else {
            if(type != "Path" && type != "Text") regHan.setPolicyVal(policyName, 0);
        }
        personalizationPolicies->child(row,1)->setText(regHan.getCurrRegDataVal(policyName));
    }*/

}


void clearPage(QLayout * layout) {
   if (! layout) return;

    while (auto item = layout->takeAt(0)) {
        auto widget = item->widget();
        delete item->widget();
        widget = nullptr;
        clearPage(item->layout());
   }
   delete layout;
}

void startProcess(QObject *parent, QString programPath, QString fileName ) {

    QProcess *process = new QProcess(parent);
    process->start(programPath);

    if(!process->waitForStarted()) {
        WarningBox warning("Could not start " + fileName);
        warning.setModal(true);
        warning.exec();
    }
}

