#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QAuthenticator>
#include <QtNetwork/QNetworkProxy>

class Network : public QObject
{
    Q_OBJECT
public:
    Network(QWidget *parent = nullptr);

public slots:
    void get(QString url);
    void post(QString url, QByteArray data);
    void head(QString url);

public slots:
    void readyRead();
    void authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);
    void encrypted(QNetworkReply *reply);
    void finished(QNetworkReply *reply);
    void networkAccessChanged(QNetworkAccessManager::NetworkAccessibility accessable);
    void preSharedKeyAuthenticationRequired(QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator);
    void proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator);
    void sslErrors(QNetworkReply *reply, const QList<QSslError> &errors);
    void error();

    int getFileLength();

private:
    QNetworkAccessManager *manager;
    int lastFileLength;



};

#endif // NETWORK_H
