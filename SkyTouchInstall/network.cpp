#include "network.h"
#include <QtWidgets>

Network::Network(QWidget *parent):  QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::authenticationRequired, this, &Network::authenticationRequired);
    connect(manager, &QNetworkAccessManager::encrypted, this, &Network::encrypted);
    connect(manager, &QNetworkAccessManager::networkAccessibleChanged, this, &Network::networkAccessChanged);
    connect(manager, &QNetworkAccessManager::preSharedKeyAuthenticationRequired, this, &Network::preSharedKeyAuthenticationRequired);
    connect(manager, &QNetworkAccessManager::authenticationRequired, this, &Network::authenticationRequired);
    connect(manager, &QNetworkAccessManager::sslErrors, this, &Network::sslErrors);
    connect(manager, &QNetworkAccessManager::proxyAuthenticationRequired, this, &Network::proxyAuthenticationRequired);


}

void Network::get(QString url)
{
    qDebug() << "getting form server";
    //QNetworkRequest *request(QUrl(url));
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(url)));
    connect(reply, &QNetworkReply::readyRead, this, &Network::readyRead);


}

void Network::post(QString url, QByteArray data)
{
    qDebug() << "Posting to server...";
    QNetworkRequest request = QNetworkRequest(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "text/html");

    QNetworkReply *reply = manager->post(request, data);
    connect(reply, &QNetworkReply::readyRead, this, &Network::readyRead);

}

void Network::head(QString url)
{
    qDebug() << "getting head form server";
    QNetworkReply *reply = manager->head(QNetworkRequest(QUrl(url)));
    connect(reply, &QNetworkReply::readyRead, this, &Network::readyRead);
}

void Network::readyRead()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender()); // alternative way to get reply without a paremeter
    if(reply){
        //we have a reply
        qDebug() << reply->readAll();
    }
    if(reply->operation() == QNetworkAccessManager::HeadOperation){
        int fileLength = reply->header(QNetworkRequest::ContentLengthHeader).toInt();
        qDebug() << fileLength;
    }


    reply->deleteLater();
}

void Network::authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator)
{

}

void Network::encrypted(QNetworkReply *reply)
{

}

void Network::finished(QNetworkReply *reply)
{

}

void Network::networkAccessChanged(QNetworkAccessManager::NetworkAccessibility accessable)
{

}

void Network::preSharedKeyAuthenticationRequired(QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator)
{

}

void Network::proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator)
{

}

void Network::sslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{

}

void Network::error()
{

}


