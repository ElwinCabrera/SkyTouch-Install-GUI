#include "mainwindow.h"
//#include "ui_mainwindow.h"
#include <QtWidgets>


MainWindow::MainWindow(QWidget *  /* parent unused */) /*: QMainWindow(parent), ui(new Ui::MainWindow)*/ {
    //ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
    resize(QSize(700, 500));

    network = new Network;

    menuBar = new QMenuBar;
    statusBar = new QStatusBar;
    createMenuActions();
    createMenu();


    SoftwareInfo *si= new SoftwareInfo("Cash Register Express", "http://download2.pcamerica.com/12.9/CRE_Setup.exe", "http://download2.pcamerica.com/12.9/CRE_Setup_x64.exe");
    softwareList.push_back(si);

    SoftwareInfo *si1= new SoftwareInfo("CRE1", "http://download2.pcamerica.com/12.9/CRE_Setup.exe", "http://download2.pcamerica.com/12.9/CRE_Setup_x64.exe" );
    softwareList.push_back(si1);

    SoftwareInfo *si2= new SoftwareInfo("CRE2", "http://download2.pcamerica.com/12.9/CRE_Setup.exe", "http://download2.pcamerica.com/12.9/CRE_Setup_x64.exe" );
    softwareList.push_back(si2);

    SoftwareInfo *si3= new SoftwareInfo("CRE3", "http://download2.pcamerica.com/12.9/CRE_Setup.exe", "http://download2.pcamerica.com/12.9/CRE_Setup_x64.exe" );
    softwareList.push_back(si3);

    QTabWidget *tabs = new QTabWidget(this);
    SoftwareDownloadPage *softwarePage= new SoftwareDownloadPage(this);
    softwarePage->initPage(softwareList, network);

    tabs->addTab(softwarePage, "Software");
    tabs->addTab(new ConfigurationPage(this), "Configuration");
    tabs->setTabPosition(QTabWidget::North);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(menuBar);
    mainLayout->addWidget(tabs);

    mainLayout->addWidget(statusBar);
    setLayout(mainLayout);

    setWindowTitle(tr("SkyTouch POS Setup"));
    statusBar->showMessage(tr("Ready"));


}

MainWindow::~MainWindow()
{
    //delete ui;
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


void MainWindow::exitApp()
{
    qDebug() << "menu Exit pressed";

}

//void MainWindow::addMenuBar(){


//}
