#include "usereditlinks.h"

UserEditLinks::UserEditLinks(vector<SoftwareInfo*> &softwareList, SoftwareDownloadPage *sPage , QWidget *parent): QWidget(parent)
{
    this->sPage = sPage;
    this->globalSoftwareList = softwareList;
    init();
}

UserEditLinks::~UserEditLinks()
{

}

void UserEditLinks::init(){
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

    for(SoftwareInfo *si: userSoftwreLinks){


        QVBoxLayout *contentsLayout = getLinkInfoLayoutAndWidgets(si);

        QGroupBox *gBox = new QGroupBox;
        gBox->setMinimumWidth(400);

        QPushButton *deleteBtn = new QPushButton(tr("Delete"));
        QHBoxLayout *btnLayout = new QHBoxLayout;
        btnLayout->addWidget(deleteBtn);
        btnLayout->addStretch(1);

        contentsLayout->addLayout(btnLayout);
        gBox->setLayout(contentsLayout);

        scrollAreaLayout->addWidget(gBox);


        btnToLink.insert(deleteBtn, si);

        connect(deleteBtn, &QPushButton::clicked, this, &UserEditLinks::deleteLinkInput);

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
    connect(addBtn, &QPushButton::clicked, this, &UserEditLinks::addLink);
}

void UserEditLinks::addLink()
{
    InputLinkDialog *input = new InputLinkDialog;
    input->setModal(true);
    input->exec();

    if(input->getSaved()) {
        SoftwareInfo *newSoftwareLink = input->getNewLink();
        userSoftwreLinks.insert(newSoftwareLink);
        //update the UI screan on the softeare Tab
        //populateUserPolicyEntries(input);
        init();
        globalSoftwareList.push_back(newSoftwareLink);
        if(sPage && sPage->onInitPage()) {
            vector<SoftwareInfo*> tmp;
            sPage->initPage(globalSoftwareList, nullptr);
        }
    }
    delete input;
}


void UserEditLinks::deleteLinkInput()
{
    QObject* senderObj = sender();
       if (senderObj->isWidgetType()){
           QPushButton* button = qobject_cast<QPushButton*>(senderObj);
           if (button){
              auto it = btnToLink.find(button);
              if(it != btnToLink.end()) {
                  SoftwareInfo *si = it.value();
                  userSoftwreLinks.erase(userSoftwreLinks.find(si));
                  deleteInGlobalList(si);

                  delete si;
                  init();

                  if(sPage && sPage->onInitPage()){
                      vector<SoftwareInfo*> tmp;
                      sPage->initPage(globalSoftwareList, nullptr);
                  }

              }
           }
       }
}

void UserEditLinks::deleteInGlobalList(SoftwareInfo *si){
    for(int i = 0; globalSoftwareList.size(); ++i){
        if(globalSoftwareList.at(i) == si) globalSoftwareList.erase(globalSoftwareList.begin() + i);
    }
}




QVBoxLayout* UserEditLinks::getLinkInfoLayoutAndWidgets(SoftwareInfo *si){

    QLabel *nameLabel = new QLabel(tr("Name:"));
    QLabel *bit32Label = new QLabel(tr("32Bit URL:"));
    QLabel *bit64Label = new QLabel(tr("64Bit URL:"));

    QLineEdit *nameInput = new QLineEdit;
    QLineEdit *bit32Input = new QLineEdit;
    QLineEdit *bit64Input = new QLineEdit;

    nameInput->setText(si->getFileName32()+ ", " +si->getFileName64());
    bit32Input->setText(si->get32BitURL());
    bit64Input->setText(si->get64BitURL());


    nameInput->setEnabled(false);
    bit32Input->setEnabled(false);
    bit64Input->setEnabled(false);

//    QPushButton *deleteBtn = new QPushButton(tr("Delete"));
//    QHBoxLayout *btnLayout = new QHBoxLayout;

//    btnLayout->addWidget(deleteBtn);
//    btnLayout->addStretch(1);

    QVBoxLayout *contentsLayout = new QVBoxLayout;
    contentsLayout->addWidget(nameLabel);
    contentsLayout->addWidget(nameInput);

    contentsLayout->addWidget(bit32Label);
    contentsLayout->addWidget(bit32Input);

    contentsLayout->addWidget(bit64Label);
    contentsLayout->addWidget(bit64Input);

    //contentsLayout->addLayout(btnLayout);

    //connect(deleteBtn, &QPushButton::clicked, this, &UserEditLinks::deleteRegInput);

    return contentsLayout;
}


















InputLinkDialog::InputLinkDialog(QWidget *parent)
{

    init();
}

InputLinkDialog::~InputLinkDialog()
{

}

void InputLinkDialog::init()
{
    if(mainLayout){
        disconnect(mainLayout, 0,0,0);
        clearLayotAndWidgets(mainLayout);
        mainLayout = nullptr;
    }
    mainLayout = new QVBoxLayout;
    QVBoxLayout *contentsLayout = addNewLink();


    QPushButton *saveBtn = new QPushButton(tr("Save"));
    QPushButton *cancelBtn = new QPushButton(tr("Cancel"));

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addWidget(cancelBtn);
    btnLayout->addWidget(saveBtn);

    mainLayout->addLayout(contentsLayout);
    mainLayout->addLayout(btnLayout);

    setLayout(mainLayout);

    connect(cancelBtn, &QPushButton::clicked, this, &InputLinkDialog::closeWin);
    connect(saveBtn, &QPushButton::clicked, this, &InputLinkDialog::saveLinkEntry);
}



void InputLinkDialog::saveLinkEntry()
{
    if(!isValidInput()){
        messageBox("Input Fields Empty", "Cannot save, Some or all imput fields are empty.","Error");
        return;
    }



    if(softwareLink == nullptr) {
        softwareLink = new SoftwareInfo(nameInput->text(), bit32Input->text(), bit64Input->text());
        saved = true;
        this->close();
    } else {
       saved = false;
       int msgReturn = messageBox("Error in saving entry", "Could not save entry. Click OK to try again or Cancel to cancel.");
       if(msgReturn == QMessageBox::Cancel) this->close();
    }

}

bool InputLinkDialog::isValidInput(){

    if(nameInput->text() == "") return false;

    if(bit32Btn->isChecked()){
        if(bit32Input->text() == "") return false;
    } else if (bit64Btn->isChecked()){
        if(bit64Input->text() == "") return false;
    } else if (bothBtn->isChecked()) {
        if(bit32Input->text() == "" || bit32Input->text() == "") return false;
    } else if (dontKnowBtn->isChecked()) {
        if(bit32Input->text() == "") return false;
    } else {
        return false;
    }

    return true;
}

void InputLinkDialog::closeWin()
{
    if(nameInput->text() != "" || bit32Input->text() != "" || bit64Input->text() != "") {
        int msgRet = messageBox("Close Without Saving", "You are currently editing this are you sure you want to close without saving?");
        if(msgRet == QMessageBox::Ok) this->close();
    } else this->close();


}

void InputLinkDialog::onVersionSelect()
{
    firstCall = false;

    nameInputText = nameInput->text();
    bit32BtnChecked = bit32Btn->isChecked();
    bit64BtnChecked = bit64Btn->isChecked();
    bothBtnChecked = bothBtn->isChecked();
    dontKnowBtnChecked = dontKnowBtn->isChecked();

    //make sure to clear all other things so you wont save a 64 bit when the user swichrd to only 32 bit
    init();
}




QVBoxLayout* InputLinkDialog::addNewLink(){



    QLabel *nameLabel;
    QLabel *bit32Label;
    QLabel *bit64Label;
    QLabel *dontKnowBitLabel;



    nameLabel = new QLabel(tr("Enter Name:"));
    bit32Label = new QLabel(tr("Enter 32 Bit Link:"));
    bit64Label = new QLabel(tr("Enter 32 Bit Link:"));
    dontKnowBitLabel = new QLabel(tr("Enter Link:"));

    bit32Btn = new QRadioButton(tr("I only have 32Bit Link"));
    bit64Btn = new QRadioButton(tr("I only have 64Bit Link"));
    bothBtn = new QRadioButton(tr("I have both Links"));
    dontKnowBtn = new QRadioButton(tr("I don't know"));

    bit32Btn->setChecked(bit32BtnChecked);
    bit64Btn->setChecked(bit64BtnChecked);
    bothBtn->setChecked(bothBtnChecked);
    dontKnowBtn->setChecked(dontKnowBtnChecked);

    nameInput = new QLineEdit;
    bit32Input = new QLineEdit;
    bit64Input = new QLineEdit;

    if(nameInputText == "") nameInput->setPlaceholderText("File Name");
    else nameInput->setText(nameInputText);



    QHBoxLayout *radioBtnsLayout = new QHBoxLayout;
    radioBtnsLayout->addWidget(bit32Btn);
    radioBtnsLayout->addWidget(bit64Btn);
    radioBtnsLayout->addWidget(bothBtn);
    radioBtnsLayout->addWidget(dontKnowBtn);


    QVBoxLayout *contentsLayout = new QVBoxLayout;

    contentsLayout->addWidget(nameLabel);
    contentsLayout->addWidget(nameInput);

    contentsLayout->addLayout(radioBtnsLayout);

    if(bit32Btn->isChecked()){
        contentsLayout->addWidget(bit32Label);
        contentsLayout->addWidget(bit32Input);
        bit32Input->setPlaceholderText("32Bit URL");
    }

    if(bit64Btn->isChecked()){
        contentsLayout->addWidget(bit64Label);
        contentsLayout->addWidget(bit64Input);
        bit64Input->setPlaceholderText("64Bit URL");
    }

    if(bothBtn->isChecked()){
        contentsLayout->addWidget(bit32Label);
        contentsLayout->addWidget(bit32Input);
        bit32Input->setPlaceholderText("32Bit URL");

        contentsLayout->addWidget(bit64Label);
        contentsLayout->addWidget(bit64Input);
        bit64Input->setPlaceholderText("64Bit URL");
    }

    if(dontKnowBtn->isChecked()){
        contentsLayout->addWidget(dontKnowBitLabel);
        contentsLayout->addWidget(bit32Input);
        bit32Input->setPlaceholderText("32Bit URL");
    }



    disconnect(bit32Btn, 0, 0, 0);
    disconnect(bit64Btn, 0, 0, 0);
    disconnect(bothBtn, 0, 0, 0);
    disconnect(dontKnowBtn, 0, 0, 0);

    connect(bit32Btn, &QRadioButton::toggled, this, &InputLinkDialog::onVersionSelect);
    connect(bit64Btn, &QRadioButton::toggled, this, &InputLinkDialog::onVersionSelect);
    connect(bothBtn, &QRadioButton::toggled, this, &InputLinkDialog::onVersionSelect);
    connect(dontKnowBtn, &QRadioButton::toggled, this, &InputLinkDialog::onVersionSelect);




    return contentsLayout;
}
