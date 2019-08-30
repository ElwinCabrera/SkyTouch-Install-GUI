#include "usereditregistry.h"


UserEditReg::UserEditReg(QStandardItem *customPolicies, RegistryHandler *regHan, QWidget *parent): QWidget(parent)
{
    this->customPolicies = customPolicies;
    this->regHan = regHan;
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
    setMinimumHeight(450);
    setMinimumWidth(450);

    //setMaximumHeight(400);

    mainLayout = new QVBoxLayout;
    scrollArea = new QScrollArea;
    QWidget *saWidget = new QWidget;



    scrollAreaLayout = new QVBoxLayout;

    for(UserRegistryItem *ri: userRegSet){


        QVBoxLayout *contentsLayout = getRegInfoLayoutAndWidgets(ri->getKey(), ri->getValueName(), ri->getData(), ri->getDescription());

        QGroupBox *gBox = new QGroupBox;
        gBox->setMinimumWidth(400);

        QPushButton *deleteBtn = new QPushButton(tr("Delete"));
        QHBoxLayout *btnLayout = new QHBoxLayout;
        btnLayout->addWidget(deleteBtn);
        btnLayout->addStretch(1);

        contentsLayout->addLayout(btnLayout);
        gBox->setLayout(contentsLayout);

        scrollAreaLayout->addWidget(gBox);


        btnToItem.insert(deleteBtn, ri);

        connect(deleteBtn, &QPushButton::clicked, this, &UserEditReg::deleteRegInput);

    }

    saWidget->setLayout(scrollAreaLayout);
    scrollArea->setWidget(saWidget);


    QPushButton *closeBtn = new QPushButton(tr("Close"));
    //QPushButton *saveBtn = new QPushButton(tr("Save"));
    QPushButton *addBtn = new QPushButton(tr("Add New"));

    QHBoxLayout *btnLayout = new QHBoxLayout;
    if(closeBtnEnable) btnLayout->addWidget(closeBtn);
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
        userRegSet.insert(regItem);
        //insert to registry and update standard item
        regHan->addReg(regItem->getKey(), regItem->getValueName(), regItem->getData());
        populateUserPolicyEntries(regItem);
        init();
    }
    delete inputReg;
}
void UserEditReg::populateUserPolicyEntries(UserRegistryItem *regItem){
    QList<QStandardItem*> row;

    QStandardItem *customName = new QStandardItem(regItem->getDescription());
    QStandardItem *customNameRegVal = new QStandardItem(regHan->getCurrRegDataVal(regItem->getValueName()));
    QStandardItem *customNameRegKeyName = new QStandardItem(regItem->getValueName());
    QStandardItem *customNameDataType = new QStandardItem(regItem->getDataType());

    customName->setCheckable(true);
    customName->setCheckState(Qt::Checked);
    customName->setEditable(false);
    customNameRegVal->setEditable(false);

    row.append(customName);
    row.append(customNameRegVal);
    row.append(customNameRegKeyName);
    row.append(customNameDataType);
    customPolicies->appendRow(row);

}

void UserEditReg::deleteRegInput()
{
    QObject* senderObj = sender();
       if (senderObj->isWidgetType()){
           QPushButton* button = qobject_cast<QPushButton*>(senderObj);
           if (button){
              auto it = btnToItem.find(button);
              if(it != btnToItem.end()) {
                  UserRegistryItem *item = it.value();
                  auto regSetIt = userRegSet.find(item);
                  userRegSet.erase(regSetIt);

                  regHan->deleteKey(item->getValueName());
                  removeFromTree(item->getValueName());
                  delete item;
                  init();

              }
           }
       }
}

void UserEditReg::removeFromTree(QString policyName){
    int row = 0;
    for(; row < customPolicies->rowCount(); ++row){
        if(customPolicies->child(row, 2)->text() == policyName) break;
    }
    customPolicies->removeRow(row);

}



QVBoxLayout* UserEditReg::getRegInfoLayoutAndWidgets( QString key, QString valueName, QVariant data, QString desc){

    QLabel *keyLabel = new QLabel(tr("Key:"));
    QLabel *valueNameLabel = new QLabel(tr("Value Name:"));
    QLabel *valueLabel = new QLabel(tr("Data:"));

    QLineEdit *descInput = new QLineEdit;
    QLineEdit *keyTextInput = new QLineEdit;
    QLineEdit *valueNameInput = new QLineEdit;
    QLineEdit *valueInput = new QLineEdit;

    descInput->setText(desc);
    keyTextInput->setText(key);
    valueNameInput->setText(valueName);
    valueInput->setText(data.toString());

    descInput->setEnabled(false);
    keyTextInput->setEnabled(false);
    valueNameInput->setEnabled(false);
    valueInput->setEnabled(false);


//    QPushButton *deleteBtn = new QPushButton(tr("Delete"));
//    QHBoxLayout *btnLayout = new QHBoxLayout;

//    btnLayout->addWidget(deleteBtn);
//    btnLayout->addStretch(1);

    QVBoxLayout *contentsLayout = new QVBoxLayout;
    contentsLayout->addWidget(keyLabel);
    contentsLayout->addWidget(keyTextInput);

    contentsLayout->addWidget(valueNameLabel);
    contentsLayout->addWidget(valueNameInput);

    contentsLayout->addWidget(valueLabel);
    contentsLayout->addWidget(valueInput);

    //contentsLayout->addLayout(btnLayout);

    //connect(deleteBtn, &QPushButton::clicked, this, &UserEditReg::deleteRegInput);

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
    if(( !numberBtn->isChecked() && !binaryBtn->isChecked() &&
       !stringBtn->isChecked() && !pathBtn->isChecked() ) || (keyTextInput->text() == "" ||
            valueNameInput->text() == "" || valueInput->text() == ""))
    {
        messageBox("Input Fields Empty", "Some or all imput fields are empty, cannot save");
        return;
    }
    if(descInput->text() == "") {
        int msgRet = messageBox("Saving Without Description", "Are you sure you want to save without a description?\nClick Ok to save without a description, or Close to continue editing.");
        if(msgRet != QMessageBox::Ok) return;
    }

    saved = true;
    QVariant data ;

    if(numberBtn->isChecked() || binaryBtn->isChecked()) data =  valueInput->text().toInt();
    else data = valueInput->text();

    QString dataType;

    if(stringBtn->isChecked()) dataType = "STRING";
    else if(pathBtn->isChecked()) dataType = "PATH";
    else dataType = "DWORD";

    if(regItem == nullptr) {
        regItem = new UserRegistryItem(keyTextInput->text(), valueNameInput->text(), data, dataType, descInput->text());
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

    QLabel *descLabel = new QLabel(tr("Enter Description:"));
    QLabel *keyLabel = new QLabel(tr("Enter Key or subkey:"));
    QLabel *valueNameLabel = new QLabel(tr("Enter a Name for the Value:"));
    QLabel *valueLabel = new QLabel(tr("Enter the Value or Data:"));

    descInput = new QLineEdit;
    keyTextInput = new QLineEdit;
    valueNameInput = new QLineEdit;
    valueInput = new QLineEdit;

    descInput->setPlaceholderText("Description");
    keyTextInput->setPlaceholderText("Key");
    valueNameInput->setPlaceholderText("Name");
    valueInput->setPlaceholderText("Data");


    stringBtn = new QRadioButton(tr("Text (String)"));
    pathBtn = new QRadioButton(tr("Path"));
    numberBtn = new QRadioButton(tr("Number (DWORD)"));
    binaryBtn = new QRadioButton(tr("Binary"));

    QHBoxLayout *radioBtnsLayout = new QHBoxLayout;
    radioBtnsLayout->addWidget(stringBtn);
    radioBtnsLayout->addWidget(pathBtn);
    radioBtnsLayout->addWidget(numberBtn);
    radioBtnsLayout->addWidget(binaryBtn);


    QVBoxLayout *contentsLayout = new QVBoxLayout;
    contentsLayout->addWidget(descLabel);
    contentsLayout->addWidget(descInput);

    contentsLayout->addWidget(keyLabel);
    contentsLayout->addWidget(keyTextInput);

    contentsLayout->addWidget(valueNameLabel);
    contentsLayout->addWidget(valueNameInput);

    contentsLayout->addWidget(valueLabel);
    contentsLayout->addWidget(valueInput);

    contentsLayout->addLayout(radioBtnsLayout);

    return contentsLayout;
}
