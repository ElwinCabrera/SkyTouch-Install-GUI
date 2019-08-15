#include "installconfirmation.h"

#include <QtWidgets>


InstallConfirmation::InstallConfirmation(QWidget *parent, vector<SoftwareInfo*> softwareL) {
    resize(QSize(600, 300));

    QGroupBox *confirmInstallGroup = new QGroupBox(tr("Programs to be Installed..."));
    softwareListWidget = new QListWidget;
    softwareListWidget->setViewMode(QListView::ListMode);
    softwareListWidget->setMaximumWidth(650);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    for(SoftwareInfo *si: softwareL){
        if(si->getDownloadMarked()) {
            //Creating a new list widget item whose parent is the softwareListWidget itself
            QListWidgetItem *item = new QListWidgetItem(softwareListWidget);

            if(si->getVersionSelect32()) item->setText(si->getSoftwareName() + ": " + si->get32BitURL());
            if(si->getVersionSelect64()) item->setText(si->getSoftwareName() + ": " + si->get64BitURL());

            //Adding the item to the softwareListWidget
            softwareListWidget->addItem(item);

            connect(buttonBox, &QDialogButtonBox::accepted, si, &SoftwareInfo::downloadStart);
        }
    }

    QLabel *totalSizeLabel = new QLabel;
    uint64_t fileSize = totalFileSize(softwareL);
    totalSizeLabel->setText("Total Size: " + QString::number(fileSize) + "MiB");






    QHBoxLayout *confirmInstallLayout = new QHBoxLayout;
    confirmInstallLayout->addWidget(softwareListWidget);
    confirmInstallGroup->setLayout(confirmInstallLayout);

    QHBoxLayout *sizeLabelLayout = new QHBoxLayout;
    sizeLabelLayout->addStretch(1);
    sizeLabelLayout->addWidget(totalSizeLabel);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(buttonBox);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(confirmInstallGroup);
    //mainLayout->addStretch(1000);
    mainLayout->addLayout(sizeLabelLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &InstallConfirmation::okButtonCliked);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &InstallConfirmation::cancelButtonClicked);


}

uint64_t InstallConfirmation::totalFileSize(vector<SoftwareInfo*> softwareL)
{

    uint64_t totalSize = 0;
    for(SoftwareInfo *si: softwareL){
        if(si->getDownloadMarked() ){
            if(si->getVersionSelect32()) network.head(si->get32BitURL());
            if(si->getVersionSelect64()) network.head(si->get64BitURL());

            totalSize += network.getFileLength();
        }
    }
    return totalSize / (1024 * 1024); // converting to megabytes


}

void InstallConfirmation::okButtonCliked() {
    confirm = true;
    this->close();

}

void InstallConfirmation::cancelButtonClicked() {
    confirm = false;
    this->close();
}
