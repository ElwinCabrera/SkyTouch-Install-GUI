#include "installconfirmation.h"

#include <QtWidgets>


InstallConfirmation::InstallConfirmation(QSet<SoftwareInfo*> &softwareList, Network *network, QWidget * /* parent unused */) {
    resize(QSize(600, 300));
    this->softwareList = softwareList;
    this->network = network;

    QGroupBox *confirmInstallGroup = new QGroupBox(tr("Programs to be Installed..."));
    softwareListWidget = new QListWidget;
    softwareListWidget->setViewMode(QListView::ListMode);
    softwareListWidget->setMaximumWidth(650);



    for(SoftwareInfo *si: softwareList){
        if(si->getDownloadMarked()) {
            //Creating a new list widget item whose parent is the softwareListWidget itself
            QListWidgetItem *item = new QListWidgetItem(softwareListWidget);

            if(si->getVersionSelect32()) item->setText(si->getSoftwareName() + ": " + si->get32BitURL());
            if(si->getVersionSelect64()) item->setText(si->getSoftwareName() + ": " + si->get64BitURL());

            //Adding the item to the softwareListWidget
            softwareListWidget->addItem(item);


        }
    }

    QLabel *totalSizeLabel = new QLabel;
    uint64_t fileSize = totalFileSize();
    totalSizeLabel->setText("Total Size: " + QString::number(fileSize) + "MiB");



    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);


    QHBoxLayout *confirmInstallLayout = new QHBoxLayout;
    confirmInstallLayout->addWidget(softwareListWidget);
    confirmInstallGroup->setLayout(confirmInstallLayout);

    QHBoxLayout *sizeLabelLayout = new QHBoxLayout;
    sizeLabelLayout->addStretch(1);
    sizeLabelLayout->addWidget(totalSizeLabel);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(buttonBox);


    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(confirmInstallGroup);
    //mainLayout->addStretch(1000);
    mainLayout->addLayout(sizeLabelLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &InstallConfirmation::okButtonCliked);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &InstallConfirmation::cancelButtonClicked);


}

InstallConfirmation::~InstallConfirmation()
{
    qDebug() << "InstallConfirmation Destructor";

    /*for(SoftwareInfo *si: softwareList){
        auto it = softwareList.find(si);
        softwareList.erase(it);
        if(si) delete si;
    }*/
    //if(softwareListWidget) delete softwareListWidget;
    if(mainLayout) clearLayotAndWidgets(mainLayout);

}

uint64_t InstallConfirmation::totalFileSize()
{

    uint64_t totalSize = 0;
    for(SoftwareInfo *si: softwareList){
        if(si->getDownloadMarked() ){
            if(si->getVersionSelect32()) network->head(si->get32BitURL());
            if(si->getVersionSelect64()) network->head(si->get64BitURL());

            totalSize += network->getFileLength();
        }
    }
    return totalSize / (1024 * 1024); // converting to megabytes


}

void InstallConfirmation::okButtonCliked() {
    confirm = true;
    this->close();
}

void InstallConfirmation::cancelButtonClicked() {
    confirm = false; // this is redundant but just in case
    this->close();
}
