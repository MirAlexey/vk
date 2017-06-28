#include "vkmanager.h"

using namespace QtJson;

VKmanager::VKmanager(QObject *parent) :
    QObject(parent)
{
}

void VKmanager::queryNewAccount()
{
    web = new QWebView;
    web->load(QUrl("https://oauth.vk.com/authorize?client_id=4861588&scope=offline,messages,wall&redirect_uri=https://oauth.vk.com/blank.html&display=popup&v=5.28&response_type=token"));
    web->show();
    connect(web,SIGNAL(urlChanged(QUrl)),this,SLOT(web_url_change(QUrl)));
}



void VKmanager::web_url_change(QUrl url)
{
    url = url.toString().replace("#", "?");
    QString token = QUrlQuery(url).queryItemValue("access_token");
    if (!token.isEmpty())QMessageBox::information(0,"token",token,QMessageBox::Ok);
    else return; //QMessageBox::warning(0,"token","oy oy oy",QMessageBox::Ok);

    QString url_query = "https://api.vk.com/method/users.get?v=5.2&access_token="+token;

    QByteArray ansver = Get(QUrl(url_query));

    if(ansver.isEmpty()) {
           qDebug() << "Пустой ответ";
           return;
           }

    QVariantMap Qvm= parse(ansver).toMap();
    QVariantList flist= Qvm.value("response").toList();
    QVariantMap fmap = flist[0].toMap();
    QString id_vk = fmap.value("id").toString();
    QString first_name = fmap.value("first_name").toString();
    QString last_name = fmap.value("last_name").toString();
    QStringList sl;
    sl << id_vk << token <<first_name << last_name;
    emit receivedNewAccount(sl);

}

void VKmanager::setActiveSendingPost(bool b)
{
    this->activeSendingPost = b;
}
void VKmanager::queryNewGroup(QString id_VK_or_screen_name)
{
    QString url_query = "https://api.vk.com/method/groups.getById?v=5.2&field=members_count,description&group_id="+id_VK_or_screen_name;

    //QByteArray ansver = Get(QUrl(url_query));
    QByteArray ansver =  Post(QUrl(url_query));

    if(ansver.isEmpty()) {
           qDebug() << "Пустой ответ";
           return;
           }
    if (ansver.contains("{\"error\":{\"error_code")) {
        qDebug() << "Ошибочный запрос";
        return;
    }
    QVariantList flist = parse(ansver).toMap().value("response").toList();
    QVariantMap fmap = flist[0].toMap();
    QString id_vk = fmap.value("id").toString();
    QString name = fmap.value("name").toString();
    QString screen_name = fmap.value("screen_name").toString();
    QString type_gr = fmap.value("type").toString();
    QString descr = fmap.value("description").toString();
    QString member_count = fmap.value("member_count").toString();;
    QStringList sl;
    sl << name<< type_gr<< member_count<< id_vk   << screen_name  << descr ;

    emit receivedNewGroup(sl);
}

void VKmanager::querySearchGroups(QString access_token,QString parameters_searching, QString offset_start = "0", QString count_finish = "250", QString sort_type = "0", QString type_group = "group")
{
    QString url_query = QString("https://api.vk.com/method/groups.search?v=5.2&q=%1&offset=%2&count=%3&sort=%4&type=%5&access_token=%6&fields=description,members_count").arg(parameters_searching).arg(offset_start).arg(count_finish).arg(sort_type).arg(type_group).arg(access_token);
    qDebug()<< url_query;
    //QByteArray ansver = Get(QUrl(url_query));
    QByteArray ansver =  Post(QUrl(url_query));
    QString str = ansver;
    emit StringtoLog(str, true,QColor("blu"));

    if(ansver.isEmpty()) {
           qDebug() << "Пустой ответ";
           return;
           }
    if (ansver.contains("{\"error\":{\"error_code")) {
        qDebug() << "Ошибочный запрос";
        return;
    }
    //ansver.replace("[","");
    //ansver.replace("]","");

    int count_item =parse(ansver).toMap().value("response").toMap().value("count").toInt();
    QStringList sl;
    int count_item_in_query = count_finish.toInt();
    int max_item = count_item_in_query>count_item?count_item:count_item_in_query;
     QVariantList flist = parse(ansver).toMap().value("response").toMap().value("items").toList();
     if (!flist.isEmpty()){
     max_item=flist.count()<max_item?flist.count():max_item;
    for (int i=0; i<max_item;i++){
        QVariantMap fmap = flist[i].toMap();
        QString id_vk = fmap.value("id").toString();
        QString name = fmap.value("name").toString();
        QString screen_name = fmap.value("screen_name").toString();
        QString type_gr = fmap.value("type").toString();
        QString descr = fmap.value("description").toString();
        QString member_count = fmap.value("members_count").toString();;
        sl  << name << type_gr  << member_count<< id_vk << screen_name <<  descr;
    }
     }
    emit receivedSearshGroup(sl,count_item,max_item);

}

void VKmanager::querySendPost(post *p, grouplist *gl, accountlist *al, int delay)
{
    QEventLoop wait;
    if(!activeSendingPost){
        QEventLoop wait2;
        QTimer::singleShot(1000,&wait2,SLOT(quit()));
        wait2.exec();
    }
    if(!activeSendingPost) {emit SentPostFinishvkm();
                            return;}
    //int acc_count = 0;
    gl->begin();
    al->begin();
    while(gl->hasnextitem()){
        group *g = gl->nextitem();
        if (!al->hasnextitem()) al->begin();
        account *a = al->nextitem();
        while (!a->isready()) {
                              al->removeitem(a);
                              al->begin();
                              a =al->nextitem();
                              if (al->countitem()<1) break;
                              }
        if (al->countitem()<1){
            QMessageBox::warning(0,"Внимание!","Кончился запас отправлений. Пост: "+p->GetNamePost(),QMessageBox::Ok);
            QString s = "Внимание! Кончился запас отправлений. Пост: "+p->GetNamePost();
            emit StringtoLog(s,false,QColor("blu"));
            return;
        }
        if (delay>50){
            QTimer::singleShot(delay,&wait,SLOT(quit()));
            wait.exec();
            }

        QUrlQuery cur;
        cur.setQuery("https://api.vk.com/method/wall.post?v=5.28");
        qDebug() <<  cur.toString();
        cur.addQueryItem("owner_id","-"+QString::number(g->getID()));
        cur.addQueryItem("access_token",a->getAccountToken());
        if (!p->GetTextPost().isEmpty()) cur.addQueryItem("message",p->GetTextPost());
        if (!p->GetAttachPost().isEmpty()) cur.addQueryItem("attachments",p->GetAttachPost());
        qDebug() <<   cur.toString();

        QUrl current = cur.toString().replace("#","%23");
        qDebug() <<  current.toString();

        //QByteArray ansver = Get(current);
        QByteArray ansver =  Post(current);

        if(ansver.isEmpty()) {
            qDebug() << "Пустой ответ";
            QString s ="Пустой ответ. Пост:"+ p->GetNamePost()+ "   Группа:"+ g->getName();
            emit StringtoLog(s,false,QColor("blu"));
            //inLog(u->GetName()+" "+g.GetID()+" нет ответа");
            //if (StatTimer) timer->start(ui->spinBox->value());
             s = "-1";
           emit SentPost(p,g,a,s,false);
           a->upcounter();
           continue;
        }
        if(ansver.contains("{\"error\":{\"error_code")){
            qDebug() << "Сообщение об ошибке";
            QString s = "Ошибка. Пост:"+ p->GetNamePost()+ "   Группа:"+ g->getName()+" Акк.:"+a->getName();
            emit StringtoLog(s,true,QColor("red"));
            s = ansver;
            emit StringtoLog(s,false,QColor("black")) ;
            qDebug() << ansver;
            //            inLog(u->GetName()+" "+g.GetID()+" Ok");
            //            if (StatTimer) timer->start(ui->spinBox->value());
            s = "-1";
            emit SentPost(p,g,a,s,false);
            a->upcounter();
            continue;
        }

        QString id_post_on_wall = parse(ansver).toMap().value("response").toMap().value("post_id").toString();
        QString s = "Успех. Пост:"+ p->GetNamePost()+ " Группа:"+ g->getName()+" Акк.:"+a->getName();
        emit StringtoLog(s,true,QColor("green"));
        a->upcounter();
        emit SentPost(p,g,a,id_post_on_wall,true);

    }
    emit SentPostFinishvkm();
}

void VKmanager::queryTestPost(post *p, QString id_group, accountlist *al)
{
    al->begin();
    account *a= al->nextitem();
    for (int i = 0; i < al->countitem();i++ )
    {a = al->nextitem();
        if (a->isready()) break;
    }
    if (!a->isready()){QMessageBox::information(0,"Внимание","Список доступных аккаунтов исчерпан!",QMessageBox::Ok);return;}

    QUrlQuery cur;
    cur.setQuery("https://api.vk.com/method/wall.post?v=5.28");
    qDebug() <<  cur.toString();
    cur.addQueryItem("owner_id","-"+id_group);
    cur.addQueryItem("access_token",a->getAccountToken());
    qDebug()<< p->GetTextPost().toUtf8();
    qDebug() << QUrl::toPercentEncoding(p->GetTextPost().toUtf8());
    QByteArray ba = QUrl::toPercentEncoding(p->GetTextPost().toUtf8());
    if (!p->GetTextPost().isEmpty()) cur.addQueryItem("message",ba);
    if (!p->GetAttachPost().isEmpty()) cur.addQueryItem("attachments",p->GetAttachPost());

    QUrl current =cur.toString();//.toString().replace("#","%23");
    qDebug() <<  current.toString();

    QByteArray ansver =  Post(current);// Get(current);
   // QByteArray ansver =  Get(current);
    qDebug() << ansver;

    if(ansver.isEmpty()) {
        qDebug() << "Пустой ответ";

        QString s = "-1";

        QMessageBox::information(0,"Пустой ответ!",ansver,QMessageBox::Ok);


    }
    if(ansver.contains("{\"error\":{\"error_code")){
        qDebug() << "Сообщение об ошибке";
        qDebug() << ansver;
        QMessageBox::information(0,"Сообщение об ошибке!",ansver,QMessageBox::Ok);
        QString s = "-1";


    }
    a->upcounter();
}






QByteArray VKmanager::Get(QUrl url)
{
   QNetworkAccessManager* manager = new QNetworkAccessManager(this);

   QNetworkReply* repley = manager->get(QNetworkRequest(url));

   QEventLoop wait;
   connect(manager, SIGNAL(finished(QNetworkReply*)), &wait, SLOT(quit()));

   QTimer::singleShot(10000,&wait,SLOT(quit()));
   wait.exec();

   QByteArray ansver = repley->readAll();
   repley->deleteLater();

   return ansver;

}

QByteArray VKmanager::Post(QUrl url)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QString str = url.toString();
    QString str1= str.left(str.indexOf("?"));
    QString str2= str.right(str.length()-str.indexOf("?")-1);
    qDebug()<<endl <<str << endl << str1 << endl<< str2;


    QNetworkRequest request = QNetworkRequest(QUrl(str1));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");


    QNetworkReply* repley = manager->post(request,str2.toUtf8());

    QEventLoop wait;
    connect(manager, SIGNAL(finished(QNetworkReply*)), &wait, SLOT(quit()));

    QTimer::singleShot(10000,&wait,SLOT(quit()));
    wait.exec();

    QByteArray ansver = repley->readAll();
    repley->deleteLater();
    qDebug()<< endl<<"Ответ: " << ansver;
    return ansver;

return QByteArray();



}
