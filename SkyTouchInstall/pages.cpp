

#include "pages.h"
#include "canceldownloadswarning.h"



SoftwareDownloadPage::SoftwareDownloadPage(QWidget *parent) : QWidget(parent){

   mainLayout = new QVBoxLayout;

}

void SoftwareDownloadPage::initPage(vector<SoftwareInfo*> softwareL)
{

    for(SoftwareInfo *si: softwareL){
        //SoftwareInfo *s = new SoftwareInfo(si->softwareName, si->url32BitVersion, si->url64BitVersion, si->markedForDownlaod, si->markedForInstall);
        this->softwareList.push_back(si);
    }

    bool firstIter = true;
    for(SoftwareInfo *si :  softwareList){
        QGroupBox *downloadGroup = new QGroupBox(si->softwareName);
        downloadGroup->setCheckable(true);

        if(firstIter){
            downloadGroup->blockSignals(true);
            downloadGroup->setChecked(true);
            downloadGroup->blockSignals(false);
            firstIter = false;
        }
        QRadioButton *downloadRadioBtn = new QRadioButton("Download "+si->softwareName);
        QRadioButton *download64RadioBtn = new QRadioButton("Download "+si->softwareName + "x64");
        download64RadioBtn->setChecked(true);

        QHBoxLayout *downloadLayout = new QHBoxLayout;
        downloadLayout->addWidget(downloadRadioBtn);
        downloadLayout->addWidget(download64RadioBtn);
        downloadGroup->setLayout(downloadLayout);

        if( si->url32BitVersion == "") downloadRadioBtn->setCheckable(false);
        if( si->url64BitVersion == "") download64RadioBtn->setCheckable(false);

        connect(downloadGroup, &QGroupBox::toggled, si, &SoftwareInfo::onDownloadCheckBoxClicked);
        connect(download64RadioBtn, &QRadioButton::toggled,si, &SoftwareInfo::onVersionSelect);

         mainLayout->addWidget(downloadGroup);
    }

    //QCheckBox *docsCheckBox = new QCheckBox(tr("Update documentation"));


    QPushButton *downloadButton = new QPushButton(tr("Start Download(s)"));
    connect(downloadButton, &QPushButton::clicked, this, &SoftwareDownloadPage::downloadButtonCliked);


    mainLayout->addSpacing(200);
    mainLayout->addWidget(downloadButton);
    mainLayout->addStretch(1);
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
   /* vector<QHBoxLayout*> layouts;
    vector<QGroupBox*> downlowdGroups;

    for(pair<QGroupBox *, QString> p: installGroups){
        if(p.first->isChecked()){
            QString s = "Downloading " + p.second;
            QGroupBox *groupBox = new QGroupBox(s);
            QProgressBar *bar = new QProgressBar;

            ProgressListenner *pl = new ProgressListenner;
            pl->pBar = bar;


            QHBoxLayout *layout = new QHBoxLayout;
            layout->addWidget(bar);
            groupBox->setLayout(layout);

            downlowdGroups.push_back(groupBox);
            pBars.push_back(bar);
            layouts.push_back(layout);

            pListeners.push_back(pl);

        }
    }

    QPushButton *stopDownload = new QPushButton(tr("Stop Download"));

    clearWidgetsAndLayouts(mainLayout);

    disconnect(downloadButton, &QPushButton::clicked, this, &SoftwareDownloadPage::onStartInstallationButtonCliked);
    mainLayout = new QVBoxLayout;
    for(QGroupBox *gb: downlowdGroups) mainLayout->addWidget(gb);
    mainLayout->addSpacing(200);
    mainLayout->addWidget(stopDownload);
    mainLayout->addStretch(1);
    setLayout(mainLayout);

    connect(stopDownload, &QPushButton::clicked, this, &SoftwareDownloadPage::stopDownloads); */


}

void SoftwareDownloadPage::startDownloads()
{
    /*for(uint i = 0 ; i<getURLs.size(); ++i){
        network.get(getURLs.at(i));
        QNetworkReply *r = network.getLastReply();
        ProgressListenner *pl = pListeners.at(i);
        connect(r, &QNetworkReply::downloadProgress, pl, &ProgressListenner::onDownloadProgress);
    }*/

}

void SoftwareDownloadPage::stopDownloads()
{
   /* CancelDownloadsWarning *warning = new CancelDownloadsWarning;
    warning->exec();
    if(warning->getOkButtonCliked()) {

        network.closeAllConnections();
        clearWidgetsAndLayouts(mainLayout);
        QGroupBox *installCREGroup = new QGroupBox(tr("CRE"));
        installCREGroup->setCheckable(true);
        installCREGroup->blockSignals(true);
        installCREGroup->setChecked(true);
        installCREGroup->blockSignals(false);

        installCRERadioBtn = new QRadioButton(tr("Install CRE"));
        installCRE64RadioBtn = new QRadioButton(tr("Install CRE x64"));
        installCRE64RadioBtn->setChecked(true);

        installGroups.push_back({installCREGroup,"CRE"});


        //QCheckBox *docsCheckBox = new QCheckBox(tr("Update documentation"));





        downloadButton = new QPushButton(tr("Start Download"));



        QHBoxLayout *installLayout = new QHBoxLayout;
        installLayout->addWidget(installCRERadioBtn);
        installLayout->addWidget(installCRE64RadioBtn);
        installCREGroup->setLayout(installLayout);





        mainLayout = new QVBoxLayout;
        mainLayout->addWidget(installCREGroup);
        //mainLayout->addWidget(packageGroup);
        mainLayout->addSpacing(200);
        mainLayout->addWidget(downloadButton);
        mainLayout->addStretch(1);
        setLayout(mainLayout);

        connect(downloadButton, &QPushButton::clicked, this, &SoftwareDownloadPage::onStartInstallationButtonCliked);



    }*/

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
