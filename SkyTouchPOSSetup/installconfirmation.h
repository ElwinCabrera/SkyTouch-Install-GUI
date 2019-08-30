#ifndef INSTALLCONFIRMATION_H
#define INSTALLCONFIRMATION_H


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
    InstallConfirmation(QSet<SoftwareInfo*> &softwareList, Network *network= nullptr, QWidget *parent = nullptr );
    uint64_t totalFileSize();
    bool getConfirmation() {return confirm; }


private:
    bool confirm = false;
    void okButtonCliked();
    void cancelButtonClicked();

    QSet<SoftwareInfo*> softwareList;
    QListWidget *softwareListWidget;
    Network *network;


};

#endif // INSTALLCONFIRMATION_H
