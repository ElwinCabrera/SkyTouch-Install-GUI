#include "network.h"

Network::Network()
{

}

void Network::get(QString url)
{
    qDebug() << "getting form server";
    QNetworkRequest request(QUrl(url));
    QNetworkReply *reply = manager.get(request);
    connect(reply, &QNetworkReply::readyRead, this, &Network::readyRead);


}

void Network::post(QString url, QByteArray data)
{

}

void Network::readyRead()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if(reply){
        //we have a reply
        qDebug() << reply->readAll();
    }
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


