#include "canceldownloadswarning.h"

CancelDownloadsWarning::CancelDownloadsWarning()
{
    resize(100,100);
    wasOkCliked = false;
    //QGroupBox *warningGroup = new QGroupBox;

    QLabel *pic = new QLabel;
    //QImage image(":/images/warning.jpg");
    //pic->setPixmap(QPixmap::fromImage(image));

    //pic->show();

    QLabel *warningLabel = new QLabel(tr("Are you sure you want to cancel all downloads?\nClick OK to confirm"));

    //QVBoxLayout *warningLayout = new QVBoxLayout;
    //warningLayout->addWidget(pic);
    //warningLayout->addWidget(warningLabel);
    //warningGroup->setLayout(warningLayout);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(warningLabel);
    mainLayout->addSpacing(50);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &CancelDownloadsWarning::okButtonCliked);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &CancelDownloadsWarning::cancelButtonClicked);



}

void CancelDownloadsWarning::okButtonCliked()
{
    wasOkCliked = true;
    this->close();
}

void CancelDownloadsWarning::cancelButtonClicked()
{
    wasOkCliked = false;
    this->close();
}
