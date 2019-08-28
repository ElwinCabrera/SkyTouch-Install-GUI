#ifndef EDITREGISTRY_H
#define EDITREGISTRY_H

#include "global.h"
#include "registryhandler.h"


class InputRegDialog : public QDialog{
  Q_OBJECT
public:
    InputRegDialog(QWidget *parent = nullptr);
    ~InputRegDialog();

    UserRegistryItem *getRegItem() {return regItem;}
    bool getSaved(){return saved;}


private slots:
    void saveRegEntry();
    void closeWin();

private:

    QVBoxLayout* addNewRegItem();
    bool saved = false;
    UserRegistryItem *regItem = nullptr;

    QLineEdit *keyTextInput = nullptr;
    QLineEdit *valueNameInput = nullptr;
    QLineEdit *valueInput = nullptr;
    QRadioButton *stringBtn = nullptr;
    QRadioButton *numberBtn = nullptr;
    QRadioButton *binaryBtn = nullptr;


};

class UserEditReg : public QWidget
{
    Q_OBJECT
public:
    explicit UserEditReg(QWidget *parent = nullptr);
    ~UserEditReg();
    void init();


signals:

private slots:
    void addRegItem();
    void deleteRegInput();

private:
    QVBoxLayout* getRegInfoLayoutAndWidgets(QString key, QString valueName, QVariant data);

    QVBoxLayout *mainLayout = nullptr;
    QVBoxLayout *scrollAreaLayout = nullptr;
    QScrollArea *scrollArea = nullptr;
    RegistryHandler regHan;

    QList<UserRegistryItem*> userRegList;
    QMap<QString, UserRegistryItem> m;

};



#endif // INPUTDIALOG_H
