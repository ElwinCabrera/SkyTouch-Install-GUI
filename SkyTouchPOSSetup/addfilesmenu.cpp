#include "addfilesmenu.h"

AddFilesMenu::AddFilesMenu(SoftwareDownloadPage *sPage , QWidget *parent) : QWidget(parent)
{
    this->sPage = sPage;
    init();
}

AddFilesMenu::~AddFilesMenu()
{
    qDebug() << "AddFilesMenu Destructor";

    for(LocalFile *lf: localFilesSet){
        if(lf) delete lf;
    }
    localFilesSet.clear();


    for(auto it = btnToFile.begin(); it != btnToFile.end(); ++it){
        if(it.key()) delete it.key();
        if(it.value()) delete it.value();
    }
    btnToFile.clear();

    /*if(mainLayout) delete mainLayout;
    if(scrollAreaLayout) delete scrollAreaLayout;
    if(scrollArea) delete scrollArea;*/
    if(mainLayout) clearLayotAndWidgets(mainLayout);

}

void AddFilesMenu::init(){
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

    for(LocalFile *lf: localFilesSet){


        QVBoxLayout *contentsLayout = getLinkInfoLayoutAndWidgets(lf);

        QGroupBox *gBox = new QGroupBox;
        gBox->setMinimumWidth(400);

        QPushButton *deleteBtn = new QPushButton(tr("Delete"));
        QHBoxLayout *btnLayout = new QHBoxLayout;
        btnLayout->addWidget(deleteBtn);
        btnLayout->addStretch(1);

        contentsLayout->addLayout(btnLayout);
        gBox->setLayout(contentsLayout);

        scrollAreaLayout->addWidget(gBox);


        btnToFile.insert(deleteBtn, lf);

        connect(deleteBtn, &QPushButton::clicked, this, &AddFilesMenu::deleteFileInput);

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
    connect(addBtn, &QPushButton::clicked, this, &AddFilesMenu::addFile);
}

void AddFilesMenu::addFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select Executable",QDir::homePath(),"All Files(*.*)");
    QStringList parts = filePath.split(QDir::separator());
    QString fileName = parts.at(parts.size()-1);



    if(!filePath.isEmpty() && !filePath.isNull()) {
        LocalFile *newLf = new LocalFile(fileName, filePath, false);

        localFilesSet.insert(newLf);

        if(sPage) sPage->addToLocalFileMap(fileName,newLf);
        init();

    }
}


void AddFilesMenu::deleteFileInput()
{
    QObject* senderObj = sender();
       if (senderObj->isWidgetType()){
           QPushButton* button = qobject_cast<QPushButton*>(senderObj);
           if (button){
              auto it = btnToFile.find(button);
              if(it != btnToFile.end()) {

                  LocalFile *lf = it.value();
                  localFilesSet.erase(localFilesSet.find(lf));

                  if(sPage) sPage->removeFromLocalFileMap(lf->getFileName());

                  delete lf;
                  init();
              }
           }
       }
}




QVBoxLayout* AddFilesMenu::getLinkInfoLayoutAndWidgets(LocalFile *lf){

    QLabel *fileNameLabel = new QLabel(tr("File Name:"));
    QLabel *pathLabel = new QLabel(tr("Path:"));

    QLineEdit *fileNameInput = new QLineEdit;
    QLineEdit *pathInput = new QLineEdit;

    fileNameInput->setText(lf->getFileName());
    pathInput->setText(lf->getFilePath());

    fileNameInput->setEnabled(false);
    pathInput->setEnabled(false);


    QVBoxLayout *contentsLayout = new QVBoxLayout;
    contentsLayout->addWidget(fileNameLabel);
    contentsLayout->addWidget(fileNameInput);

    contentsLayout->addWidget(pathLabel);
    contentsLayout->addWidget(pathInput);

    return contentsLayout;
}
