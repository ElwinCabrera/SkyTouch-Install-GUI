#ifndef REGISTRYHANDLER_H
#define REGISTRYHANDLER_H

#include "global.h"



class RegistryHandler
{
public:
    RegistryHandler();
    QString getCurrRegDataVal(QString val);
    void setDefaultValues();

private:

    QMap<QString, QString> policyNameToKey;

    QString HKCU = "HKEY_CURRENT_USER";
    QString HKLM = "HKEY_LOCAL_MACHINE";


    QString hkcuPolicyWinKey = HKCU+"\\Software\\Policies\\Microsoft\\Windows";
    QString hkcuPolicyKey = HKCU+"\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies";
    QString hkcuRunKey = HKCU+"\\Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    QString hkcuPolicyPushNotiKey = HKCU+"\\SOFTWARE\\Policies\\Microsoft\\Windows\\CurrentVersion\\PushNotifications";

    QString hklmPolicyPersonalKey = HKLM+"\\Software\\Policies\\Microsoft\\Windows\\Personalization";
    QString hklmPolicyKey = HKLM+"\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer";

};

#endif // REGISTRY_H
