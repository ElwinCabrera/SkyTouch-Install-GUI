#include "global.h"

int messageBox(QString text, QString moreDetails, QString windowTitle ){
    QMessageBox msgBox;
    msgBox.setWindowTitle(windowTitle);
    msgBox.setText(text);
    msgBox.setInformativeText(moreDetails);
    msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.setModal(true);
    return msgBox.exec();
}

void clearLayotAndWidgets(QLayout * layout) {
   if (! layout) return;

    while (auto item = layout->takeAt(0)) {
        delete item->widget();
        clearLayotAndWidgets(item->layout());
   }
   delete layout;
}

void startProcess(QObject *parent, QString programPath, QString fileName ) {

    QProcess *process = new QProcess(parent);
    process->start(programPath);

    if(!process->waitForStarted()) messageBox("Could not start " + fileName, "");

}
