#include "actionhandler.h"
#include "network.h"

ActionHandler::ActionHandler(){

}

void ActionHandler::installAll(vector<QString> getURLs)
{
    Q_UNUSED(getURLs);

}

QString ActionHandler::getDownloadUrl(QString softwareName, QString version, QString bitVersion)
{
    QString url = "";

    if(softwareName == "CRE" && bitVersion == "32") url = "http://download2.pcamerica.com/"+version+"/CRE_Setup.exe";
    if(softwareName == "CRE" && bitVersion == "64") url = "http://download2.pcamerica.com/"+version+"/CRE_Setup_x64.exe";

    return url;

}


