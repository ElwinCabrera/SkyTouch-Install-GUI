#ifndef WARNINGBOX_H
#define WARNINGBOX_H


#include "global.h"

class WarningBox : public QDialog
{
    Q_OBJECT
public:
    WarningBox(QString warningMessage);
    bool actionConfirmed() {return isConfirmed; }
    bool setWarningType(bool generic, bool stopDownloads){genericWarning = generic; stopDownloadWarning = stopDownloads;}

    void setDownloadList(vector<SoftwareInfo*> list) {downloadList = list;}
public slots:
    void okButtonCliked();
    void cancelButtonClicked();

private:
    bool isConfirmed = false;
    bool stopDownloadWarning = false;
    bool genericWarning = true;
    vector<SoftwareInfo*> downloadList;
};

#endif // CANCELDOWNLOADSWARNING_H
