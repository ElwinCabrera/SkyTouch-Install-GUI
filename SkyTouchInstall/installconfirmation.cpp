#include "installconfirmation.h"
#include <QtWidgets>

InstallConfirmation::InstallConfirmation(vector<pair<QGroupBox *,QString>> installGroups,  vector<QString> getURLs){
    resize(QSize(600, 300));

    QGroupBox *confirmInstallGroup = new QGroupBox(tr("Programs to be Installed..."));
    softwareListWidget = new QListWidget;
    softwareListWidget->setViewMode(QListView::ListMode);

    softwareListWidget->setMaximumWidth(3000);

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

    //QGroupBox *buttonGroup = new QGroupBox;
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    //buttonBox->setLayout(QDialogButtonBox::WinLayout);
    //QPushButton *closeButton = new QPushButton(tr("Close"));
    //QPushButton *confirmButton = new QPushButton(tr("Confirm"));


    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QWidget::close);

    QHBoxLayout *confirmInstallLayout = new QHBoxLayout;
    confirmInstallLayout->addWidget(softwareListWidget);
    confirmInstallGroup->setLayout(confirmInstallLayout);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(buttonBox);
    //buttonLayout->addWidget(closeButton);
    //buttonLayout->addWidget(confirmButton);
    //buttonGroup->setLayout(buttonLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(confirmInstallGroup);
    //mainLayout->addStretch(1000);
    mainLayout->addLayout(buttonLayout);



    setLayout(mainLayout);


}
