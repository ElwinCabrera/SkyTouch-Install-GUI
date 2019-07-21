#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>


MainWindow::MainWindow(QWidget *parent) /*: QMainWindow(parent), ui(new Ui::MainWindow)*/ {
    //ui->setupUi(this);
    network = new Network;
    SoftwareInfo *si= new SoftwareInfo("CRE", "http://download2.pcamerica.com/12.9/CRE_Setup.exe", "http://download2.pcamerica.com/12.9/CRE_Setup_x64.exe",true, false );
    softwareList.push_back(si);

    /*SoftwareInfo *si1= new SoftwareInfo("CRE1", "http://download2.pcamerica.com/12.9/CRE_Setup.exe", "http://download2.pcamerica.com/12.9/CRE_Setup_x64.exe",false, false );
    softwareList.push_back(si1);

    SoftwareInfo *si2= new SoftwareInfo("CRE2", "http://download2.pcamerica.com/12.9/CRE_Setup.exe", "http://download2.pcamerica.com/12.9/CRE_Setup_x64.exe",false, false );
    softwareList.push_back(si2);

    SoftwareInfo *si3= new SoftwareInfo("CRE3", "http://download2.pcamerica.com/12.9/CRE_Setup.exe", "http://download2.pcamerica.com/12.9/CRE_Setup_x64.exe",false, false );
    softwareList.push_back(si3);*/

    contentsWidget = new QListWidget;
    contentsWidget->setViewMode(QListView::IconMode);
    contentsWidget->setIconSize(QSize(96, 84));
    contentsWidget->setMovement(QListView::Static);
    contentsWidget->setMaximumWidth(128);
    contentsWidget->setSpacing(12);

    pagesWidget = new QStackedWidget;
    softwareDownloadPage = new SoftwareDownloadPage;
    softwareDownloadPage->initPage(softwareList, network);

    pagesWidget->addWidget(softwareDownloadPage);
    pagesWidget->addWidget(new ConfigurationPage);



    QPushButton *closeButton = new QPushButton(tr("Close"));

    createIcons();
    contentsWidget->setCurrentRow(100);

    connect(closeButton, &QAbstractButton::clicked, this, &QWidget::close);

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(contentsWidget);
    horizontalLayout->addWidget(pagesWidget, 1);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addStretch(100);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Config Dialog"));




}

MainWindow::~MainWindow()
{
    //delete ui;
}

void MainWindow::createIcons(){
    QListWidgetItem *configButton = new QListWidgetItem(contentsWidget);
    configButton->setIcon(QIcon(":/images/update.png"));
    configButton->setText(tr("Software"));
    configButton->setTextAlignment(Qt::AlignHCenter);
    configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *updateButton = new QListWidgetItem(contentsWidget);
    updateButton->setIcon(QIcon(":/images/config.png"));
    updateButton->setText(tr("Configuration"));
    updateButton->setTextAlignment(Qt::AlignHCenter);
    updateButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    /*QListWidgetItem *queryButton = new QListWidgetItem(contentsWidget);
    queryButton->setIcon(QIcon(":/images/query.png"));
    queryButton->setText(tr("Query"));
    queryButton->setTextAlignment(Qt::AlignHCenter);
    queryButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);*/

    connect(contentsWidget, &QListWidget::currentItemChanged, this, &MainWindow::changePage);
}

void MainWindow::changePage(QListWidgetItem *current, QListWidgetItem *previous){
    if (!current)
        current = previous;

    pagesWidget->setCurrentIndex(contentsWidget->row(current));
}
