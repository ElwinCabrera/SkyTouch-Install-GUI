#include "windowsregistry.h"
#define BUFFERSIZE 255
WindowsRegistry::WindowsRegistry()
{

}

WindowsRegistry::~WindowsRegistry()
{

}

QString WindowsRegistry::getKeyValue(QString keyName){
    QString result = "";
    HKEY hKey;
    LONG openStatus = RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",0, KEY_QUERY_VALUE, &hKey);


    if(openStatus != ERROR_SUCCESS) return result;
    char data[255];
    DWORD bufferSize = BUFFERSIZE;

   // RegGetValueA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorere", RRF_RT_ANY, NULL, (PVOID) &data,&bufferSize);


}
