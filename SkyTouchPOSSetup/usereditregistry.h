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

    QLineEdit *descInput = nullptr;
    QLineEdit *keyTextInput = nullptr;
    QLineEdit *valueNameInput = nullptr;
    QLineEdit *valueInput = nullptr;

    QRadioButton *pathBtn = nullptr;
    QRadioButton *stringBtn = nullptr;
    QRadioButton *numberBtn = nullptr;
    QRadioButton *binaryBtn = nullptr;


};

class UserEditReg : public QWidget
{
    Q_OBJECT
public:
    explicit UserEditReg(QStandardItem *customPolicies, RegistryHandler *regHan = nullptr, QWidget *parent = nullptr);
    ~UserEditReg();
    void setCloseBtn(bool set) {closeBtnEnable = set; init();}

signals:

private slots:
    void addRegItem();
    void deleteRegInput();


private:
    bool closeBtnEnable = true;
    void init();
    void populateUserPolicyEntries(UserRegistryItem *regItem);
    QVBoxLayout* getRegInfoLayoutAndWidgets(QString key, QString valueName, QVariant data, QString desc);
    void removeFromTree(QString policyName);

    QStandardItem *customPolicies = nullptr;

    QVBoxLayout *mainLayout = nullptr;
    QVBoxLayout *scrollAreaLayout = nullptr;
    QScrollArea *scrollArea = nullptr;

    RegistryHandler *regHan = nullptr;

    QSet<UserRegistryItem*> userRegSet;
    QMap<QPushButton*, UserRegistryItem*> btnToItem;

};



#endif // INPUTDIALOG_H
