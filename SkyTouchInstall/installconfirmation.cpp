#include "installconfirmation.h"

#include <QtWidgets>


InstallConfirmation::InstallConfirmation(QWidget *parent, vector<SoftwareInfo*> softwareL) {
    resize(QSize(600, 300));

    QGroupBox *confirmInstallGroup = new QGroupBox(tr("Programs to be Installed..."));
    softwareListWidget = new QListWidget;
    softwareListWidget->setViewMode(QListView::ListMode);

    softwareListWidget->setMaximumWidth(650);

    for(SoftwareInfo *si: softwareL){
        if(si->markedForDownlaod) {
            //Creating a new list widget item whose parent is the softwareListWidget itself
            QListWidgetItem *item = new QListWidgetItem(softwareListWidget);
            if(si->version32Bit) item->setText(si->softwareName + ": " + si->url32BitVersion);
            if(si->version64Bit) item->setText(si->softwareName + ": " + si->url64BitVersion);

            //Adding the item to the softwareListWidget
            softwareListWidget->addItem(item);
        }
    }

    QLabel *totalSizeLabel = new QLabel;
    totalSizeLabel->setText("Total Size: " + QString::number(totalFileSize(softwareL)) + "MB");


    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &InstallConfirmation::okButtonCliked);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &InstallConfirmation::cancelButtonClicked);

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


}

int InstallConfirmation::totalFileSize(vector<SoftwareInfo*> softwareL)
{

    int totalSize = 0;
    for(SoftwareInfo *si: softwareL){
        if(si->version32Bit) network.head(si->url32BitVersion);
        if(si->version64Bit) network.head(si->url64BitVersion);
        totalSize += network.getFileLength();
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
