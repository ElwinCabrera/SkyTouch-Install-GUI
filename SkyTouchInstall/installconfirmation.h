#ifndef INSTALLCONFIRMATION_H
#define INSTALLCONFIRMATION_H

#include <QDialog>
#include <vector>
#include "network.h"

using std::pair;
using std::vector;

QT_BEGIN_NAMESPACE
class QListWidget;
class QListWidgetItem;
class QStackedWidget;
class QGroupBox;
QT_END_NAMESPACE

class InstallConfirmation : public QDialog
{
    Q_OBJECT

public:
    InstallConfirmation(vector<pair<QGroupBox *,QString>> installGroups,  vector<QString> getURLs);
    int totalFileSize();
    bool getConfirmation() {return confirm; }


private:
     QListWidget *softwareListWidget;
     vector<QString> URLs;
     bool confirm ;
     Network network;

     void okButtonCliked();
     void cancelButtonClicked();
};

#endif // INSTALLCONFIRMATION_H
