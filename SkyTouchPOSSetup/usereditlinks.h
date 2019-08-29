#ifndef USEREDITLINKS_H
#define USEREDITLINKS_H

#include "global.h"


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
    explicit UserEditLinks(QWidget *parent = nullptr);
    ~UserEditLinks();

signals:

private slots:
    void addLink();
    void deleteLinkInput();


private:
    void init();
    QVBoxLayout* getLinkInfoLayoutAndWidgets(SoftwareInfo *si);


    QVBoxLayout *mainLayout = nullptr;
    QVBoxLayout *scrollAreaLayout = nullptr;
    QScrollArea *scrollArea = nullptr;

    QSet<SoftwareInfo*> userSoftwreLinks;
    QMap<QPushButton*, SoftwareInfo*> btnToLink;
};

#endif // USEREDITLINKS_H
