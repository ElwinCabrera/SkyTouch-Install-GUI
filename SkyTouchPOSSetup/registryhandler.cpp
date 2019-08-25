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
    systemSettings.setValue("DisableCMD", 0); //Prevent access to the command prompt
    policyNameToType.insert("DisableCMD","SYSTEM");


    runSetting.setValue("CashRegisterExpressRun", "C:\\Program Files (x86)\\CRE.NET\\CRE2004"); //
    policyNameToType.insert("CashRegisterExpressRun", "RUN");

    policySettings.setValue("NoControlPanel", 0); //Prohibit access to Control Panel and PC Settings
    policySettings.setValue("HidePowerOptions", 0); // Remove and prevent access to the Shut Down, Restart, Sleep, and Hibernate commands
    policySettings.setValue("Nologoff", 0); // Remove logoff
    policySettings.setValue("DisabletaskMgr", 0); // Remove Task Manager
    policySettings.setValue("DisablelockWorkstation", 0); // Remove Lock Computer
    policySettings.setValue("Disablechangepassword", 0); // Remove Change Passoword
    policySettings.setValue("NoAutoUpdate", 0); // Windows automatic updates
    policySettings.setValue("TaskbarNoNotification", 0); // Turn off all balloon notifications
    policySettings.setValue("NoballoonFeatureAdvertisements", 0);


    policySettings.setValue("NoChangestartMenu", 0); // Prevent users from customizing their start screen
    policySettings.setValue("LockTaskbar", 0); // Lock the taskBar
    policySettings.setValue("TaskbarNoAddRemoveToolbar", 0); // Prevent users from adding or removing toolbars
    policySettings.setValue("NoSetTaskbar", 0); //Prevent changes to Taskbar and start menu Settings
    policySettings.setValue("taskbarLockAll", 0); // Lock all taskbar settings

    //policySettings.setValue("NoTileApplicationNotification", 0); // Turn off tile notifications -- NOT IN THIS SUBKEY CHANGE LATER
    //policySettings.setValue("NoCloudApplicationNotification", 0); // Turn off notifications network usage -- NOT IN THIS SUBKEY CHANGE LATER
    //policySettings.setValue("NoWindowMinimizingShortcuts", 0); // Turn off Aero Shake window minimizing mouse gesture -- NOT IN THIS SUBKEY CHANGE LATER
    //policySettings.setValue("NoChanginglockscreen", 0); //Prevent changing lock screen and logon image -- NOT IN THIS SUBKEY CHANGE LATER
    //policySettings.setValue("Nolockscreen", 0); // Do not display the lock screen -- NOT IN THIS SUBKEY CHANGE LATER
    //policySettings.setValue("NoChangingWallPaper", 0); // Prevent changing desktop background/wallpaper -- NOT IN THIS SUBKEY CHANGE LATER


    policySettings.setValue("NoMovingBands",0); // Prohibit adjusting desktop toolbars

    /*
     * Note: The default account picture is stored at %PROGRAMDATA%\Microsoft\User Account pictures\user.jpg. The default guest picture is stored at %PROGRAMDATA%\Microsoft\User Account pictures\guest.jpg. If the default pictures do not exist, an empty frame is displayed.
     */
    policySettings.setValue("UseDefaultTile", 0); // Apply the default account picture to all users
}
