#ifndef REGISTRYHANDLER_H
#define REGISTRYHANDLER_H

#include "global.h"

#define HKCU_POLICY_KEY "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies"
#define HKCU_RUN_KEY "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run"
#define HKCU_SYSTEM_KEY "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\System"

class RegistryHandler
{
public:
    RegistryHandler();
    QString getCurrRegDataVal(QString val);
    void setDefaultValues();

private:
    QSettings policySettings;
    QSettings runSetting; // for auto start
    QSettings systemSettings;

    QMap<QString, QString> policyNameToType;

};

#endif // REGISTRY_H
