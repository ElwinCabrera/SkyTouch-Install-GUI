#ifndef INSTALLCONFIRMATION_H
#define INSTALLCONFIRMATION_H

#include <QDialog>
#include <vector>
#include "network.h"
#include "global.h"

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
    InstallConfirmation(QWidget *parent , vector<SoftwareInfo*> softwareL);
    int totalFileSize(vector<SoftwareInfo*> softwareL);
    bool getConfirmation() {return confirm; }


private:
     QListWidget *softwareListWidget;
     bool confirm ;
     Network network;

     void okButtonCliked();
     void cancelButtonClicked();
};

#endif // INSTALLCONFIRMATION_H
