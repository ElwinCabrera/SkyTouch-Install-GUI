#include "mainwindow.h"
//#include "ui_mainwindow.h"
#include <QtWidgets>


MainWindow::MainWindow(QWidget *parent) /*: QMainWindow(parent), ui(new Ui::MainWindow)*/ {
    //ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

    network = new Network;

    menuBar = new QMenuBar;
    statusBar = new QStatusBar;
    createMenuActions();
    createMenu();


    SoftwareInfo *si= new SoftwareInfo("CRE", "http://download2.pcamerica.com/12.9/CRE_Setup.exe", "http://download2.pcamerica.com/12.9/CRE_Setup_x64.exe");
    softwareList.push_back(si);

    SoftwareInfo *si1= new SoftwareInfo("CRE1", "http://download2.pcamerica.com/12.9/CRE_Setup.exe", "http://download2.pcamerica.com/12.9/CRE_Setup_x64.exe" );
    softwareList.push_back(si1);

    SoftwareInfo *si2= new SoftwareInfo("CRE2", "http://download2.pcamerica.com/12.9/CRE_Setup.exe", "http://download2.pcamerica.com/12.9/CRE_Setup_x64.exe" );
    softwareList.push_back(si2);

    SoftwareInfo *si3= new SoftwareInfo("CRE3", "http://download2.pcamerica.com/12.9/CRE_Setup.exe", "http://download2.pcamerica.com/12.9/CRE_Setup_x64.exe" );
    softwareList.push_back(si3);

    contentsWidget = new QListWidget;
    contentsWidget->setViewMode(QListView::IconMode);
    contentsWidget->setIconSize(QSize(96, 84));
    contentsWidget->setMovement(QListView::Static);
    contentsWidget->setMaximumWidth(128);
    contentsWidget->setMinimumWidth(128);
    contentsWidget->setSpacing(12);

    pagesWidget = new QStackedWidget;
    softwareDownloadPage = new SoftwareDownloadPage(this);
    softwareDownloadPage->initPage(softwareList, network);

    pagesWidget->addWidget(softwareDownloadPage);
    pagesWidget->addWidget(new ConfigurationPage);


    createIcons();
    contentsWidget->setCurrentRow(100);

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(contentsWidget);
    horizontalLayout->addWidget(pagesWidget, 1);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(menuBar);
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addStretch(100);
    mainLayout->addSpacing(12);
    //mainLayout->addLayout(buttonsLayout);
    mainLayout->addWidget(statusBar);
    setLayout(mainLayout);

    setWindowTitle(tr("SkyTouch POS Setup"));
    statusBar->showMessage(tr("Ready"));


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



void MainWindow::createMenuActions(){
    browseFilesAct = new QAction(tr("&Add Local Files"), this);
    browseFilesAct->setShortcuts(QKeySequence::New);
    browseFilesAct->setStatusTip(tr("Search for local files to be installed"));
    //connect(browseFilesAct, &QAction::triggered, this, &MainWindow::browseFiles);

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcuts(QKeySequence::New);
    exitAct->setStatusTip(tr("Close Application"));
    connect(exitAct, &QAction::triggered, this, &MainWindow::exitApp);

    linksAct = new QAction(tr("&Download Links"),this);
    linksAct->setShortcuts(QKeySequence::New);
    linksAct->setStatusTip(tr("Add, Edit, Delete a download link"));
    //connect(linksAct, &QAction::triggered, this, &MainWindow::modifyDownloadLinks);

    addToWinRegistryAct = new QAction(tr("&Windows Registry"),this);
    addToWinRegistryAct->setShortcuts(QKeySequence::New);
    addToWinRegistryAct->setStatusTip(tr("Add, Edit, Delete a windows registry file"));
    //connect(addToWinRegistryAct, &QAction::triggered, this, &MainWindow::modifyWindowsReg);

    optionsAct = new QAction(tr("&Options"),this);
    optionsAct->setShortcuts(QKeySequence::New);
    optionsAct->setStatusTip(tr("Application Options"));
    //connect(optionsAct, &QAction::triggered, this, &MainWindow::appOptions);

    reportBugAct = new QAction(tr("&Report Bugs"),this);
    reportBugAct->setShortcuts(QKeySequence::New);
    //reportBugAct->setStatusTip(tr("Application Options"));
    //connect(reportBugAct, &QAction::triggered, this, &MainWindow::reportBugs);

    aboutAct = new QAction(tr("&About"),this);
    aboutAct->setShortcuts(QKeySequence::New);
    aboutAct->setStatusTip(tr("About this application"));
    //connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

    aboutSkyTouchAct = new QAction(tr("&About SkyTouch"), this);
    aboutSkyTouchAct->setShortcuts(QKeySequence::New);
    aboutSkyTouchAct->setStatusTip(tr("About SkyTouch"));
    //connect(aboutSkyTouchAct, &QAction::triggered, this, &MainWindow::aboutSkyTouch);


}
void MainWindow::createMenu(){

    fileMenu = menuBar->addMenu(tr("&File"));
    fileMenu->addAction(browseFilesAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar->addMenu(tr("&Edit"));
    editMenu->addAction(linksAct);
    editMenu->addAction(addToWinRegistryAct);
    editMenu->addSeparator();
    editMenu->addAction(optionsAct);

    helpMenu = menuBar->addMenu(tr("&Help"));
    helpMenu->addAction(reportBugAct);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutSkyTouchAct);
}

void MainWindow::changePage(QListWidgetItem *current, QListWidgetItem *previous){
    if (!current)
        current = previous;

    pagesWidget->setCurrentIndex(contentsWidget->row(current));
}

void MainWindow::exitApp()
{
    qDebug() << "menu Exit pressed";

}

//void MainWindow::addMenuBar(){


//}
