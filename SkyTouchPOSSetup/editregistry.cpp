#include "editregistry.h"

UserEditReg::UserEditReg(QWidget *parent)
{
    init();

}

UserEditReg::~UserEditReg()
{

}

void UserEditReg::init(){
    if(mainLayout) {
        clearLayotAndWidgets(mainLayout);
        mainLayout = nullptr;
    }
    //resize(QSize(390,250));
    setMinimumHeight(250);
    setMinimumWidth(390);

    //setMaximumHeight(400);

    mainLayout = new QVBoxLayout;
    scrollArea = new QScrollArea;
    QWidget *saWidget = new QWidget;



    scrollAreaLayout = new QVBoxLayout;

    for(UserRegistryItem *ri: userRegList){

        QVBoxLayout *contentsLayout = getRegInfoLayoutAndWidgets(ri->getKey(), ri->getValueName(), ri->getData());
        QGroupBox *gBox = new QGroupBox;
        gBox->setMinimumWidth(400);
        gBox->setLayout(contentsLayout);
        scrollAreaLayout->addWidget(gBox);

    }

    saWidget->setLayout(scrollAreaLayout);
    scrollArea->setWidget(saWidget);


    QPushButton *closeBtn = new QPushButton(tr("Close"));
    //QPushButton *saveBtn = new QPushButton(tr("Save"));
    QPushButton *addBtn = new QPushButton(tr("Add New"));

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addWidget(closeBtn);
    //btnLayout->addWidget(saveBtn);
    btnLayout->addWidget(addBtn);

    mainLayout->addWidget(scrollArea);
    mainLayout->addLayout(btnLayout);
    setLayout(mainLayout);

    connect(closeBtn, &QPushButton::clicked, this, &QWidget::close);
    connect(addBtn, &QPushButton::clicked, this, &UserEditReg::addRegItem);
}

void UserEditReg::addRegItem()
{
    InputRegDialog *inputReg = new InputRegDialog;
    inputReg->setModal(true);
    inputReg->exec();

    if(inputReg->getSaved()) {
        UserRegistryItem *regItem = inputReg->getRegItem();
        userRegList.append(regItem);
        init();
    }
    delete inputReg;
}

void UserEditReg::deleteRegInput()
{

}



QVBoxLayout* UserEditReg::getRegInfoLayoutAndWidgets(QString key, QString valueName, QVariant data){

    QLabel *keyLabel = new QLabel(tr("Key:"));
    QLabel *valueNameLabel = new QLabel(tr("Value Name:"));
    QLabel *valueLabel = new QLabel(tr("Data:"));

    QLineEdit *keyTextInput = new QLineEdit;
    QLineEdit *valueNameInput = new QLineEdit;
    QLineEdit *valueInput = new QLineEdit;
    keyTextInput->setText(key);
    valueNameInput->setText(valueName);
    valueInput->setText(data.toString());
    keyTextInput->setEnabled(false);

    valueNameInput->setEnabled(false);
    valueInput->setEnabled(false);


    QPushButton *deleteBtn = new QPushButton(tr("Delete"));
    QHBoxLayout *btnLayout = new QHBoxLayout;

    btnLayout->addWidget(deleteBtn);
    btnLayout->addStretch(1);

    QVBoxLayout *contentsLayout = new QVBoxLayout;
    contentsLayout->addWidget(keyLabel);
    contentsLayout->addWidget(keyTextInput);

    contentsLayout->addWidget(valueNameLabel);
    contentsLayout->addWidget(valueNameInput);

    contentsLayout->addWidget(valueLabel);
    contentsLayout->addWidget(valueInput);

    contentsLayout->addLayout(btnLayout);

    connect(deleteBtn, &QPushButton::clicked, this, &UserEditReg::deleteRegInput);

    return contentsLayout;
}


















InputRegDialog::InputRegDialog(QWidget *parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QVBoxLayout *contentsLayout = addNewRegItem();


    QPushButton *saveBtn = new QPushButton(tr("Save"));
    QPushButton *cancelBtn = new QPushButton(tr("Cancel"));

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addWidget(cancelBtn);
    btnLayout->addWidget(saveBtn);

    mainLayout->addLayout(contentsLayout);
    mainLayout->addLayout(btnLayout);

    setLayout(mainLayout);

    connect(cancelBtn, &QPushButton::clicked, this, &InputRegDialog::closeWin);
    connect(saveBtn, &QPushButton::clicked, this, &InputRegDialog::saveRegEntry);

}

InputRegDialog::~InputRegDialog()
{

}



void InputRegDialog::saveRegEntry()
{
    if(!numberBtn->isChecked() || !binaryBtn->isChecked() ||
       !stringBtn->isChecked() || keyTextInput->text() == "" ||
            valueNameInput->text() == "" || valueInput->text() == "")
    {
        messageBox("Input Fields Empty", "Some or all imput fields are empty, cannot save");
        return;
    }
    saved = true;
    QVariant data ;

    if(numberBtn->isChecked() || binaryBtn->isChecked()) data =  valueInput->text().toInt();
    else data = valueInput->text();

    if(regItem == nullptr) {
        regItem = new UserRegistryItem(keyTextInput->text(), valueNameInput->text(), data);
        this->close();
    } else {
       saved = false;
       int msgReturn = messageBox("Error in saving entry", "Could not save entry. Click OK to try again or Cancel to cancel.");
       if(msgReturn == QMessageBox::Cancel) this->close();

    }

}

void InputRegDialog::closeWin()
{
    if(keyTextInput->text() != "" || valueNameInput->text() != "" || valueInput->text() != "") {
        int msgRet = messageBox("Close Without Saving", "You are currently editing this are you sure you want to close without saving?");
        if(msgRet == QMessageBox::Ok) this->close();
    } else this->close();


}


QVBoxLayout* InputRegDialog::addNewRegItem(){

    QLabel *keyLabel = new QLabel(tr("Enter Key or subkey:"));
    QLabel *valueNameLabel = new QLabel(tr("Enter a Name for the Value:"));
    QLabel *valueLabel = new QLabel(tr("Enter the Value or Data:"));

    keyTextInput = new QLineEdit;
    valueNameInput = new QLineEdit;
    valueInput = new QLineEdit;

    keyTextInput->setPlaceholderText("Key");
    valueNameInput->setPlaceholderText("Name");
    valueInput->setPlaceholderText("Data");


    stringBtn = new QRadioButton(tr("Text (String)"));
    numberBtn = new QRadioButton(tr("Number (DWORD)"));
    binaryBtn = new QRadioButton(tr("Binary"));

    QHBoxLayout *radioBtnsLayout = new QHBoxLayout;
    radioBtnsLayout->addWidget(stringBtn);
    radioBtnsLayout->addWidget(numberBtn);
    radioBtnsLayout->addWidget(binaryBtn);


    QVBoxLayout *contentsLayout = new QVBoxLayout;
    contentsLayout->addWidget(keyLabel);
    contentsLayout->addWidget(keyTextInput);

    contentsLayout->addWidget(valueNameLabel);
    contentsLayout->addWidget(valueNameInput);

    contentsLayout->addWidget(valueLabel);
    contentsLayout->addWidget(valueInput);

    contentsLayout->addLayout(radioBtnsLayout);

    return contentsLayout;
}
