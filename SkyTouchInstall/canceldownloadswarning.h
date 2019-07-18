#ifndef CANCELDOWNLOADSWARNING_H
#define CANCELDOWNLOADSWARNING_H

#include <QObject>
#include <QDialog>
#include <QtWidgets>
#include <QWidget>

class CancelDownloadsWarning : public QDialog
{
    Q_OBJECT
public:
    CancelDownloadsWarning();

    void okButtonCliked();
    void cancelButtonClicked();
    bool getOkButtonCliked() {return wasOkCliked; }

private:
    bool wasOkCliked ;
};

#endif // CANCELDOWNLOADSWARNING_H
