

#include "pages.h"
#include "actionhandler.h"
#include "canceldownloadswarning.h"



SoftwareInstallationPage::SoftwareInstallationPage(QWidget *parent) : QWidget(parent){
    mainLayout = nullptr;
    setMainLayout(true);

}

void SoftwareInstallationPage::setMainLayout(bool firstTimeLoad)
{
    if(mainLayout) clearWidgetsAndLayouts(mainLayout);

    QGroupBox *installCREGroup = new QGroupBox(tr("CRE"));
    installCREGroup->setCheckable(true);
    installCREGroup->blockSignals(true);
    installCREGroup->setChecked(true);
    installCREGroup->blockSignals(false);

    installCRERadioBtn = new QRadioButton(tr("Install CRE"));
    installCRE64RadioBtn = new QRadioButton(tr("Install CRE x64"));
    installCRE64RadioBtn->setChecked(true);

    if(firstTimeLoad) installGroups.push_back({installCREGroup,"CRE"});


    //QCheckBox *docsCheckBox = new QCheckBox(tr("Update documentation"));



    /*QGroupBox *packageGroup = new QGroupBox(tr("Existing packages"));

    QListWidget *packageList = new QListWidget;
    QListWidgetItem *qtItem = new QListWidgetItem(packageList);
    qtItem->setText(tr("Qt"));
    QListWidgetItem *qsaItem = new QListWidgetItem(packageList);
    qsaItem->setText(tr("QSA"));
    QListWidgetItem *teamBuilderItem = new QListWidgetItem(packageList);
    teamBuilderItem->setText(tr("Teambuilder"));*/

    startInstallationButton = new QPushButton(tr("Start Download"));



    QHBoxLayout *installLayout = new QHBoxLayout;
    installLayout->addWidget(installCRERadioBtn);
    installLayout->addWidget(installCRE64RadioBtn);
    installCREGroup->setLayout(installLayout);



    /*QVBoxLayout *packageLayout = new QVBoxLayout;
    packageLayout->addWidget(packageList);
    packageGroup->setLayout(packageLayout);*/

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(installCREGroup);
    //mainLayout->addWidget(packageGroup);
    mainLayout->addSpacing(200);
    mainLayout->addWidget(startInstallationButton);
    mainLayout->addStretch(1);
    setLayout(mainLayout);

    connect(startInstallationButton, &QPushButton::clicked, this, &SoftwareInstallationPage::onStartInstallationButtonCliked);


}

void SoftwareInstallationPage::onStartInstallationButtonCliked(){
    ActionHandler actionHandler;
    bool minimumOneChecked = false;

    for(uint i = 0; i < installGroups.size(); ++i){
        if(installGroups.at(i).first->isChecked()) {
            minimumOneChecked = true;
            int j = 0;
            for(QRadioButton *rb : installGroups.at(i).first->findChildren<QRadioButton*> ()){
                if(rb->isChecked()) break;
                j++;
            }
            QString bitVersion = (j == 0) ? "32":"64";
            QString url = actionHandler.getDownloadUrl(installGroups.at(i).second, "12.9" ,bitVersion);
            //QString url = "https://postman-echo.com/get?foo1=bar1&foo2=bar2";
            getURLs.push_back(url);
            qDebug() << installGroups.at(i).second << bitVersion << " marked for installation";
            qDebug() << "URL: " << url;
        }
    }
    //getURLs.push_back("http://download2.pcamerica.com/12.9/CRE_Setup.exe");
    if(minimumOneChecked){
        confirmWindow = new InstallConfirmation(installGroups, getURLs);
        confirmWindow->setModal(true);
        confirmWindow->exec();

        if(confirmWindow->getConfirmation()) {
            qDebug() << "download confirmed";

            showDownloadProgress();
            startDownloads();

            //if all downloads are done then return to installation screen
        }
        if(!confirmWindow->getConfirmation()) qDebug() << "download  NOT confirmed";
    }


}

void SoftwareInstallationPage::showDownloadProgress(){
    vector<QHBoxLayout*> layouts;
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
    disconnect(startInstallationButton, &QPushButton::clicked, this, &SoftwareInstallationPage::onStartInstallationButtonCliked);
    mainLayout = new QVBoxLayout;
    for(QGroupBox *gb: downlowdGroups) mainLayout->addWidget(gb);
    mainLayout->addSpacing(200);
    mainLayout->addWidget(stopDownload);
    mainLayout->addStretch(1);
    setLayout(mainLayout);

    connect(stopDownload, &QPushButton::clicked, this, &SoftwareInstallationPage::stopDownloads);


}

void SoftwareInstallationPage::startDownloads()
{
    for(int i = 0 ; i<getURLs.size(); ++i){
        network.get(getURLs.at(i));
        QNetworkReply *r = network.getLastReply();
        ProgressListenner *pl = pListeners.at(i);
        connect(r, &QNetworkReply::downloadProgress, pl, &ProgressListenner::onDownloadProgress);
    }

}

void SoftwareInstallationPage::stopDownloads()
{
    CancelDownloadsWarning *warning = new CancelDownloadsWarning;
    warning->exec();
    if(warning->getOkButtonCliked()) {


        for(int i = 0 ; i<getURLs.size(); ++i){
            vector<QNetworkReply*> rs = network.getReplys();
            ProgressListenner *pl = pListeners.at(i);
            disconnect(rs.at(i), &QNetworkReply::downloadProgress, pl, &ProgressListenner::onDownloadProgress);
        }
        network.closeAllConnections();
        setMainLayout(false);
    }
    //clearWidgetsAndLayouts(mainLayout);
    //SoftwareInstallationPage(nullptr);
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
