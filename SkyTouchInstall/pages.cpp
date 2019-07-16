

#include "pages.h"
#include "actionhandler.h"



SoftwareInstallationPage::SoftwareInstallationPage(QWidget *parent) : QWidget(parent){

    QGroupBox *installCREGroup = new QGroupBox(tr("CRE"));
    installCREGroup->setCheckable(true);
    installCREGroup->blockSignals(true);
    installCREGroup->setChecked(true);
    installCREGroup->blockSignals(false);

    installCRERadioBtn = new QRadioButton(tr("Install CRE"));
    installCRE64RadioBtn = new QRadioButton(tr("Install CRE x64"));
    installCRE64RadioBtn->setChecked(true);

    installGroups.push_back(installCREGroup);


    //QCheckBox *docsCheckBox = new QCheckBox(tr("Update documentation"));



    /*QGroupBox *packageGroup = new QGroupBox(tr("Existing packages"));

    QListWidget *packageList = new QListWidget;
    QListWidgetItem *qtItem = new QListWidgetItem(packageList);
    qtItem->setText(tr("Qt"));
    QListWidgetItem *qsaItem = new QListWidgetItem(packageList);
    qsaItem->setText(tr("QSA"));
    QListWidgetItem *teamBuilderItem = new QListWidgetItem(packageList);
    teamBuilderItem->setText(tr("Teambuilder"));*/

    startInstallationButton = new QPushButton(tr("Start Installation"));

    QHBoxLayout *installLayout = new QHBoxLayout;
    installLayout->addWidget(installCRERadioBtn);
    installLayout->addWidget(installCRE64RadioBtn);
    installCREGroup->setLayout(installLayout);



    /*QVBoxLayout *packageLayout = new QVBoxLayout;
    packageLayout->addWidget(packageList);
    packageGroup->setLayout(packageLayout);*/

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(installCREGroup);
    //mainLayout->addWidget(packageGroup);
    mainLayout->addSpacing(200);
    mainLayout->addWidget(startInstallationButton);
    mainLayout->addStretch(1);
    setLayout(mainLayout);

    connect(startInstallationButton, &QPushButton::clicked, this, &SoftwareInstallationPage::onStartInstallationButtonCliked);
}

void SoftwareInstallationPage::onStartInstallationButtonCliked(){
    for(uint i = 0; i < installGroups.size(); ++i){
        if(installGroups.at(i)->isChecked()) {

            int j = 0;
            for(QRadioButton *rb : installGroups.at(i)->findChildren<QRadioButton*> ()){
                if(rb->isChecked()) break;
                j++;
            }
            QString version = (j == 0) ? "32":"64";
            markedForInstall.push_back({i, version});
            qDebug() << i <<" "<< version << " marked for installation";
        }
    }

}

QPushButton* SoftwareInstallationPage::getStartInstallationButton() { return startInstallationButton; }



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
