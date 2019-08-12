#include "network.h"
#include <QtWidgets>

Network::Network(QWidget *parent):  QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    lastFileLength = -1;
    lastReply = nullptr;

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

    QString targetFolder = "/home/elwin/Downloads";
    QString fileName = "TEST_CRE.exe";
    mFile = new QFile( targetFolder + QDir::separator() + fileName);
    // Trying to open the file
    if (!mFile->open(QIODevice::WriteOnly)){
        qDebug() << "Could not open file";
        delete mFile;
        mFile = nullptr;
    }
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(url)));

    //reply->setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    lastReply = reply;
    replys.push_back(reply);
    //connect(reply, &QNetworkReply::readyRead, this, &Network::readyRead);
    connect(reply, SIGNAL(finished()), this, SLOT(finished()));
    //connect(this, SIGNAL(cancelDownload()), reply, SLOT(abort()));



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
    reply->deleteLater();



}

void Network::readyRead()
{
    qDebug() << "Got some data and ready to read";
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender()); // alternative way to get reply without a paremeter
    if(reply){
        //we have a reply
        qDebug() << reply->readAll();
        if(mFile->isOpen()) {
            mFile->write(reply->readAll());
            mFile->flush();
            mFile->close();
        }
    }


    reply->deleteLater();
}

void Network::authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator)
{
    Q_UNUSED(reply);
    Q_UNUSED(authenticator);

    qDebug() << "Authentication Requred";

}

void Network::encrypted(QNetworkReply *reply)
{
    Q_UNUSED(reply);

    qDebug() << "Encrypted";

}

void Network::finished()
{

    qDebug() << "Finished";
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender()); // alternative way to get reply without a paremeter
    if(reply){
        //we have a reply
        //qDebug() << reply->readAll();
        if(mFile) {
            qDebug() << "file is open attempting to write";
            mFile->write(reply->readAll());
            mFile->flush();
            mFile->close();
            qDebug() << "Finished writing to file, file closed";

            //set a flag to start a process to execute the exe file
        }
    }


    //reply->deleteLater();

}

void Network::networkAccessChanged(QNetworkAccessManager::NetworkAccessibility accessable)
{

    Q_UNUSED(accessable);

    qDebug() << "Network Access Changed";

}

void Network::preSharedKeyAuthenticationRequired(QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator)
{
    Q_UNUSED(reply);
    Q_UNUSED(authenticator);

    qDebug() << "Pre Shared Key Authentication Required";

}

void Network::proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator)
{
    Q_UNUSED(proxy);
    Q_UNUSED(authenticator);
    qDebug() << "Proxy Authentication Required";

}

void Network::sslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    Q_UNUSED(reply);
    Q_UNUSED(errors);

    qDebug() << "SSL Errors";

}

void Network::error()
{
    qDebug() << "error";
}

int Network::getFileLength()
{
    return lastFileLength;

}

QNetworkAccessManager *Network::getAccessManager()
{
 return manager;
}

QNetworkReply *Network::getLastReply()
{
    return lastReply;

}

vector<QNetworkReply *> Network::getReplys()
{
    return replys;

}

void Network::closeAllConnections()
{
    for(QNetworkReply *reply: replys){

        disconnect(reply, SIGNAL(finished()), this, SLOT(finished()));
        reply->abort();
        reply->deleteLater();
    }
    replys.clear();
    if(mFile){
        mFile->flush();
        mFile->close();
    }

}


