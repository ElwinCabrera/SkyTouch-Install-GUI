

#include "pages.h"
#include "canceldownloadswarning.h"



SoftwareDownloadPage::SoftwareDownloadPage(QWidget *parent) : QWidget(parent){



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
    viewDownloadProgButton->setDisabled(true);

    readyToInstallButton = new QPushButton(tr("Show Ready to Install"));
    readyToInstallButton->setDisabled(true);

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
        InstallConfirmation *confirmWindow = new InstallConfirmation(this, softwareList);
        confirmWindow->setModal(true);
        confirmWindow->exec();

        if(confirmWindow->getConfirmation()) {
            qDebug() << "download confirmed";
            showDownloadProgress();
            startDownloads();

            //if all downloads are done then return to installation screen
        }
        if(!confirmWindow->getConfirmation()) qDebug() << "download  NOT confirmed";

        delete confirmWindow;
    }
}

void SoftwareDownloadPage::searchForLocalFiles(){

}

void SoftwareDownloadPage::viewDownloadProg(){

}

void SoftwareDownloadPage::showReadyToInstall(){

}







void SoftwareDownloadPage::showDownloadProgress(){

    clearWidgetsAndLayouts(mainLayout);
    mainLayout = new QVBoxLayout;
    //disconnect(downloadButton, &QPushButton::clicked, this, &SoftwareDownloadPage::onStartInstallationButtonCliked);
    disconnect(this,0,0,0);


    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setFixedSize(QSize(350, 325));
    QWidget *scrollAreaWidget = new QWidget;
    QVBoxLayout *scrollAreaLayout = new QVBoxLayout;


    for(SoftwareInfo *si: softwareList){
        if(si->markedForDownlaod){

            QString s = "Downloading " + si->softwareName;
            QGroupBox *groupBox = new QGroupBox(s);
            //groupBox->setFixedWidth(312.5);
            QProgressBar *pBar = new QProgressBar;
            pBar->setFixedWidth(300);

            si->pl = new ProgressListenner;
            si->pl->pBar = pBar;

            QHBoxLayout *layout = new QHBoxLayout;
            layout->addWidget(pBar);
            layout->addStretch(1);
            groupBox->setLayout(layout);


            disconnect(si, 0,0,0);

            //mainLayout->addWidget(groupBox);
            scrollAreaLayout->addWidget(groupBox);

        }
    }
    scrollAreaWidget->setLayout(scrollAreaLayout);
    scrollArea->setWidget(scrollAreaWidget);

    QPushButton *backButton = new QPushButton(tr("Back"));

    QPushButton *stopDownload = new QPushButton(tr("Stop Download"));
    QPalette pal = stopDownload->palette();
    pal.setColor(QPalette::Button, QColor(Qt::red));
    stopDownload->setAutoFillBackground(true);
    stopDownload->setPalette(pal);
    stopDownload->update();

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(backButton);
    buttonLayout->addWidget(stopDownload);


    mainLayout->addWidget(scrollArea);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch(1);
    setLayout(mainLayout);

    connect(stopDownload, &QPushButton::clicked, this, &SoftwareDownloadPage::stopDownloads);

}

void SoftwareDownloadPage::startDownloads()
{
    for(SoftwareInfo *si : softwareList){
        if(si->version32Bit) network->get(si->url32BitVersion);
        if(si->version64Bit) network->get(si->url64BitVersion);

        QNetworkReply *r = network->getLastReply();

        connect(r, &QNetworkReply::downloadProgress, si->pl, &ProgressListenner::onDownloadProgress);
    }

}

void SoftwareDownloadPage::stopDownloads()
{
    CancelDownloadsWarning warning;
    warning.setModal(true);
    warning.exec();
    if(warning.getOkButtonCliked()) {

        network->closeAllConnections();
        clearWidgetsAndLayouts(mainLayout);


        //could do stop only checked(selected) downloads
        for(SoftwareInfo *si: softwareList) {disconnect(si->pl,0,0,0); delete si->pl; }


        vector<SoftwareInfo*> a;
        initPage(a, NULL);

    }

    //delete warning;

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
   if (! layout)
      return;
   while (auto item = layout->takeAt(0)) {
      delete item->widget();
      clearWidgetsAndLayouts(item->layout());
   }
   delete layout;
}
