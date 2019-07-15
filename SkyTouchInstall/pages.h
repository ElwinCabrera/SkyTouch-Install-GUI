#ifndef PAGES_H
#define PAGES_H

#include <QWidget>




class SoftwareInstallationPage : public QWidget {
public:
    SoftwareInstallationPage(QWidget *parent = 0);
   // ~SoftwareInstallationPage();
};

class ConfigurationPage : public QWidget
{
public:
    ConfigurationPage(QWidget *parent = 0);
    //~ConfigurationPage();
};

#endif // PAGES_H
