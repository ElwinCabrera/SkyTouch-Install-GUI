#ifndef USEREDITLINKS_H
#define USEREDITLINKS_H

#include "global.h"
#include "pages.h"


class InputLinkDialog: public QDialog{
    Q_OBJECT
public:
    InputLinkDialog(QWidget *parent = nullptr);
    ~InputLinkDialog();

    SoftwareInfo *getNewLink() {return softwareLink;}
    bool getSaved(){return saved;}


private slots:
    void saveLinkEntry();
    void closeWin();
    void onVersionSelect();

private:
    void init();
    QVBoxLayout* addNewLink();
    bool isValidInput();

    bool firstCall = true;
    bool saved = false;



    QVBoxLayout *mainLayout = nullptr;


    SoftwareInfo *softwareLink = nullptr;

    QLineEdit *nameInput = nullptr;
    QLineEdit *bit32Input = nullptr;
    QLineEdit *bit64Input = nullptr;

    QRadioButton *bit32Btn = nullptr;
    QRadioButton *bit64Btn = nullptr;
    QRadioButton *bothBtn = nullptr;
    QRadioButton *dontKnowBtn = nullptr;

    bool bit32BtnChecked = false;
    bool bit64BtnChecked = false;
    bool bothBtnChecked = false;
    bool dontKnowBtnChecked = false;

    QString nameInputText = "";

};

class UserEditLinks : public QWidget
{
    Q_OBJECT
public:
    explicit UserEditLinks(SoftwareDownloadPage *sPage = nullptr, QWidget *parent = nullptr);
    ~UserEditLinks();
    void setCloseBtn(bool set) {closeBtnEnable = set; init();}

signals:

private slots:
    void addLink();
    void deleteLinkInput();


private:
    bool closeBtnEnable = true;
    void init();
    QVBoxLayout* getLinkInfoLayoutAndWidgets(SoftwareInfo *si);


    SoftwareDownloadPage *sPage = nullptr;  //do not delete

    QVBoxLayout *mainLayout = nullptr;     // delete on exit
    QVBoxLayout *scrollAreaLayout = nullptr; // delete on exit
    QScrollArea *scrollArea = nullptr; // delete on exit

    QSet<SoftwareInfo*> userSoftwreLinks; // delete on exit
    QMap<QPushButton*, SoftwareInfo*> btnToLink; // delete on exit
};

#endif // USEREDITLINKS_H
