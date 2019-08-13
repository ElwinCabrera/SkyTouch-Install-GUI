#ifndef WARNINGBOX_H
#define WARNINGBOX_H


#include "global.h"

class WarningBox : public QDialog
{
    Q_OBJECT
public:
    WarningBox(QString warningMessage);
    bool actionConfirmed() {return isConfirmed; }

public slots:
    void okButtonCliked();
    void cancelButtonClicked();

private:
    bool isConfirmed = false;
};

#endif // CANCELDOWNLOADSWARNING_H
