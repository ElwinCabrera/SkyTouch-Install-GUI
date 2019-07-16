#ifndef PAGES_H
#define PAGES_H

#include <QWidget>
#include <QtWidgets>
#include <QDebug>
#include <vector>
//#include<pair>

using std::vector;
using std::pair;


class SoftwareInstallationPage : public QWidget {
public:
    SoftwareInstallationPage(QWidget *parent = 0);
   // ~SoftwareInstallationPage();


public slots:
    void onStartInstallationButtonCliked();

private:
    QRadioButton *installCRERadioBtn;
    QRadioButton *installCRE64RadioBtn;
    QPushButton *startInstallationButton;

    vector<pair<QGroupBox *,QString>> installGroups;
    vector<QString> getURLs;
};



class ConfigurationPage : public QWidget{
public:
    ConfigurationPage(QWidget *parent = 0);
    //~ConfigurationPage();
};



#endif // PAGES_H
