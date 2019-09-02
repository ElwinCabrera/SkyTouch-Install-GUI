#ifndef EDITREGISTRY_H
#define EDITREGISTRY_H

#include "global.h"
#include "registryhandler.h"
#include "softwareinfo.h"
class UserRegistryItem;
class InputRegDialog;

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


class UserRegistryItem{
public:
    UserRegistryItem(QString key, QString valueName, QVariant data, QString dataType = "DWORD", QString description = ""){
        this->key = key;
        this->valueName = valueName;

        this->data = data;
        this->dataType = dataType;
        this->descrption = description;
    }
    UserRegistryItem(){}


    void setKey(QString newKey) {key = newKey;}
    void setValueName(QString newValueName) {valueName = newValueName;}
    void setData(QVariant newData) { data = newData;}
    void setDataType(QString type) {dataType = type;}
    void setDesc(QString desc) {descrption = desc;}



    QString getKey() {return key;}
    QString getValueName() {return valueName;}
    QVariant getData() {return data;}
    QString getDataType() {return dataType;}
    QString getDescription(){return descrption;}


private:

    QString key = "";
    QString valueName = "";
    QVariant data;
    QString dataType = "";
    QString descrption = "";
};

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

    QVBoxLayout *mainLayout = nullptr;
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

#endif // INPUTDIALOG_H
