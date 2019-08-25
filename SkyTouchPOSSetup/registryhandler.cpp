#include "registryhandler.h"

RegistryHandler::RegistryHandler(){

    //QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies", QSettings::NativeFormat);
    //policySettings.setValue("");

    policySettings.setPath(QSettings::NativeFormat, QSettings::UserScope ,HKCU_POLICY_KEY);
    runSetting.setPath(QSettings::NativeFormat, QSettings::UserScope, HKCU_RUN_KEY);
    systemSettings.setPath(QSettings::NativeFormat, QSettings::UserScope, HKCU_SYSTEM_KEY);


}

QString RegistryHandler::getCurrRegDataVal(QString policyName){

}

void RegistryHandler::setDefaultValues(){



    /************  HKCU\Software\Microsoft\Windows\CurrentVersion\Policies\... ***********/
    // Explorer
    policySettings.setValue("NoControlPanel", 1); //Prohibit access to Control Panel and PC Settings
    policySettings.setValue("HidePowerOptions", 1); // Remove and prevent access to the Shut Down, Restart, Sleep, and Hibernate commands
    policySettings.setValue("Nologoff", 1); // Remove logoff
    policySettings.setValue("NoAutoUpdate", 1); // Windows automatic updates
    policySettings.setValue("TaskbarNoNotification", 1); // Turn off all balloon notifications
    policySettings.setValue("NoChangestartMenu", 0); // Prevent users from customizing their start screen
    policySettings.setValue("LockTaskbar", 1); // Lock the taskBar
    policySettings.setValue("TaskbarNoAddRemoveToolbar", 0); // Prevent users from adding or removing toolbars
    policySettings.setValue("NoSetTaskbar", 0); //Prevent changes to Taskbar and start menu Settings
    policySettings.setValue("taskbarLockAll", 0); // Lock all taskbar settings
    policySettings.setValue("NoMovingBands",0); // Prohibit adjusting desktop toolbars

    // System
    policySettings.setValue("DisabletaskMgr", 1); // Remove Task Manager
    policySettings.setValue("DisablelockWorkstation", 1); // Remove Lock Computer
    policySettings.setValue("Disablechangepassword", 1); // Remove Change Passoword

    /**************** HKCU\Software\Policies\Microsoft\Windows\...  ********/
    // Explorer
    policySettings.setValue("NoballoonFeatureAdvertisements", 1);

    // System
    systemSettings.setValue("DisableCMD", 1); //Prevent access to the command prompt
    policyNameToType.insert("DisableCMD","SYSTEM");

    //ActiveDesktop
    policySettings.setValue("NoChangingWallPaper", 1); // Prevent changing desktop background/wallpaper



    /********************** HKCU\SOFTWARE\Policies\Microsoft\Windows\CurrentVersion\PushNotifications\... *******/
    policySettings.setValue("NoTileApplicationNotification", 1); // Turn off tile notifications
    policySettings.setValue("NoCloudApplicationNotification", 1); // Turn off notifications network usage

    /***************************** HKCU\Software\Policies\Microsoft\Windows\Explorer\ ... **********************/
    policySettings.setValue("NoWindowMinimizingShortcuts", 1); // Turn off Aero Shake window minimizing mouse gesture



    /********************* HKLM\Software\Policies\Microsoft\Windows\Personalization\ ... ************************/
    policySettings.setValue("NoChanginglockscreen", 0); //Prevent changing lock screen and logon image

    /********************* HKLM\Software\Policies\Microsoft\Windows\Personalization ****************************/
    policySettings.setValue("Nolockscreen", 1); // Do not display the lock screen



    /************************ HKLM\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer ******************/
    /*
     * Note: The default account picture is stored at %PROGRAMDATA%\Microsoft\User Account pictures\user.jpg.
     * The default guest picture is stored at %PROGRAMDATA%\Microsoft\User Account pictures\guest.jpg.
     * If the default pictures do not exist, an empty frame is displayed.
     */
    policySettings.setValue("UseDefaultTile", 0); // Apply the default account picture to all users
}
