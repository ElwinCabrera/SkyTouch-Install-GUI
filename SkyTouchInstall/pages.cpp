

#include "pages.h"
#include "canceldownloadswarning.h"



SoftwareDownloadPage::SoftwareDownloadPage(QWidget *parent) : QWidget(parent){
    downloadConfirmed = false;
    readyToInstall = false;


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
        QGroupBox *downloadGroup = new QGroupBox("Download "+si->softwareName);
        downloadGroup->setFixedWidth(312.5);
        downloadGroup->setCheckable(true);
        downloadGroup->blockSignals(true);
        downloadGroup->setChecked(si->markedForDownlaod);

        if(si->downloadInProg || si->downloadSuccess){
            downloadGroup->setChecked(false);
            downloadGroup->setDisabled(true);
        }

        downloadGroup->blockSignals(false);


        QRadioButton *downloadRadioBtn = new QRadioButton("32 Bit");
        QRadioButton *download64RadioBtn = new QRadioButton("64 Bit");
        download64RadioBtn->setChecked(true);

        QHBoxLayout *downloadLayout = new QHBoxLayout;
        downloadLayout->addStretch(1);
        downloadLayout->addWidget(downloadRadioBtn);
        downloadLayout->addWidget(download64RadioBtn);
        downloadGroup->setLayout(downloadLayout);

        if( si->url32BitVersion == "") downloadRadioBtn->setCheckable(false);
        if( si->url64BitVersion == "") download64RadioBtn->setCheckable(false);
        downloadRadioBtn->setChecked(si->version32Bit);
        download64RadioBtn->setChecked(si->version64Bit);

        connect(downloadGroup, &QGroupBox::toggled, si, &SoftwareInfo::onDownloadCheckBoxClicked);
        connect(download64RadioBtn, &QRadioButton::toggled,si, &SoftwareInfo::onVersionSelect);

        //mainLayout->addWidget(downloadGroup);
        scrollAreaLayout->addWidget(downloadGroup);

    }
    scrollAreaWidget->setLayout(scrollAreaLayout);
    scrollArea->setWidget(scrollAreaWidget);



    QPushButton *searchForLocalButton = new QPushButton(tr("Search For Local Files"));


    viewDownloadProgButton = new QPushButton(tr("Show Downlaod Progress"));




    readyToInstallButton = new QPushButton(tr("Show Ready to Install"));
    if(!isReadyForInstall()) readyToInstallButton->setDisabled(true);


    QPushButton *downloadButton = new QPushButton(tr("Start Download(s)"));
    downloadButton->setDefault(true);




    connect(downloadButton, &QPushButton::clicked, this, &SoftwareDownloadPage::downloadButtonCliked);
    connect(searchForLocalButton, &QPushButton::clicked, this , &SoftwareDownloadPage::searchForLocalFiles);
    connect(viewDownloadProgButton, &QPushButton::clicked, this, &SoftwareDownloadPage::viewDownloadProg);
    connect(readyToInstallButton, &QPushButton::clicked, this, &SoftwareDownloadPage::showReadyToInstall);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(searchForLocalButton);
    buttonsLayout->addWidget(viewDownloadProgButton);




    //
    mainLayout->addWidget(scrollArea);
    //mainLayout->addWidget(downloadButton);
    mainLayout->addLayout(buttonsLayout);
    mainLayout->addWidget(readyToInstallButton);
    mainLayout->addWidget(downloadButton);

    mainLayout->addStretch(1);
   // mainLayout->addSpacing(200);
    setLayout(mainLayout);


}




void SoftwareDownloadPage::downloadButtonCliked(){
    qDebug() <<  "startDownloadClicked";
    bool minimumOneChecked = false;

    for(SoftwareInfo *si: softwareList){
        if(si->markedForDownlaod) {minimumOneChecked = true; break;}
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

            //if all downloads are done then return to installation screen
        }
        if(!confirmWindow.getConfirmation()) qDebug() << "download  NOT confirmed";

    }
}

void SoftwareDownloadPage::searchForLocalFiles(){

}

void SoftwareDownloadPage::viewDownloadProg(){
    showDownloadProgress();
}

void SoftwareDownloadPage::showReadyToInstall(){

}

void SoftwareDownloadPage::backToSoftwareList(){

    if(mainLayout) clearWidgetsAndLayouts(mainLayout);

    downloadConfirmed = false;

    for(SoftwareInfo *si: softwareList) {
        if(si->reply && si->downloadInProg ) disconnect(si->reply, &QNetworkReply::downloadProgress, si->pl, &ProgressListenner::onDownloadProgress);
    }
    vector<SoftwareInfo*> tmp;
    initPage(tmp, NULL);
}

void SoftwareDownloadPage::finishedDownloading(){
    qDebug() << "finished Downloading in SoftwareDownloadsPage";

    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if(reply == NULL) return;



    QString targetFolder = "/home/elwin/Downloads";
    QFile *mFile;

    for(SoftwareInfo *si: softwareList){
        if(si->reply == reply){
            si->downloadInProg = false;
            si->downloadSuccess = true;
            si->markedForDownlaod = false;
            si->markedForInstall = true;


            QString fileName = si->softwareName;
            if(si->version64Bit) fileName += "_x64";
            fileName += ".exe";

            mFile = new QFile( targetFolder + QDir::separator() + fileName);
            // Trying to open the file
            if (!mFile->open(QIODevice::WriteOnly)){
                qDebug() << "Could not open file";
                delete mFile;
                mFile = nullptr;
            }

            if(mFile) {
                qDebug() << "file is open attempting to write";
                mFile->write(reply->readAll());
                mFile->flush();
                mFile->close();
                qDebug() << "Finished writing to file. file closed.";

            }

        }
    }

    //readyToInstall = true;
    if(readyToInstallButton) readyToInstallButton->setDisabled(false);



    reply->deleteLater();
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


    for(SoftwareInfo *si: softwareList){

        if(si->markedForDownlaod  || si->downloadInProg){

            QString s = "Downloading " + si->softwareName;
            QGroupBox *groupBox = new QGroupBox(s);
            //groupBox->setFixedWidth(312.5);

            if(!si->downloadInProg){
                si->pl = new ProgressListenner;
            } else {
                if(si->reply && si->pl) connect(si->reply, &QNetworkReply::downloadProgress, si->pl,&ProgressListenner::onDownloadProgress);
            }

            if(si->pl){
                si->pl->pBar = new QProgressBar;
                si->pl->pBar->setFixedWidth(300);

                QHBoxLayout *layout = new QHBoxLayout;
                layout->addWidget(si->pl->pBar);
                layout->addStretch(1);
                groupBox->setLayout(layout);
                scrollAreaLayout->addWidget(groupBox);
            }



        }
    }
    scrollAreaWidget->setLayout(scrollAreaLayout);
    scrollArea->setWidget(scrollAreaWidget);

    QPushButton *backButton = new QPushButton(tr("Back"));


    stopDownloadBtn = new QPushButton(tr("Stop Download"));
    if(!isDownloadInProgress()) stopDownloadBtn->setDisabled(true);

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
        if(si->markedForDownlaod) {
            if(si->version32Bit) network->get(si->url32BitVersion);
            if(si->version64Bit) network->get(si->url64BitVersion);

            QNetworkReply *r = network->getLastReply();
            si->reply = r;
            si->downloadInProg = true;
            si->markedForDownlaod = false;
            stopDownloadBtn->setDisabled(false);

            if(si->pl) connect(r, &QNetworkReply::downloadProgress, si->pl, &ProgressListenner::onDownloadProgress);
            connect(r, &QNetworkReply::finished, this, &SoftwareDownloadPage::finishedDownloading);
        }
    }

}

void SoftwareDownloadPage::stopDownloads()
{
    CancelDownloadsWarning warning;
    warning.setModal(true);
    warning.exec();
    if(warning.getOkButtonCliked()) {


        clearWidgetsAndLayouts(mainLayout);



        //could do stop only checked(selected) downloads
        for(SoftwareInfo *si: softwareList) {
            if(si->downloadInProg){
                disconnect(si->reply,0,0,0);
                disconnect(si->pl,0,0,0);
                delete si->pl;

                si->downloadInProg = false;
                si->downloadInterrupted = true;
                si->markedForDownlaod = true;
            }
        }
        network->closeAllConnections();


        vector<SoftwareInfo*> a;
        initPage(a, NULL);

    }

}

bool SoftwareDownloadPage::isDownloadInProgress(){

    for(SoftwareInfo *si: softwareList){
        if(!si->pl) continue;
        if(si->pl->_lastKnownReceived < si->pl->_lastKnownTotal) return true;
    }
    return false;
}

bool SoftwareDownloadPage::isReadyForInstall(){
    for(SoftwareInfo *si: softwareList) if(si->markedForInstall) return true;
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
