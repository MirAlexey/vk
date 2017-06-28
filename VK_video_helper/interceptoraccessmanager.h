#ifndef INTERCEPTORACCESSMANAGER_H
#define INTERCEPTORACCESSMANAGER_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QNetworkCookieJar>
#include <QNetworkCookie>
#include <QDebug>
#include <QVariant>

class InterceptorAccessManager : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit InterceptorAccessManager(QObject *parent = 0);

signals:
     void FoundFileName(QString);
public slots:


    // QNetworkAccessManager interface
protected:
    QNetworkReply *createRequest(Operation op, const QNetworkRequest &request, QIODevice *outgoingData);
};

#endif // INTERCEPTORACCESSMANAGER_H
