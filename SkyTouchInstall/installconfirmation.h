#ifndef INSTALLCONFIRMATION_H
#define INSTALLCONFIRMATION_H

#include <QDialog>
#include <vector>

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

private:
     QListWidget *softwareListWidget;
};

#endif // INSTALLCONFIRMATION_H
