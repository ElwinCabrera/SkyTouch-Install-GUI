#include "installconfirmation.h"

#include <QtWidgets>


InstallConfirmation::InstallConfirmation(vector<pair<QGroupBox *,QString>> installGroups,  vector<QString> getURLs){
    resize(QSize(600, 300));
    for(QString s: getURLs) URLs.push_back(s);

    QGroupBox *confirmInstallGroup = new QGroupBox(tr("Programs to be Installed..."));
    softwareListWidget = new QListWidget;
    softwareListWidget->setViewMode(QListView::ListMode);

    softwareListWidget->setMaximumWidth(650);

    QString listEntry = "";
    int getURLIdx = 0;
    for(pair<QGroupBox *,QString> p: installGroups){
        if(p.first->isChecked()) {
            //Creating a new list widget item whose parent is the softwareListWidget itself
            QListWidgetItem *item = new QListWidgetItem(softwareListWidget);
            item->setText(p.second + ": " + getURLs.at(getURLIdx));

            //Adding the item to the softwareListWidget
            softwareListWidget->addItem(item);

            getURLIdx++;
        }
    }

    QLabel *totalSizeLabel = new QLabel;
    totalSizeLabel->setText("Total Size: " + QString::number(totalFileSize()) + "MB");


    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QWidget::close);

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

int InstallConfirmation::totalFileSize()
{
    Network network;
    int totalSize = 0;
    for(QString url: URLs){
        network.head(url);

        totalSize += network.getFileLength();
    }
    return totalSize / (1024 * 1024); // converting to megabytes


}
