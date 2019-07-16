#ifndef PAGES_H
#define PAGES_H

#include <QWidget>
#include <QtWidgets>
#include <vector>

using std::vector;


class SoftwareInstallationPage : public QWidget {
public:
    SoftwareInstallationPage(QWidget *parent = 0);

    QRadioButton* getInstallCRECheckBox() { return installCRERadioBtn; }
    QRadioButton* getInstallCRE64CheckBox() { return installCRE64RadioBtn; }
    QPushButton* getStartInstallationButton() { return startInstallationButton; }

   // ~SoftwareInstallationPage();
public slots:
    void onStartInstallationButtonCliked();

private:
    QRadioButton *installCRERadioBtn;
    QRadioButton *installCRE64RadioBtn;
    QPushButton *startInstallationButton;

    vector<QGroupBox *> markedForInstall;
};

class ConfigurationPage : public QWidget
{
public:
    ConfigurationPage(QWidget *parent = 0);
    //~ConfigurationPage();
};

#endif // PAGES_H
