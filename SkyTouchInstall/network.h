#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QtWidgets>
#include <vector>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QAuthenticator>
#include <QtNetwork/QNetworkProxy>

using std::vector;

class Network : public QObject
{
    Q_OBJECT
public:
    Network(QWidget *parent = nullptr);


    int getFileLength();
    // void setPBars(vector<QProgressBar*> bars);

public slots:
    void get(QString url);
    void post(QString url, QByteArray data);
    void head(QString url);



public slots:
    void readyRead();
    void authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);
    void encrypted(QNetworkReply *reply);
    void finished();
    void networkAccessChanged(QNetworkAccessManager::NetworkAccessibility accessable);
    void preSharedKeyAuthenticationRequired(QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator);
    void proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator);
    void sslErrors(QNetworkReply *reply, const QList<QSslError> &errors);
    void error();



    QNetworkAccessManager* getAccessManager();
    QNetworkReply *getLastReply();
    vector<QNetworkReply*> getReplys();
    void closeAllConnections();



private:
    QNetworkAccessManager *manager;
    int lastFileLength;
    QNetworkReply *lastReply;
    QFile *mFile;

    //vector<QProgressBar*> pBars;
    vector<QNetworkReply*> replys;



};



#endif // NETWORK_H
