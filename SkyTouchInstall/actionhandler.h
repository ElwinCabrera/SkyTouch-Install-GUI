#ifndef ACTIONHANDLER_H
#define ACTIONHANDLER_H

#include <QWidget>
#include <vector>
//#include<pair>

using std::vector;
using std::pair;

class ActionHandler{
public:
    ActionHandler();
    void installAll(vector<QString> getURLs);
    QString getDownloadUrl(QString softwareName, QString version, QString bitVersion);

};

#endif // ACTIONHANDLER_H
