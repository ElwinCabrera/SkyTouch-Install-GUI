

#include "pages.h"
#include "warningbox.h"



SoftwareDownloadPage::SoftwareDownloadPage(QWidget *parent) : QWidget(parent){
    downloadConfirmed = false;
    readyToInstall = false;
    localFilesInInstallQ = false;


}

void SoftwareDownloadPage::initPage(vector<SoftwareInfo*> &softwareL, Network *network)
{
    if(network) this->network = network;
    if(!softwareL.empty()) this->softwareList = softwareL;



    QScrollArea *scrollArea = new QScrollArea;

    scrollArea->setFixedSize(QSize(350, 325));

    mainLayout = new QVBoxLayout;
    QWidget *scrollAreaWidget = new QWidget;
    QVBoxLayout *scrollAreaLayout = new QVBoxLayout;

    for(SoftwareInfo *si :  softwareList){
        QGroupBox *downloadGroup = new QGroupBox("Download "+si->getSoftwareName());
        downloadGroup->setFixedWidth(312.5);
        downloadGroup->setCheckable(true);
        downloadGroup->blockSignals(true);
        downloadGroup->setChecked(si->getDownloadMarked());

        if(si->downloadInProgress() || si->getDownloadSuccess()){
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

        if( si->get32BitURL() == "") downloadRadioBtn->setCheckable(false);
        if( si->get64BitURL() == "") download64RadioBtn->setCheckable(false);
        downloadRadioBtn->setChecked(si->getVersionSelect32());
        download64RadioBtn->setChecked(si->getVersionSelect64());

        connect(downloadGroup, &QGroupBox::toggled, si, &SoftwareInfo::onDownloadCheckBoxClicked);
        connect(download64RadioBtn, &QRadioButton::toggled,si, &SoftwareInfo::onVersionSelect);

        //mainLayout->addWidget(downloadGroup);
        scrollAreaLayout->addWidget(downloadGroup);

    }
    scrollAreaWidget->setLayout(scrollAreaLayout);
    scrollArea->setWidget(scrollAreaWidget);



    QPushButton *searchForLocalButton = new QPushButton(tr("Search For Local Files"));


    viewDownloadProgButton = new QPushButton(tr("Show Downlaod Progress"));




    readyToInstallButton = new QPushButton(tr("Ready to Install"));

    if(!isReadyForInstall()) readyToInstallButton->setDisabled(true);
    else readyToInstallButton->setStyleSheet("QPushButton{background-color:green;");



    QPushButton *downloadButton = new QPushButton(tr("Start Download(s)"));
    downloadButton->setDefault(true);



    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(searchForLocalButton);
    buttonsLayout->addWidget(viewDownloadProgButton);




    //
    mainLayout->addWidget(scrollArea);
    mainLayout->addLayout(buttonsLayout);
    mainLayout->addWidget(readyToInstallButton);
    mainLayout->addWidget(downloadButton);

    mainLayout->addStretch(1);
   // mainLayout->addSpacing(200);
    setLayout(mainLayout);

    connect(downloadButton, &QPushButton::clicked, this, &SoftwareDownloadPage::downloadButtonCliked);
    connect(searchForLocalButton, &QPushButton::clicked, this , &SoftwareDownloadPage::searchForLocalFiles);
    connect(viewDownloadProgButton, &QPushButton::clicked, this, &SoftwareDownloadPage::viewDownloadProg);
    connect(readyToInstallButton, &QPushButton::clicked, this, &SoftwareDownloadPage::showReadyToInstall);


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
            showDownloadProgress();
            startDownloads();
            stopDownloadBtn->setDisabled(false);

            //if all downloads are done then return to installation screen
        } else qDebug() << "download  NOT confirmed";

    }
}

void SoftwareDownloadPage::searchForLocalFiles(){

    if(!mainLayout) {
        qDebug() << "in function searchForLocalFiles: mainLayout is NULL";
        return;
    }
    if(mainLayout) clearWidgetsAndLayouts(mainLayout);
    mainLayout = new QVBoxLayout;

    disconnect(this,0,0,0);


    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setFixedSize(QSize(350, 325));
    QWidget *scrollAreaWidget = new QWidget;
    QVBoxLayout *scrollAreaLayout = new QVBoxLayout;


    QSet<QString> visitedFilesSet;

    QDirIterator dirIt("/home/elwin/Downloads",QDirIterator::Subdirectories);
    while (dirIt.hasNext()) {
        dirIt.next();
        if (QFileInfo(dirIt.filePath()).isFile()) {
            if(QFileInfo(dirIt.filePath()).suffix() == "exe") {

                qDebug()<< dirIt.filePath();

                QMap<QString,LocalFile*>::iterator it = localFilesMap.find(dirIt.fileName());

                LocalFile *lf = nullptr;
                if(it == localFilesMap.end()) {

                    lf = new LocalFile(dirIt.fileName(), dirIt.filePath(),false);

                    localFilesMap.insert(dirIt.fileName(),lf);

                } else lf = it.value();

                if(visitedFilesSet.find(dirIt.fileName()) == visitedFilesSet.end()) visitedFilesSet.insert(dirIt.fileName());
                else continue;



                QGroupBox *gBox= new QGroupBox;
                gBox->setFixedWidth(312.5);

                gBox->setCheckable(true);
                if(lf->getInstallState()){
                    gBox->setTitle("Marked For Install");
                }
                if(lf) gBox->setChecked(lf->getReadyState() || lf->getInstallState());
                else gBox->setChecked(false);

                QLabel *label = new QLabel(dirIt.fileName());
                QHBoxLayout *layout = new QHBoxLayout;

                layout->addWidget(label);
                //layout->addStretch(1);
                gBox->setLayout(layout);
                scrollAreaLayout->addWidget(gBox);

                if(lf) connect(gBox, &QGroupBox::clicked, lf, &LocalFile::changeReadyState);

            }


        }
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
    connect(backButton, &QPushButton::clicked, this, &SoftwareDownloadPage::backToSoftwareList);


}

void SoftwareDownloadPage::viewDownloadProg(){
    showDownloadProgress();
}

void SoftwareDownloadPage::showReadyToInstall(){
    if(mainLayout) clearWidgetsAndLayouts(mainLayout);
    else { qDebug() << "mainLayout NOT null: in showReadyToInstall"; return; }

    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setFixedSize(QSize(350, 325));
    QWidget *scrollAreaWidget = new QWidget;
    QVBoxLayout *scrollAreaLayout = new QVBoxLayout;

    for(SoftwareInfo *si: softwareList){
        if(si->getInstallReadyState()){

        }
    }



}

void SoftwareDownloadPage::backToSoftwareList(){

    if(mainLayout) clearWidgetsAndLayouts(mainLayout);

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

//    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
//    if(reply == NULL) return;



//    QString targetFolder = "/home/elwin/Downloads";
//    QFile *mFile;

//    for(SoftwareInfo *si: softwareList){
//        if(si->getNetworkReply() == reply){
//            si->downloadInProg = false;
//            si->downloadSuccess = true;
//            si->markedForDownlaod = false;
//            si->markedForInstall = true;


//            QString fileName = si->getSoftwareName();
//            if(si->version64Bit) fileName += "_x64";
//            fileName += ".exe";

//            mFile = new QFile( targetFolder + QDir::separator() + fileName);
//            // Trying to open the file
//            if (!mFile->open(QIODevice::WriteOnly)){
//                qDebug() << "Could not open file";
//                delete mFile;
//                mFile = nullptr;
//            }

//            if(mFile) {
//                qDebug() << "file is open attempting to write";
//                mFile->write(reply->readAll());
//                mFile->flush();
//                mFile->close();
//                qDebug() << "Finished writing to file. file closed.";

//            }

//        }
//    }

    //readyToInstall = true;
    if(readyToInstallButton) {
        readyToInstallButton->setDisabled(false);
        readyToInstallButton->setStyleSheet("QPushButton{background-color:green;}");

    }



    //reply->deleteLater();
}

void SoftwareDownloadPage::addFileToInstallList(){
    //show warning label

    WarningBox warning("Are you sure you want to add the selected files to the install queue?");
    warning.setModal(true);
    warning.exec();
    if(warning.actionConfirmed()) {
        localFilesInInstallQ = true;
        for(LocalFile *lf: localFilesMap){
            if(lf->getReadyState()) qDebug() << lf->getFileName()<<" is ready to be installed";

        }

    }
}







void SoftwareDownloadPage::showDownloadProgress(){

    if(!mainLayout) {
        qDebug() << "in function showDownloadProgres: mainLayout is NULL";
        return;
    }
    if(mainLayout) clearWidgetsAndLayouts(mainLayout);
    mainLayout = new QVBoxLayout;

    disconnect(this,0,0,0);


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
                //ProgressListenner *pl = new ProgressListenner;
                si->setProgressListener(new ProgressListenner);
                connect(stopDownloadBtn, &QPushButton::clicked, si, &SoftwareInfo::stopDownload);
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
    connect(backButton, &QPushButton::clicked, this, &SoftwareDownloadPage::backToSoftwareList);

}

void SoftwareDownloadPage::startDownloads()
{
    for(SoftwareInfo *si : softwareList){
        if(si->getDownloadMarked()) {
            if(si->getVersionSelect32()) network->get(si->get32BitURL());
            if(si->getVersionSelect64()) network->get(si->get64BitURL());

            QNetworkReply *reply = network->getLastReply();
            si->setNetworkReply(reply);
//            si->downloadInProg = true;
//            si->markedForDownlaod = false;


            if(si->getProgressListener()) connect(reply, &QNetworkReply::downloadProgress, si->getProgressListener(), &ProgressListenner::onDownloadProgress);
            connect(reply, &QNetworkReply::finished, this, &SoftwareDownloadPage::finishedDownloading);
            connect(reply, &QNetworkReply::finished, si, &SoftwareInfo::finishedDownload);
        }
    }

}

void SoftwareDownloadPage::stopDownloads()
{
    WarningBox warningbox("Are you sure you want to cancel ALL downloads?");
    warningbox.setWarningType(false, true);
    warningbox.setModal(true);
    warningbox.exec();
    if(warningbox.actionConfirmed()) {


        clearWidgetsAndLayouts(mainLayout);
        for(SoftwareInfo *si: softwareList) si->stopDownload();



//        //could do stop only checked(selected) downloads
//        for(SoftwareInfo *si: softwareList) {
//            if(si->downloadInProgress()){
//                disconnect(si->getNetworkReply(),0,0,0);
//                disconnect(si->getProgressListener(),0,0,0);
//                delete si->getProgressListener();

//                si->downloadInProg = false;
//                si->downloadInterrupt = true;
//                si->markedForDownlaod = true;
//            }
//        }
//        network->closeAllConnections();


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




ConfigurationPage::ConfigurationPage(QWidget *parent) : QWidget(parent){
    QGroupBox *configGroup = new QGroupBox(tr("Server configuration"));

    QLabel *serverLabel = new QLabel(tr("Server:"));
    QComboBox *serverCombo = new QComboBox;
    serverCombo->addItem(tr("Qt (Australia)"));
    serverCombo->addItem(tr("Qt (Germany)"));
    serverCombo->addItem(tr("Qt (Norway)"));
    serverCombo->addItem(tr("Qt (People's Republic of China)"));
    serverCombo->addItem(tr("Qt (USA)"));

    QHBoxLayout *serverLayout = new QHBoxLayout;
    serverLayout->addWidget(serverLabel);
    serverLayout->addWidget(serverCombo);

    QVBoxLayout *configLayout = new QVBoxLayout;
    configLayout->addLayout(serverLayout);
    configGroup->setLayout(configLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(configGroup);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

void clearWidgetsAndLayouts(QLayout * layout) {
   if (! layout) return;

   while (auto item = layout->takeAt(0)) {
      delete item->widget();
      clearWidgetsAndLayouts(item->layout());
   }
   delete layout;
}
