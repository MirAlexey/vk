#include "interceptoraccessmanager.h"

InterceptorAccessManager::InterceptorAccessManager(QObject *parent) :
    QNetworkAccessManager(parent)
{
}


QNetworkReply *InterceptorAccessManager::createRequest(Operation op, const QNetworkRequest &request, QIODevice *outgoingData)
{
    QString s =request.url().toString() ;
    // qDebug()<< "[REQUEST]" << s ;
    //QRegExp rx("https?:\/\/(([a-zA-Z0-9][a-zA-Z0-9_-]*\.*)*\/)*([a-zA-Z0-9][a-zA-Z0-9_-]*\.)*mp4");//"https://cs518117.vk.me/u58622976/videos/e1c59460d6.360.mp4?  /^(http|https|ftp)://([A-Z0-9][A-Z0-9_-]*(?:.[A-Z0-9][A-Z0-9_-]*)+):?(d+)?/?/i
    QRegExp rx1("https?:\/\/[a-zA-Z0-9]([a-zA-Z0-9_-]*\.)*vk\.*([a-zA-Z0-9_-]*\.*)*(\/*([a-zA-Z0-9_-]*\.*))*(\.mp4|\.flv)");
    rx1.indexIn(s,0);


    if (rx1.cap(0)!="")
    {
        qDebug() << "[REQUEST PATTERN]" << rx1.indexIn(s,0)<<" "<< rx1.cap(0)<< rx1.isValid();
        emit FoundFileName(rx1.cap(0));
    }
//    QList<QByteArray> hba = request.rawHeaderList();
//    for (int i=0;i<hba.count();i++) qDebug() <<hba.at(i);
//    qDebug()<< "CD" <<request.header(QNetworkRequest::ContentDispositionHeader).toStringList();
//    qDebug()<< "CT" <<request.header(QNetworkRequest::ContentTypeHeader).toStringList();
//    qDebug()<< "CL" <<request.header(QNetworkRequest::ContentLengthHeader).toStringList();
//    qDebug()<< "L" <<request.header(QNetworkRequest::LocationHeader).toStringList();
//    qDebug()<< "LM" <<request.header(QNetworkRequest::LastModifiedHeader).toStringList();
//    qDebug()<< "C" <<request.header(QNetworkRequest::CookieHeader).toStringList();

//    qDebug()<< "UA" <<request.header(QNetworkRequest::UserAgentHeader).toStringList();
//    qDebug()<< "S" <<request.header(QNetworkRequest::ServerHeader).toStringList();
//    QNetworkCookieJar *c = this->cookieJar();
//    QList<QNetworkCookie> lc = c->cookiesForUrl(request.url());
//    for(int i=0;i<lc.count();i++) qDebug() << lc.at(i).value();
    QNetworkReply *real = QNetworkAccessManager::createRequest(op, request, outgoingData);
    return real;
}
