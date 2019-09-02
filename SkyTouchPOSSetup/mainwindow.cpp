#include "mainwindow.h"


MainWindow::MainWindow(QWidget *  /* parent unused */) /*: QMainWindow(parent), ui(new Ui::MainWindow)*/ {
    //ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
    resize(QSize(700, 500));

    network = new Network;
    regHan = new RegistryHandler;


    menuBar = new QMenuBar;
    statusBar = new QStatusBar;
    createMenuActions();
    createMenu();


    SoftwareInfo *si= new SoftwareInfo("Cash Register Express", "http://download2.pcamerica.com/12.9/CRE_Setup.exe", "http://download2.pcamerica.com/12.9/CRE_Setup_x64.exe");
    softwareList.insert(si);

    SoftwareInfo *si1= new SoftwareInfo("CRE1", "http://download2.pcamerica.com/12.9/CRE_Setup.exe", "http://download2.pcamerica.com/12.9/CRE_Setup_x64.exe" );
    softwareList.insert(si1);

    SoftwareInfo *si2= new SoftwareInfo("CRE2", "http://download2.pcamerica.com/12.9/CRE_Setup.exe", "http://download2.pcamerica.com/12.9/CRE_Setup_x64.exe" );
    softwareList.insert(si2);

    SoftwareInfo *si3= new SoftwareInfo("CRE3", "http://download2.pcamerica.com/12.9/CRE_Setup.exe", "http://download2.pcamerica.com/12.9/CRE_Setup_x64.exe" );
    softwareList.insert(si3);

    softwareTab= new SoftwareDownloadPage(softwareList,network,this);
    configTab = new ConfigurationPage(regHan,this);

    QTabWidget *tabs = new QTabWidget(this);
    tabs->addTab(softwareTab, "Software");
    tabs->addTab(configTab, "Configuration");
    tabs->setTabPosition(QTabWidget::North);

    editReg = new UserEditReg(configTab->getUserEntryItem(),regHan);
    editLink = new UserEditLinks(softwareTab);
    addFilesMenu = new AddFilesMenu(softwareTab);
    options = new OptionsMenu;
    reportBugs = new ReportBugsMenu;



    mainLayout = new QVBoxLayout;
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

    qDebug() << "MainWindow Destructor";

    for(SoftwareInfo *si: softwareList){
        if(si) delete si;
    }
    softwareList.clear();
    //if(menuBar) delete menuBar;
    //if(statusBar) delete statusBar;


   if(softwareTab) delete softwareTab;
   if(configTab) delete configTab;
   if(network) delete network;
   if(regHan) delete regHan;

   if(editReg) delete editReg;
   if(editLink) delete editLink;
   if(options) delete options;
   if(addFilesMenu) delete addFilesMenu;
   if(reportBugs) delete reportBugs;

   if(fileMenu) delete fileMenu;
   if(browseFilesAct) delete browseFilesAct;
   if(exitAct) delete exitAct;

   if(editMenu) delete editMenu;
   if(linksAct) delete linksAct;
   if(addToWinRegistryAct) delete addToWinRegistryAct;
   if(optionsAct) delete optionsAct;
   if(helpMenu) delete helpMenu;
   if(reportBugAct) delete reportBugAct;
   if(aboutAct) delete aboutAct;
   if(aboutSkyTouchAct) delete aboutSkyTouchAct;


   if(mainLayout) clearLayotAndWidgets(mainLayout);

}




void MainWindow::createMenuActions(){
    browseFilesAct = new QAction(tr("&Add Local Files"), this);
    browseFilesAct->setShortcuts(QKeySequence::New);
    browseFilesAct->setStatusTip(tr("Search for local files to be installed"));
    connect(browseFilesAct, &QAction::triggered, this, &MainWindow::browseFilesMenu);

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcuts(QKeySequence::New);
    exitAct->setStatusTip(tr("Close Application"));
    connect(exitAct, &QAction::triggered, this, &MainWindow::exitApp);

    linksAct = new QAction(tr("&Download Links"),this);
    linksAct->setShortcuts(QKeySequence::New);
    linksAct->setStatusTip(tr("Add, Edit, Delete a download link"));
    connect(linksAct, &QAction::triggered, this, &MainWindow::modifyDownloadLinks);

    addToWinRegistryAct = new QAction(tr("&Windows Registry"),this);
    addToWinRegistryAct->setShortcuts(QKeySequence::New);
    addToWinRegistryAct->setStatusTip(tr("Add, Edit, Delete a windows registry file"));
    connect(addToWinRegistryAct, &QAction::triggered, this, &MainWindow::modifyWindowsReg);

    optionsAct = new QAction(tr("&Options"),this);
    optionsAct->setShortcuts(QKeySequence::New);
    optionsAct->setStatusTip(tr("Application Options"));
    connect(optionsAct, &QAction::triggered, this, &MainWindow::appOptions);

    reportBugAct = new QAction(tr("&Report Bugs"),this);
    reportBugAct->setShortcuts(QKeySequence::New);
    //reportBugAct->setStatusTip(tr("Application Options"));
    connect(reportBugAct, &QAction::triggered, this, &MainWindow::reportBugsMenu);

    aboutAct = new QAction(tr("&About"),this);
    aboutAct->setShortcuts(QKeySequence::New);
    aboutAct->setStatusTip(tr("About this application"));
    connect(aboutAct, &QAction::triggered, this, &MainWindow::aboutMenu);

    aboutSkyTouchAct = new QAction(tr("&About SkyTouch"), this);
    aboutSkyTouchAct->setShortcuts(QKeySequence::New);
    aboutSkyTouchAct->setStatusTip(tr("About SkyTouch"));
    connect(aboutSkyTouchAct, &QAction::triggered, this, &MainWindow::aboutSkyTouchMenu);


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

void MainWindow::browseFilesMenu()
{
    addFilesMenu->setParent(nullptr);
    addFilesMenu->setCloseBtn(true);
    addFilesMenu->show();
}

void MainWindow::exitApp()
{
    qDebug() << "menu Exit pressed";
    //check for downlaod progress

}

void MainWindow::modifyWindowsReg()
{
    editReg->setParent(nullptr);
    editReg->setCloseBtn(true);
    editReg->show();

}

void MainWindow::modifyDownloadLinks()
{
    editLink->setParent(nullptr);
    editLink->setCloseBtn(true);
    editLink->show();
}

void MainWindow::appOptions(){
    //options->addTab(nullptr, "Settings");
    addFilesMenu->setCloseBtn(false);
    editLink->setCloseBtn(false);
    editReg->setCloseBtn(false);
    options->addTab(addFilesMenu, "Add Files");
    options->addTab(editLink, "Edit Links");
    options->addTab(editReg, "Edit Registry");


    options->show();
}

void MainWindow::reportBugsMenu()
{
    reportBugs->show();

}

void MainWindow::aboutMenu()
{
    QString detailedDesc = "This application was custumized to fit the need for SkyTouch, LLC to help inprove their work productivity\nPlease email any questions or concers to elwincab0@gmail.com\n\nVersion 0.0.1";
    messageBox("Created by Elwin Cabrera",detailedDesc, "About");
}

void MainWindow::aboutSkyTouchMenu()
{
    QString detailedDesc = "SkyTouch is an independent company servicing and installing Point of Sale (POS) systems in various small buisnesses around the east coast.";
    messageBox("SkyTouch, LLC",detailedDesc, "About SkyTouch");

}


