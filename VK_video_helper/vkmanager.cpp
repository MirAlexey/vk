#include "vkmanager.h"

using namespace QtJson;

VKmanager::VKmanager(QObject *parent) :
    QObject(parent)
{
}

void VKmanager::queryForUploadVideoFile(VideoFile *vf, Account *account, QString id_group)
{
    QString url_query = QString("https://api.vk.com/method/video.save?v=5.34&access_token=%1&name=\"%2\"&description=\"%3\"&wallpost=%4&group_id=%5").arg(account->getAccountToken()).arg(vf->GetNameFile()).arg(vf->GetDescriptionFile()).arg("0").arg(id_group);
    qDebug() << url_query;
    QByteArray ansver = Get(url_query);
    if(ansver.isEmpty()) {
        qDebug() << "Пустой ответ";
        QString s = "-1";

        QEventLoop wait6;
        QTimer::singleShot(1000,&wait6,SLOT(quit()));
        wait6.exec();
        QByteArray ansver = Get(url_query);
        if(ansver.isEmpty()) {
            QMessageBox::information(0,"Пустой ответ! Нет ответа на выгрузку файла.",ansver,QMessageBox::Ok);
            return;
        }
    }
    qDebug()<< ansver;

    QStringList sl;
    QVariantMap videoinfo = parse(ansver).toMap().value("response").toMap();
    if (!videoinfo.isEmpty()){

        QString upload_url = videoinfo.value("upload_url").toString();
        QString new_video_id = videoinfo.value("video_id").toString();
        QString owner_id = videoinfo.value("owner_id").toString();
        QString title = videoinfo.value("title").toString();
        QString description = videoinfo.value("description").toString();
        QString access_key = videoinfo.value("access_key").toString();
        vf->SetAccess_key(access_key);
        //vf->SetOwner_id(owner_id);
        vf->SetTitle(title);
        vf->SetNewVideo_id(new_video_id);

        QNetworkAccessManager* manager = new QNetworkAccessManager(this);
        QNetworkRequest request = QNetworkRequest(QUrl(upload_url));
        //request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("multipart/form-data")); // непонятно почему установка этого хедера ломает отправку ??? хотя он вроде должен быть
        QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
        QHttpPart imagePart;
        QString s3;
        QString s1 = "video/mpeg";
        if (vf->GetNameFile().contains(".mp4")) {s1 = "video/mp4"; s3=".mp4";}
        if (vf->GetNameFile().contains(".flv")) {s1 = "video/x-flv";s3=".flv";}

        imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant(s1));
        imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"video_file\";filename=\""+vf->GetNameFile()+s3+"\""));
        //QFile *file = new QFile(vf->GetLinkFile());
        if (vf->GetContent() != NULL)
        { qDebug()<< "Длина файла на отдачу:" << (*vf->GetContent()).count();
            if (!(*vf->GetContent()).isNull()){
                if (!(*vf->GetContent()).isEmpty())
                    imagePart.setBody(*vf->GetContent());
                    qDebug() << "контент пуст?" <<(*vf->GetContent()).isEmpty();
            } else {
                qDebug()<< "удаление";
                if (vf->GetContent() != NULL)delete vf->GetContent();
                vf->SetContent(NULL);
                vf->SetStatusDownload(false);
                emit uploadfilefail();
                return;
            }
        }


    else{
        QFile *file = new QFile(vf->GetNameFileOnDisk());
        file->open(QIODevice::ReadOnly);
        if (!file->isOpen())
            for (int i = 1; i <6;i++){
                if (file->open(QIODevice::ReadOnly)) break;
                QEventLoop wait7;
                QTimer::singleShot(i*1000,&wait7,SLOT(quit()));
                wait7.exec();
            }
        if (!file->isOpen()) {
            qDebug()<< "Ошибка открытия файла";
            emit toLog("Ошибка открытия файла");
            delete file;
            file = NULL;
            multiPart->deleteLater();
            vf->SetStatusDownload(false);
            emit uploadfilefail();
            return;
        }
        imagePart.setBodyDevice(file);
        file->setParent(multiPart);
        // we cannot delete the file now, so delete it with the multiPart
    }

    multiPart->append(imagePart);


    QList<QByteArray> hl = request.rawHeaderList();
    for (int i=0;i<hl.count();i++) qDebug() << hl.at(i);
    qDebug() << request.url().toString();
    QNetworkReply *reply = manager->post(request, multiPart);
    multiPart->setParent(reply);// delete the multiPart with the reply
    connect(reply,SIGNAL(uploadProgress(qint64,qint64)),this,SLOT(onUploadProgress(qint64,qint64)));
    connect(reply,SIGNAL(finished()),this,SLOT(uploadfilefinished()));
    //connect(reply,SIGNAL(finished()),manager,SLOT(deleteLater()));
    connect(reply,SIGNAL(finished()),multiPart,SLOT(deleteLater()));
    return;
    }
    qDebug() << "Неверный запрос на скачивание файла!";

}



void VKmanager::queryGetListVideoFile(QString id_VK_or_screen_name, Account *account)
{   int offset_video = 0;
    int videocount = 0;
    int i_count = 0;
    QStringList sl;
    do
    {
        QEventLoop wait;
        QTimer::singleShot(400,&wait,SLOT(quit()));
        wait.exec();


        offset_video = i_count;
        QString url_query = QString("https://api.vk.com/method/video.get?v=5.34&access_token=%1&owner_id=-%2&offset=%3").arg(account->getAccountToken()).arg(id_VK_or_screen_name).arg(QString::number(offset_video));
        QByteArray ansver = Get(url_query);
        if(ansver.isEmpty()) {
            qDebug() << "Пустой ответ";
            QString s = "-1";
            QMessageBox::information(0,"Пустой ответ! Не получен список видеофайлов",ansver,QMessageBox::Ok);
            return;
        }
        qDebug()<< ansver;


        QVariantList videoinfo = parse(ansver).toMap().value("response").toMap().value("items").toList();
        QVariantMap video_item;
        videocount = parse(ansver).toMap().value("response").toMap().value("count").toInt();

        int tek_kol_video =  videoinfo.count();
        for (int i = 0;i<tek_kol_video ;i++){
            video_item = videoinfo[i].toMap();
            QString namefile = video_item.value("title").toString();
            QString video_id = video_item.value("id").toString();
            //QString owner_id = video_item.value("owner_id").toString();
            QString owner_id = id_VK_or_screen_name;
            QString title = video_item.value("title").toString();
            QString description = video_item.value("description").toString();
            QString player = video_item.value("player").toString();
            sl << namefile << player <<  description << " "<<title <<owner_id << video_id << "false"<<"false";
        }
        i_count+=tek_kol_video;
    } while(videocount-offset_video>100);
    emit searshVideoFinished(sl);
}

void VKmanager::querySearchVideo(QString access_token, QString parameters_searching, QString offset_start, QString count_finish, QString sort_type, QString type_group)
{

}

void VKmanager::queryNewAccount()
{
    QWebView *web = new QWebView();
    web->load(QUrl("https://oauth.vk.com/authorize?client_id=5000210&scope=offline,messages,wall,video&redirect_uri=https://oauth.vk.com/blank.html&display=popup&v=5.34&response_type=token"));
    web->show();


    connect(web,SIGNAL(urlChanged(QUrl)),this,SLOT(web_url_change(QUrl)));

}



void VKmanager::web_url_change(QUrl url)
{
    url = url.toString().replace("#", "?");
    QString token = QUrlQuery(url).queryItemValue("access_token");
    if (!token.isEmpty())QMessageBox::information(0,"token",token,QMessageBox::Ok);
    else return; //QMessageBox::warning(0,"token","oy oy oy",QMessageBox::Ok);

    QString url_query = "https://api.vk.com/method/users.get?v=5.34&access_token="+token;

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
    sl << token <<first_name  << last_name<< id_vk;
    emit receivedNewAccount(sl);
}

void VKmanager::uploadfilefinished()
{
   QObject* obj=QObject::sender();
   QByteArray ansver = static_cast<QNetworkReply*>(obj)->readAll() ;
   //QByteArray ansver = reply->readAll();
   qDebug() << ansver;
   static_cast<QNetworkReply*>(obj)->deleteLater();
   if (ansver.contains("error") || ansver.contains("<html>"))
   {
       qDebug()<< "Ошибка. Ответ сервера:" << ansver;
       emit uploadfilefail();
   }else emit uploadfilesuccess();

   //delete reply;
   //reply = NULL;

}

void VKmanager::onUploadProgress(qint64 int1, qint64 int2)
{
    emit UploadProgress(int1,int2);
}


QByteArray VKmanager::Get(QUrl url)
{
   qDebug()<<url.toString();
   QNetworkAccessManager* manager = new QNetworkAccessManager(this);

   QNetworkReply *reply = manager->get(QNetworkRequest(url));

   QEventLoop wait;
   connect(manager, SIGNAL(finished(QNetworkReply*)), &wait, SLOT(quit()));

   QTimer::singleShot(15000,&wait,SLOT(quit()));
   wait.exec();

   QByteArray ansver = reply->readAll();

   delete reply;
   reply = NULL;

//   reply->deleteLater();
//   manager->deleteLater();
     delete manager;
     manager = NULL;





   return ansver;

}


QByteArray VKmanager::Post(QUrl url,QByteArray data)
{
    //QNetworkAccessManager* manager = new QNetworkAccessManager(this);



//    QNetworkRequest request = QNetworkRequest(QUrl(str1));
//    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

//    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);


//    QHttpPart imagePart;
//    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
//    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"image\""));
//    QFile *file = new QFile("image.jpg");
//    file->open(QIODevice::ReadOnly);
//    imagePart.setBodyDevice(d);
//    file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart

//    multiPart->append(textPart);
//    multiPart->append(imagePart);

//    QUrl url("http://my.server.tld");
//    QNetworkRequest request(url);

//    QNetworkAccessManager manager;
//    QNetworkReply *reply = manager.post(request, multiPart);
//    multiPart->setParent(reply); // delete the multiPart with the reply




//    QNetworkReply* repley = manager->post(request,str2.toUtf8());

//    QEventLoop wait;
//    connect(manager, SIGNAL(finished(QNetworkReply*)), &wait, SLOT(quit()));

//    QTimer::singleShot(10000,&wait,SLOT(quit()));
//    wait.exec();

//    QByteArray ansver = repley->readAll();
//    repley->deleteLater();
//    qDebug()<< endl<<"Ответ: " << ansver;
//    return ansver;

return QByteArray();



}
