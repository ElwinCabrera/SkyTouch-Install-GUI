#include "global.h"

int messageBox(QString text, QString moreDetails){
    QMessageBox msgBox;
    msgBox.setText(text);
    msgBox.setInformativeText(moreDetails);
    msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.setModal(true);
    return msgBox.exec();
}
