#include "network.h"
#include <QtWidgets>

Network::Network(QWidget *parent):  QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    lastFileLength = -1;
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
    qDebug() << "getting header form server";
    QNetworkReply *reply = manager->head(QNetworkRequest(QUrl(url)));

   // connect(reply, &QNetworkReply::finished, this, &Network::readyRead);



    QTimer timer;
    timer.setSingleShot(true);

    QEventLoop loop;
    connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    timer.start(30000);   // 30 secs. timeout
    loop.exec();

    if(timer.isActive()) {
        timer.stop();
        if(reply->error() > 0) {
           // handle error
        } else {
          int v = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

          if (v >= 200 && v < 300) {  // Success
              lastFileLength = reply->header(QNetworkRequest::ContentLengthHeader).toInt();
              qDebug() << "File lenght is: "<< lastFileLength;
          }
        }
    } else {
       // timeout
       disconnect(reply, SIGNAL(finished()), &loop, SLOT(quit()));

       reply->abort();
    }



}

void Network::readyRead()
{
    qDebug() << "Got some data and ready to read";
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender()); // alternative way to get reply without a paremeter
    if(reply){
        //we have a reply
        qDebug() << reply->readAll();
    }
    if(reply->operation() == QNetworkAccessManager::HeadOperation){
        lastFileLength = reply->header(QNetworkRequest::ContentLengthHeader).toInt();
        qDebug() << "File lenght is: "<< lastFileLength;
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

int Network::getFileLength()
{
    return lastFileLength;

}


