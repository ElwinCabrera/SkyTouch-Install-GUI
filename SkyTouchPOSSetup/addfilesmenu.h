#ifndef ADDFILESMENU_H
#define ADDFILESMENU_H

#include "global.h"
#include "pages.h"
#include "softwareinfo.h"

class AddFilesMenu : public QWidget
{
    Q_OBJECT
public:
    explicit AddFilesMenu(SoftwareDownloadPage *sPage = nullptr , QWidget *parent = nullptr);
    ~AddFilesMenu();
    void setCloseBtn(bool set) {closeBtnEnable = set; init();}

signals:

public slots:
    void addFile();
    void deleteFileInput();

private:
    bool closeBtnEnable = true;
    void init();
    QVBoxLayout* getLinkInfoLayoutAndWidgets(LocalFile *lf);

    SoftwareDownloadPage *sPage= nullptr;

    QSet<LocalFile*> localFilesSet;
    QMap<QPushButton*, LocalFile*> btnToFile;

    QVBoxLayout *mainLayout= nullptr;
    QVBoxLayout *scrollAreaLayout = nullptr;
    QScrollArea *scrollArea = nullptr;
};

#endif // ADDFILESMENU_H
