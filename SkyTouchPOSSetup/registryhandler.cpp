#include "registryhandler.h"

RegistryHandler::RegistryHandler(){

    policyNameToKey.insert("CashRegisterExpressRun", hkcuRunKey);

    policyNameToKey.insert("NoControlPanel",hkcuPolicyKey+"\\Explorer");
    policyNameToKey.insert("HidePowerOptions",hkcuPolicyKey+"\\Explorer");
    policyNameToKey.insert("Nologoff",hkcuPolicyKey+"\\Explorer");
    policyNameToKey.insert("NoAutoUpdate",hkcuPolicyKey+"\\Explorer");
    policyNameToKey.insert("TaskbarNoNotification",hkcuPolicyKey+"\\Explorer");
    policyNameToKey.insert("NoChangestartMenu",hkcuPolicyKey+"\\Explorer");
    policyNameToKey.insert("LockTaskbar",hkcuPolicyKey+"\\Explorer");
    policyNameToKey.insert("TaskbarNoAddRemoveToolbar",hkcuPolicyKey+"\\Explorer");
    policyNameToKey.insert("NoSetTaskbar",hkcuPolicyKey+"\\Explorer");
    policyNameToKey.insert("taskbarLockAll",hkcuPolicyKey+"\\Explorer");
    policyNameToKey.insert("NoMovingBands",hkcuPolicyKey+"\\Explorer");
    policyNameToKey.insert("DisabletaskMgr",hkcuPolicyKey+"\\System");
    policyNameToKey.insert("DisablelockWorkstation",hkcuPolicyKey+"\\System");
    policyNameToKey.insert("Disablechangepassword",hkcuPolicyKey+"\\System");



    policyNameToKey.insert("NoballoonFeatureAdvertisements",hkcuPolicyWinKey+"\\Explorer");
    policyNameToKey.insert("NoWindowMinimizingShortcuts",hkcuPolicyWinKey+"\\Explorer");
    policyNameToKey.insert("DisableCMD",hkcuPolicyWinKey+"\\System");
    policyNameToKey.insert("NoChangingWallPaper",hkcuPolicyWinKey+"\\ActiveDesktop");


    policyNameToKey.insert("NoTileApplicationNotification",hkcuPolicyPushNotiKey);
    policyNameToKey.insert("NoCloudApplicationNotification",hkcuPolicyPushNotiKey);


    policyNameToKey.insert("NoChanginglockscreen",hklmPolicyPersonalKey);
    policyNameToKey.insert("Nolockscreen",hklmPolicyPersonalKey);

    policyNameToKey.insert("UseDefaultTile",hklmPolicyKey);

}

QString RegistryHandler::getCurrRegDataVal(QString policyName){

    auto it = policyNameToKey.find(policyName);
    if(it != policyNameToKey.end()){
        QString key = it.value();
        QSettings settings(key, QSettings::NativeFormat);
        return settings.value(policyName).toString();
    }

    return "";
}

void RegistryHandler::setDefaultValues(){

    /************  HKCU\Software\Microsoft\Windows\CurrentVersion\Run ***********/
    QSettings policyRunSettings(hkcuRunKey, QSettings::NativeFormat);
    policyRunSettings.setValue("CashRegisterExpressRun", "C:\\Program Files (x86)\\CRE.NET\\CRE2004.exe");


    /************  HKCU\Software\Microsoft\Windows\CurrentVersion\Policies\... ***********/
    // Explorer
    QSettings policyExplorerSettings(hkcuPolicyKey+"\\Explorer", QSettings::NativeFormat);
    policyExplorerSettings.setValue("NoControlPanel", 1); //Prohibit access to Control Panel and PC Settings
    policyExplorerSettings.setValue("HidePowerOptions", 1); // Remove and prevent access to the Shut Down, Restart, Sleep, and Hibernate commands
    policyExplorerSettings.setValue("Nologoff", 1); // Remove logoff
    policyExplorerSettings.setValue("NoAutoUpdate", 1); // Windows automatic updates
    policyExplorerSettings.setValue("TaskbarNoNotification", 1); // Turn off all balloon notifications
    policyExplorerSettings.setValue("NoChangestartMenu", 0); // Prevent users from customizing their start screen
    policyExplorerSettings.setValue("LockTaskbar", 1); // Lock the taskBar
    policyExplorerSettings.setValue("TaskbarNoAddRemoveToolbar", 0); // Prevent users from adding or removing toolbars
    policyExplorerSettings.setValue("NoSetTaskbar", 0); //Prevent changes to Taskbar and start menu Settings
    policyExplorerSettings.setValue("taskbarLockAll", 0); // Lock all taskbar settings
    policyExplorerSettings.setValue("NoMovingBands",0); // Prohibit adjusting desktop toolbars


    // System
    QSettings policySystemSettings(hkcuPolicyKey+"\\System", QSettings::NativeFormat);
    policySystemSettings.setValue("DisabletaskMgr", 1); // Remove Task Manager
    policySystemSettings.setValue("DisablelockWorkstation", 1); // Remove Lock Computer
    policySystemSettings.setValue("Disablechangepassword", 1); // Remove Change Passoword


    /**************** HKCU\Software\Policies\Microsoft\Windows\...  ********/
    // Explorer
    QSettings policyWinExplorerSettings(hkcuPolicyWinKey+"\\Explorer", QSettings::NativeFormat);
    policyWinExplorerSettings.setValue("NoballoonFeatureAdvertisements", 1);
    policyWinExplorerSettings.setValue("NoWindowMinimizingShortcuts", 1); // Turn off Aero Shake window minimizing mouse gesture


    // System
    QSettings policyWinSystemSettings(hkcuPolicyWinKey+"\\System", QSettings::NativeFormat);
    policyWinSystemSettings.setValue("DisableCMD", 1); //Prevent access to the command prompt


    //ActiveDesktop
    QSettings policyWinActiveDesktopSettings(hkcuPolicyWinKey+"\\ActiveDesktop", QSettings::NativeFormat);
    policyWinActiveDesktopSettings.setValue("NoChangingWallPaper", 1); // Prevent changing desktop background/wallpaper



    /********************** HKCU\SOFTWARE\Policies\Microsoft\Windows\CurrentVersion\PushNotifications\... *******/
    QSettings policyPushNotiSettings(hkcuPolicyPushNotiKey, QSettings::NativeFormat);
    policyPushNotiSettings.setValue("NoTileApplicationNotification", 1); // Turn off tile notifications
    policyPushNotiSettings.setValue("NoCloudApplicationNotification", 1); // Turn off notifications network usage



    /********************* HKLM\Software\Policies\Microsoft\Windows\Personalization\ ... ************************/
    QSettings policyPersonalSettings(hklmPolicyPersonalKey, QSettings::NativeFormat);
    policyPersonalSettings.setValue("NoChanginglockscreen", 0); //Prevent changing lock screen and logon image
    policyPersonalSettings.setValue("Nolockscreen", 1); // Do not display the lock screen


    /************************ HKLM\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer ******************/
    QSettings policyExplorerSettingsHKLM(hklmPolicyKey, QSettings::NativeFormat);

    /*
     * Note: The default account picture is stored at %PROGRAMDATA%\Microsoft\User Account pictures\user.jpg.
     * The default guest picture is stored at %PROGRAMDATA%\Microsoft\User Account pictures\guest.jpg.
     * If the default pictures do not exist, an empty frame is displayed.
     */
    policyExplorerSettingsHKLM.setValue("UseDefaultTile", 0); // Apply the default account picture to all users
}
