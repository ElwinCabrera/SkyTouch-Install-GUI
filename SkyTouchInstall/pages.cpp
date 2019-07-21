

#include "pages.h"
#include "canceldownloadswarning.h"



SoftwareDownloadPage::SoftwareDownloadPage(QWidget *parent) : QWidget(parent){



}

void SoftwareDownloadPage::initPage(vector<SoftwareInfo*> softwareL, Network *network)
{

    if(!softwareL.empty()){

        this->network = network;

        for(SoftwareInfo *si: softwareL){
            //SoftwareInfo *s = new SoftwareInfo(si->softwareName, si->url32BitVersion, si->url64BitVersion, si->markedForDownlaod, si->markedForInstall);
            this->softwareList.push_back(si);
        }

    }

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
    QPushButton *viewDownloadProgButton = new QPushButton(tr("Show Downlaod Progress"));
    viewDownloadProgButton->setDisabled(true);

    QPushButton *downloadButton = new QPushButton(tr("Start Download(s)"));
    downloadButton->setDefault(true);




    connect(downloadButton, &QPushButton::clicked, this, &SoftwareDownloadPage::downloadButtonCliked);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(searchForLocalButton);
    buttonsLayout->addWidget(viewDownloadProgButton);



    //
    mainLayout->addWidget(scrollArea);
    //mainLayout->addWidget(downloadButton);
    mainLayout->addLayout(buttonsLayout);
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

            ProgressListenner *pl = new ProgressListenner;
            pl->pBar = pBar;

            QHBoxLayout *layout = new QHBoxLayout;
            layout->addWidget(pBar);
            layout->addStretch(1);
            groupBox->setLayout(layout);

            pListeners.push_back(pl);

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
    for(uint i = 0 ; i<softwareList.size(); ++i){
        if(softwareList.at(i)->version32Bit) network->get(softwareList.at(i)->url32BitVersion);
        if(softwareList.at(i)->version64Bit) network->get(softwareList.at(i)->url64BitVersion);

        QNetworkReply *r = network->getLastReply();
        ProgressListenner *pl = pListeners.at(i);
        connect(r, &QNetworkReply::downloadProgress, pl, &ProgressListenner::onDownloadProgress);
    }

}

void SoftwareDownloadPage::stopDownloads()
{
    CancelDownloadsWarning *warning = new CancelDownloadsWarning;
    warning->setModal(true);
    warning->exec();
    if(warning->getOkButtonCliked()) {

        network->closeAllConnections();
        clearWidgetsAndLayouts(mainLayout);

        vector<SoftwareInfo*> a;
        //could do stop checked downloads
        for(ProgressListenner *pl: pListeners) {disconnect(pl,0,0,0); delete pl; }
        pListeners.clear();

        initPage(a, NULL);

    }

    delete warning;

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
