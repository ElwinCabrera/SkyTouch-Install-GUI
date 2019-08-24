#ifndef WINDOWSREGISTRY_H
#define WINDOWSREGISTRY_H

#include "global.h"
#include <windows.h>
#include<wchar.h>

using std::wstring;

class WindowsRegistry
{
public:
    WindowsRegistry();
    ~WindowsRegistry();

    QString getKeyValue(QString keyName);
    void addKeyIfNotExist();


    INT8 runOnBoot(QString progPath);
    INT8 disableRunOnBoot(QString value);

private:
    INT8 testCreationStatus(LONG create_status ,LONG value_status, LONG close_status);
    INT8 testDeletionStatus(LONG open_status ,LONG delete_status, LONG close_status);

};

#endif // WINDOWSREGISTRY_H
