#include "castomvkwebview.h"

EnterinVK *EnterinVK::_instance = 0;
GetFileNameVK* GetFileNameVK::_instance = 0;
NopOperationVK* NopOperationVK::_instance = 0;
RunVideoVK* RunVideoVK::_instance = 0;
EnterLoginPass* EnterLoginPass::_instance = 0;
GetFileNameVK2_1* GetFileNameVK2_1::_instance = 0;
GetFileNameVK3_1* GetFileNameVK3_1::_instance = 0;
GetFileNameVK2_2* GetFileNameVK2_2::_instance = 0;
GetFileNameVK2_3* GetFileNameVK2_3::_instance = 0;
RunVideoVK2* RunVideoVK2::_instance = 0;







CastomVKwebview::CastomVKwebview(QWidget *parent) :
    QWebView(parent)
{






    timer = new QTimer(this);
    interceptor = new InterceptorAccessManager(this);
    connect(interceptor,SIGNAL(FoundFileName(QString)),this,SLOT(onFoundFileName(QString)));
    QWebSettings *webset = this->settings();
    webset->setAttribute(QWebSettings::PluginsEnabled,true);
    webset->setAttribute(QWebSettings::JavascriptEnabled,true);
    webset->setAttribute(QWebSettings::JavaEnabled, true);
    webset->setAttribute(QWebSettings::JavascriptCanOpenWindows, true);
    this->page()->setNetworkAccessManager(interceptor);
    //connect(this, SIGNAL(loadFinished(bool)),this, SLOT(onLoadFinished()));
    tek_operationVK = EnterLoginPass::Instance(this);
    type_saving_file = false;
    metod_download = true;
    file=NULL;
    reply = NULL;
    connect(tek_operationVK, SIGNAL(SuccessOperation(bool)),this,SLOT(onLoadFinished()));

    connect(timer,SIGNAL(timeout()),this,SLOT(onFailDownUpLoadFile()));

}


QString CastomVKwebview::GetCurrentUrlFile()
{
    return url_file;
}

QString CastomVKwebview::GetCurrentFileName()
{
    return filename;
}

void CastomVKwebview::StartTimer()
{
    timer->start(20000);
}

void CastomVKwebview::StopTimer()
{
    timer->stop();
}

void CastomVKwebview::onDownloadProgress(qint64 int1, qint64 int2)
{
    emit DownloadProgress(int1,int2);
}


void CastomVKwebview::LoadVideoFilefromVK(VideoFile *vf, Account *acc)
{
    QRegExp rx1("https?:\/\/[a-zA-Z0-9]([a-zA-Z0-9_-]*\.)*vk\.*([a-zA-Z0-9_-]*\.*)*(\/*([a-zA-Z0-9_-]*\.*))*(\.mp4|\.flv)");
    rx1.indexIn(vf->GetLinkFile(),0);
    tek_vf = vf;
    tek_acc = acc;
    filename = vf->GetNameFile();
    url_file = vf->GetLinkFile();
    if (vf == NULL) return;
    if (rx1.cap(0)!="") {
        this->onFoundFileName(vf->GetLinkFile());
        return;
    }


    connect(this->page(), SIGNAL(loadFinished(bool)),this, SLOT(onLoadFinished()));
    this->load(QUrl("https://vk.com"));
}
void CastomVKwebview::onFailDownUpLoadFile()
{
    tek_operationVK = GetFileNameVK3_1::Instance(this);
    emit FailDownUpLoadFile();
}



void CastomVKwebview::onLoadFinished()
{
   // qDebug()<< "next";
   tek_operationVK->RunOperation(this);
}

void CastomVKwebview::onFileLoadingFinished()
{
    //QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (reply->error() == QNetworkReply::NoError){
        if (!type_saving_file) {
            //             QString s;
            //             QRegExp rx1("(\.mp4|\.flv)");
            //             rx1.indexIn(this->tek_vf->GetLinkFile(),0);
            //             s = rx1.cap(0);
            //             tek_vf->SetNameFileOnDisk(this->GetCurrentDir()+this->GetCurrentFileName()+s);
            tek_vf->SetNameFileOnDisk(file->fileName());
            file->flush();
            file->close();
            delete file;
            file = NULL;
            this->tek_vf->SetStatusDownload(true);
            //type_saving_file = true;
          //reply->deleteLater();
            delete reply;
            reply = NULL;
            emit VideoFileisDownLoad();
            return;
        }
        try{
            qDebug() << "выделение";
            QByteArray *content = new QByteArray(reply->readAll());
            tek_vf->SetContent(content);
            qDebug()<< "Длина файла:" << (*tek_vf->GetContent()).count();
            this->tek_vf->SetStatusDownload(true);
            delete reply;
            reply = NULL;
            emit VideoFileisDownLoad();
            //qDebug()<< "Длина файла:" << (*tek_vf->GetContent()).count();
            //reply->deleteLater();
        }
        catch(std::bad_alloc &e)
        {
            try{
                QString s;
                QRegExp rx1("(\.mp4|\.flv)");
                rx1.indexIn(this->tek_vf->GetLinkFile(),0);
                s = rx1.cap(0);
                QFile *file = new QFile(this->GetCurrentDir()+this->GetCurrentFileName()+s);
                if (file->open(QIODevice::WriteOnly))
                {
                    if (file->write(reply->readAll()) >0){
                        this->tek_vf->SetStatusDownload(true);
                        tek_vf->SetNameFileOnDisk(this->GetCurrentDir()+this->GetCurrentFileName()+s);
                        emit VideoFileisDownLoad();
                    }
                } else {
                    type_saving_file = false;
                    this->onFailDownUpLoadFile();
                }
                tek_vf->SetContent(NULL);
                file->flush();
                file->close();
                delete file;
                file = NULL;
                delete reply;
                reply = NULL;
            }
            catch(std::bad_alloc) {
                qDebug()<< "Ошибка сохранения:" << e.what();
                tek_vf->SetContent(NULL);
                type_saving_file = false;
                delete reply;
                reply = NULL;
                this->onFailDownUpLoadFile();
                //reply->deleteLater();
                return;
            }
        }

      /*  *content = ;

                QFile file(this->GetCurrentDir()+this->GetCurrentFileName()+s);
                for (int i = 1; i <6;i++){
                    if (file.open(QIODevice::WriteOnly)) break;
                    QEventLoop wait7;
                    QTimer::singleShot(i*1000,&wait7,SLOT(quit()));
                    wait7.exec();
                }
                if(file.isOpen())
                {
                    if (content->count() == file.write(*content)){ ; // пишем в файл

                    this->tek_vf->SetLinkFile(this->GetCurrentDir()+this->GetCurrentFileName()+s);
                    qDebug()<< "загрузка завершена";}
                    else qDebug()<< "Ошибка записа файла. Файл записан не полностью.";
                }
                else {qDebug() << "Файл не доступен. Ошибка открытия файла";
                    emit toLog("Файл не доступен. Ошибка открытия файла");}
                file.close();*/
    } else {
        qDebug()<< "Ошибка в ответе сервера";
        this->onFailDownUpLoadFile();
    }
    //this->load(QUrl("https://vk.com"));
}

void CastomVKwebview::onReadyReadData()
{
    //QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    qDebug() << reply->header(QNetworkRequest::ContentDispositionHeader).toString();
    qDebug() << reply->header(QNetworkRequest::ContentTypeHeader).toString();
    qDebug() << reply->header(QNetworkRequest::ContentLengthHeader).toString();
    qDebug() << reply->header(QNetworkRequest::LocationHeader).toString();
    qDebug() << reply->header(QNetworkRequest::LastModifiedHeader).toString();
    qDebug() << reply->header(QNetworkRequest::CookieHeader).toString();
    qDebug() << reply->header(QNetworkRequest::SetCookieHeader).toString();
    qDebug() << reply->header(QNetworkRequest::UserAgentHeader).toString();
    qDebug() << reply->header(QNetworkRequest::ServerHeader).toString();


    if (reply->error() == QNetworkReply::NoError){
        if(file)
        {
           file->write(reply->readAll()); // пишем в файл
        }
        else {qDebug() << "Файл не доступен. Ошибка открытия файла";
              emit toLog("Файл не доступен. Ошибка открытия файла");}

       }
}



void CastomVKwebview::onFoundFileName(QString s)
{


    QUrl url(s);
    timer->stop();
    {
        QEventLoop wait;
        QTimer::singleShot(1000,&wait,SLOT(quit()));
        wait.exec();
    }

    this->tek_vf->SetLinkFile(s);

    this->page()->mainFrame()->evaluateJavaScript("window.history.back();");
    //QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        // создаем объект для запроса
    QNetworkRequest request(url);

        // Выполняем запрос, получаем указатель на объект
        // ответственный за ответ
    QString s2;
    QRegExp rx1("(\.mp4|\.flv)");
    rx1.indexIn(this->tek_vf->GetLinkFile(),0);
    s2 = rx1.cap(0);
    if (this->GetCurrentFileName().contains(s2))s2 ="";
    this->tek_vf->SetNameFile(this->GetCurrentFileName()+s2);

    if (!type_saving_file) {

        QString s1="";
        while (QFile::exists(this->GetCurrentDir()+s1+this->GetCurrentFileName()+s2)) {
          s1+="1"  ;
        }
        file = new QFile(this->GetCurrentDir()+s1+this->GetCurrentFileName().remove("/")+s2) ;
        qDebug() << file->fileName();
        file->open(QIODevice::Append);
        if  (!file->isOpen())
        {
            for (int i = 1; i <6;i++){
                if (file->open(QIODevice::Append)) break;
                QEventLoop wait7;
                QTimer::singleShot(i*1000,&wait7,SLOT(quit()));
                wait7.exec();
            }
        }
            if (!file->isOpen()) {
                qDebug()<< "Не открылся файл";
                return;
            }

        //this->tek_vf->SetNameFile(this->GetCurrentFileName()+s1+s2);
    }
    //QNetworkReply* reply=  manager->get(request);

        reply =  manager.get(request);
        // Подписываемся на сигнал о готовности загрузки

        connect(reply, SIGNAL(finished()),this, SLOT(onFileLoadingFinished()) );
        connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(onDownloadProgress(qint64,qint64)));
     if (!type_saving_file)
                connect(reply, SIGNAL(readyRead()),this, SLOT(onReadyReadData()) );


        qDebug()<< "Загрузка начата";

}





void CastomVKwebview::SetOperation(OperationVK *new_operationVK)
{
 if (new_operationVK) tek_operationVK =  new_operationVK;
}



bool EnterLoginPass::RunOperation(CastomVKwebview *vkweb)
{
    QWebElement input1 = vkweb->page()->mainFrame()->findFirstElement("input[name=email]");
    if (input1.isNull()) QMessageBox::critical(vkweb, "", "error");
    else   {input1.evaluateJavaScript("this.value = '"+ vkweb->tek_acc->getEmail()+"'");}
    input1 = vkweb->page()->mainFrame()->findFirstElement("input[name=pass]");
    if (input1.isNull()) QMessageBox::critical(vkweb, "", "error");
    else   {input1.evaluateJavaScript("this.value = '"+vkweb->tek_acc->getPass()+"'");}
    //OperationVK *p = new EnterinVK(vkweb);
    this->NextOperation(vkweb, EnterinVK::Instance(vkweb));
    emit SuccessOperation(true);
     return true;
}


bool EnterinVK::RunOperation(CastomVKwebview *vkweb)
{

        QEventLoop wait;
        QTimer::singleShot(500,&wait,SLOT(quit()));
        wait.exec();

    QWebElement button = vkweb->page()->mainFrame()->findFirstElement("button[id=quick_login_button]");

    if (button.isNull()) QMessageBox::critical(vkweb, "", "error",QMessageBox::Ok);


    else   {qDebug() << button.localName();
                        qDebug() << button.tagName();

            button.evaluateJavaScript("this.click();");
    }

    //emit  SuccessOperation(true);
     if (vkweb->metod_download)this->NextOperation(vkweb,GetFileNameVK::Instance(vkweb));
     else this->NextOperation(vkweb,GetFileNameVK3_1::Instance(vkweb));
     return true;
}

bool GetFileNameVK::RunOperation(CastomVKwebview *vkweb)
{

        QEventLoop wait;
        QTimer::singleShot(1000,&wait,SLOT(quit()));
        wait.exec();


   qDebug()<<"Запрос на получение адреса фильма";
   vkweb->load(QUrl(vkweb->tek_vf->GetLinkFile()));
   this->NextOperation(vkweb,RunVideoVK::Instance(vkweb));
   vkweb->StartTimer();
   return true;
}


bool RunVideoVK::RunOperation(CastomVKwebview *vkweb)
{
#ifdef Q_OS_WIN32

    disconnect(vkweb->page(), SIGNAL(loadFinished(bool)),vkweb, SLOT(onLoadFinished()));
    vkweb->show();
    vkweb->raise();
    vkweb->activateWindow();

        QEventLoop wait;
        QTimer::singleShot(4000,&wait,SLOT(quit()));
        wait.exec();


    vkweb->raise();
    vkweb->activateWindow();
    INPUT ip;
    ip.mi.time = 0;
    ip.type = INPUT_MOUSE;
    ip.mi.dx = 32000;
    ip.mi.dy=32000;
    ip.mi.mouseData = 0;

    ip.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
    SendInput(1, &ip, sizeof(INPUT));
    ip.mi.dwFlags =MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE;
    SendInput(1, &ip, sizeof(INPUT));
    ip.mi.dwFlags = MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE;
    SendInput(1, &ip, sizeof(INPUT));
    //qDebug()<< "nachalo";

      //  QEventLoop wait;
        QTimer::singleShot(1000,&wait,SLOT(quit()));
        wait.exec();


      vkweb->load(QUrl("https://vk.com"));

//    vkweb->activateWindow();
//    for (int i=0;i<1000;i++){
//        ip.mi.dx = 32000+i;
//        ip.mi.dy = 32000+i;
//        ip.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
//        SendInput(1, &ip, sizeof(INPUT));
//    }

//    vkweb->raise();
//    vkweb->activateWindow();

//    ip.mi.dwFlags =MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE;
//    SendInput(1, &ip, sizeof(INPUT));
//    ip.mi.dwFlags = MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE;
//    SendInput(1, &ip, sizeof(INPUT));
//    //qDebug()<< "okonchanie";
    this->NextOperation(vkweb,GetFileNameVK::Instance(vkweb));
#endif



    return true;
}

bool NopOperationVK::RunOperation(CastomVKwebview *vkweb)
{
    this->NextOperation(vkweb, GetFileNameVK::Instance(vkweb));
    return true;
}





bool GetFileNameVK2_1::RunOperation(CastomVKwebview *vkweb)
{


    QString s = QString("https://vk.com/videos-%1?section=all").arg(vkweb->tek_vf->GetOwner_id().remove("-"));
    qDebug()<<s;
//    if (vkweb->url().toString().contains(s))
//        vkweb->page()->mainFrame()->evaluateJavaScript("window.history.back();");
    vkweb->load(QUrl(s));
    this->NextOperation(vkweb, GetFileNameVK2_2::Instance(vkweb));

    return true;
}

bool GetFileNameVK2_2::RunOperation(CastomVKwebview *vkweb)
{
    disconnect(vkweb->page(), SIGNAL(loadFinished(bool)),vkweb, SLOT(onLoadFinished()));


    QEventLoop wait;
    QTimer::singleShot(400,&wait,SLOT(quit()));
    wait.exec();

    //QWebElementCollection *wec  = new QWebElementCollection();
    QWebElement we = vkweb->page()->mainFrame()->findFirstElement("input[id=\"v_search\"]");
    if (we.isNull()){ QMessageBox::critical(vkweb, "", "error",QMessageBox::Ok);
                          return false;}
    we.evaluateJavaScript("this.click();");
    //we.evaluateJavaScript("this.focus();");
    qDebug()<<"клик и фокус";

    #ifdef Q_OS_WIN32
    INPUT ip;

    ip.type = INPUT_KEYBOARD;
    ip.ki.time = 0;
    ip.ki.wVk = VK_RETURN;
    ip.ki.dwFlags = 0;
    ip.ki.wScan = 0;
//    vkweb->raise();
//    vkweb->activateWindow();
//    SendInput(1, &ip, sizeof(INPUT));
//    ip.ki.wVk = VK_LEFT;
//    SendInput(1, &ip, sizeof(INPUT));

    we.evaluateJavaScript("this.scrollIntoView();");
    we.evaluateJavaScript("this.value = '"+ vkweb->tek_vf->GetTitle()+"';");
    qDebug()<<"ввод параметра";

    this->NextOperation(vkweb, RunVideoVK2::Instance(vkweb));

    QTimer::singleShot(5000,&wait,SLOT(quit()));
    wait.exec();
    //connect(vkweb, SIGNAL(urlChanged(QUrl)),vkweb,SLOT(onLoadFinished()));
    vkweb->raise();
    vkweb->activateWindow();
    SendInput(1, &ip, sizeof(INPUT));
    qDebug()<<"1";
    emit SuccessOperation(true);
    #endif
    return true;
}

bool GetFileNameVK2_3::RunOperation(CastomVKwebview *vkweb)
{
        QEventLoop wait;
        QTimer::singleShot(400,&wait,SLOT(quit()));
        wait.exec();
    //if (!vkweb->url().toString().contains(vkweb->tek_vf->GetTitle())) return false;
    //disconnect(vkweb, SIGNAL(urlChanged(QUrl)),vkweb,SLOT(onLoadFinished()));
        //QWebElementCollection *wec  = new QWebElementCollection();
        QWebElement we = vkweb->page()->mainFrame()->findFirstElement("input[id=\"v_search\"]");
        if (we.isNull()){ QMessageBox::critical(vkweb, "", "error",QMessageBox::Ok);
                              return false;}


    //we.evaluateJavaScript("Video.updateList(onkeydown, this);");
    we.evaluateJavaScript("this.keydown();");
    //we.evaluateJavaScript("this.paste();");
    qDebug()<<"кнопка";
    this->NextOperation(vkweb, RunVideoVK2::Instance(vkweb));

    return true;
}


bool RunVideoVK2::RunOperation(CastomVKwebview *vkweb)
{
    disconnect(vkweb->page(), SIGNAL(loadFinished(bool)),vkweb, SLOT(onLoadFinished()));

    QEventLoop wait;
    QTimer::singleShot(500,&wait,SLOT(quit()));
    wait.exec();




    QWebElement we = vkweb->page()->mainFrame()->findFirstElement("div[class=\"video_row_info_name\"]");

    if (we.isNull()){ QMessageBox::critical(vkweb, "", "error",QMessageBox::Ok);

                          return false;}

    we = we.findFirst("a");
    if (we.isNull()){ QMessageBox::critical(vkweb, "", "error",QMessageBox::Ok);
                          return false;}
    qDebug()<<we.attribute("href");

//    QTimer::singleShot(5000,&wait,SLOT(quit()));
//    wait.exec();

    we.evaluateJavaScript("this.click();");


/*
QWebElementCollection *wec =new QWebElementCollection(vkweb->page()->mainFrame()->findAllElements("div[class=\"video_row_thumb\"]"));
    int i;
    if (wec->count()<1){ QMessageBox::critical(vkweb, "", "error",QMessageBox::Ok);
                          return false;}
    for (i=0; i<wec->count();i++){
        QWebElement we = wec->at(i);
        we = we.firstChild();
        if (we.toPlainText()==vkweb->tek_vf->GetTitle()){
            we.evaluateJavaScript("this.scrollIntoView();");
            we.evaluateJavaScript("this.click();");
            break;
        }
*/

    this->NextOperation(vkweb,GetFileNameVK::Instance(vkweb));
    vkweb->StartTimer();
//    QTimer::singleShot(1000,&wait,SLOT(quit()));
//    wait.exec();
    //vkweb->load(QUrl("https://vk.com"));
    return true;
}







bool GetFileNameVK3_1::RunOperation(CastomVKwebview *vkweb)
{
    QString s = QString("https://vk.com/videos-%1?q=%2&section=all").arg(vkweb->tek_vf->GetOwner_id().remove("-")).arg(vkweb->tek_vf->GetTitle());
    qDebug()<<s;
//    if (vkweb->url().toString().contains(s))
//        vkweb->page()->mainFrame()->evaluateJavaScript("window.history.back();");
    vkweb->load(QUrl(s));
    this->NextOperation(vkweb, RunVideoVK2::Instance(vkweb));

    return true;
}
