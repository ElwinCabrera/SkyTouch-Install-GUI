#include "warningbox.h"

WarningBox::WarningBox(QString warningMessage)
{
    resize(100,100);

    //QGroupBox *warningGroup = new QGroupBox;

    /*QLabel pic;
    QImage image(":/images/warning.jpg");
    pic.setPixmap(QPixmap::fromImage(image));

    pic.show();*/
    QString message = warningMessage + "\nClick OK to confirm.";
    QLabel *warningLabel = new QLabel(message);

    /*QVBoxLayout *warningLayout = new QVBoxLayout;
    warningLayout->addWidget(pic);
    warningLayout->addWidget(warningLabel);
    warningGroup->setLayout(warningLayout);*/

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(warningLabel);
    mainLayout->addSpacing(50);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &WarningBox::okButtonCliked);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &WarningBox::cancelButtonClicked);



}

void WarningBox::okButtonCliked()
{
    isConfirmed = true;
    this->close();
}

void WarningBox::cancelButtonClicked()
{
    isConfirmed = false;
    this->close();
}
