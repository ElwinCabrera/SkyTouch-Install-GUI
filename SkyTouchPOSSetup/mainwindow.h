#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>



#include "pages.h"
#include "global.h"
#include "network.h"
#include "usereditregistry.h"
#include "registryhandler.h"
#include "usereditlinks.h"
#include "optionsmenu.h"
#include "addfilesmenu.h"
#include "reportbugsmenu.h"

QT_BEGIN_NAMESPACE
class QListWidget;
class QListWidgetItem;
class QStackedWidget;
QT_END_NAMESPACE

/*namespace Ui {
class MainWindow;
}*/



class MainWindow : public QWidget //public QMainWindow
{
    Q_OBJECT

public:
    explicit  MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int testgetInt() {return 5;}

private slots:
    void browseFilesMenu();
    void exitApp();
    void modifyWindowsReg();
    void modifyDownloadLinks();
    void appOptions();
    void reportBugsMenu();
    void aboutMenu();
    void aboutSkyTouchMenu();

private:
    void createMenuActions();
    void createMenu();

    QMenuBar *menuBar = nullptr;
    QStatusBar *statusBar = nullptr;

    SoftwareDownloadPage *softwareTab= nullptr;
    ConfigurationPage *configTab = nullptr;
    Network *network = nullptr;
    RegistryHandler *regHan = nullptr;

    QSet< SoftwareInfo*> softwareList;

    UserEditReg *editReg = nullptr;
    UserEditLinks *editLink = nullptr;
    OptionsMenu *options = nullptr;
    AddFilesMenu *addFilesMenu = nullptr;
    ReportBugsMenu *reportBugs = nullptr;


    /**********Menus and actions for menu**********/


    //In File menu
    QMenu *fileMenu = nullptr;
    QAction *browseFilesAct = nullptr;
    QAction *exitAct = nullptr;
    //QActionGroup *fileMenuActions = nullptr;

    // In edit menu
    QMenu *editMenu = nullptr;
    QAction *linksAct = nullptr;
    QAction *addToWinRegistryAct = nullptr;
    QAction *optionsAct = nullptr;
    //QActionGroup *editMenuActions = nullptr;

    //In help menu
    QMenu *helpMenu = nullptr;
    QAction *reportBugAct = nullptr;
    QAction *aboutAct = nullptr;
    QAction *aboutSkyTouchAct = nullptr;
    //QActionGroup *helpMenuActions = nullptr;



/*private:
    Ui::MainWindow *ui;*/
};

#endif // MAINWINDOW_H
