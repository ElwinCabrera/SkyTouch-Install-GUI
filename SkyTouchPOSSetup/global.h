#ifndef GLOBAL_H
#define GLOBAL_H

#include <QWidget>
#include <QtWidgets>
#include <QDebug>
#include <QDialog>
#include <QObject>
#include<QAction>


#include <QtConcurrent/QtConcurrentRun>
#include <QFuture>
#include <QFutureWatcher>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QAuthenticator>
#include <QtNetwork/QNetworkProxy>

#include <QSet>

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>




using std::vector;
using std::pair;
using std::unordered_set;
using std::set;
using std::unordered_map;




class LocalFile: public QObject{

public:
    LocalFile(QString fileName, QString filePath, bool readyForInstall){
        this->fileName = fileName;
        this->filePath = filePath;
        this->readyForInstall = readyForInstall;
    }

    QString getFileName() {return fileName;}
    QString getFilePath() {return filePath;}
    bool getInstallState() {return markedForInstall;}
    bool getReadyState() {return readyForInstall;}

    void setInstallState(bool install){this->markedForInstall = install;}
    void setReadyState(bool ready) {readyForInstall = ready;}

public slots:
    void changeReadyState(){ readyForInstall = !readyForInstall; markedForInstall = false;}
    void changeInstallState(){ markedForInstall = true; readyForInstall = false; }

private:
    QString fileName = "";
    QString filePath = "";
    bool markedForInstall = false;
    bool readyForInstall = false;


};

class ProgressListenner : public QObject
{
    //Q_OBJECT
public:
   ProgressListenner() : _lastKnownReceived(0), _lastKnownTotal(0){}
   ~ProgressListenner() {if(pBar) delete pBar;}

   qint64 _lastKnownReceived;
   qint64 _lastKnownTotal;
   QProgressBar *pBar= nullptr;

public slots:
     void onDownloadProgress( qint64 bytesReceived, qint64 bytesTotal )
      {
          _lastKnownReceived = bytesReceived;
          _lastKnownTotal = bytesTotal;

          pBar->setRange(0,bytesTotal);
          pBar->setValue(bytesReceived);
          if(bytesTotal < 0) pBar->setValue(0);
      }
};

int messageBox(QString text, QString moreDetails, QString windowTitle = "");

void clearLayotAndWidgets(QLayout * layout);
void startProcess(QObject *parent, QString programPath, QString fileName  );


#endif // GLOBAL_H
