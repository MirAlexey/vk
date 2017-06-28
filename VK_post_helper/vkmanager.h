#ifndef VKMANAGER_H
#define VKMANAGER_H

#include <QObject>
#include <QStringList>
#include <listmanager.h>
#include <QUrl>
#include <QUrlQuery>
#include <QVariant>
#include <QVariantList>
#include <QVariantMap>
#include <json.h>
#include <QMessageBox>
#include <QUrlQuery>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QEventLoop>
#include <QTimer>
#include <QDebug>
#include <QMap>
#include <QtWebKit/QtWebKit>
#include <QDateTime>
#include <QWebView>




class VKmanager : public QObject
{
    Q_OBJECT
public:
    explicit VKmanager(QObject *parent = 0);
    void       queryNewAccount();
    void       queryNewGroup(QString id_VK_or_screen_name);
    void       querySearchGroups(QString access_token,QString parameters_searching, QString offset_start, QString count_finish, QString sort_type, QString type_group);
    void       querySendPost(post *p, grouplist *gl, accountlist *al, int delay);
    void       queryTestPost(post *p,QString id_group, accountlist *al);
private:

    QByteArray Get(QUrl url);
    QByteArray Post(QUrl url);

    QWebView *web;
    QTimer *timer;
    bool activeSendingPost;
signals:
    void receivedNewAccount(QStringList&);
    void receivedNewGroup(QStringList&);
    void receivedSearshGroup(QStringList&,int,int);
    void SentPost(post*,group*,account*,QString&,bool);
    void SentPostFinishvkm();
    void StringtoLog(QString&, bool,QColor);

public slots:
void web_url_change(QUrl url);
void setActiveSendingPost(bool b);

};

#endif // VKMANAGER_H
