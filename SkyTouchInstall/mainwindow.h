#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDialog>
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



class MainWindow : public QDialog
{
    Q_OBJECT

public:
    /*explicit */ MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);

private:
    void createIcons();

    QListWidget *contentsWidget;
    QStackedWidget *pagesWidget;
    SoftwareDownloadPage *softwareDownloadPage;

    Network *network;
    vector< SoftwareInfo*> softwareList;


/*private:
    Ui::MainWindow *ui;*/
};

#endif // MAINWINDOW_H
