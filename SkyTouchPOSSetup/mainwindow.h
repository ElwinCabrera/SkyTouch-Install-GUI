#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>



#include "pages.h"
#include "global.h"
#include "network.h"

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

public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);

private slots:
    void exitApp();

private:
    void createIcons();

    void createMenuActions();
    void createMenu();

    QListWidget *contentsWidget = nullptr;
    QStackedWidget *pagesWidget = nullptr;
    QMenuBar *menuBar = nullptr;
    QStatusBar *statusBar = nullptr;

    SoftwareDownloadPage *softwareDownloadPage = nullptr;
    Network *network = nullptr;

    vector< SoftwareInfo*> softwareList;

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
