#include "widget.h"
#include "ui_widget.h"


//void CatchSIGSEGV(int sign)
//{
// qDebug()<< "Ошибка SEG" << sign;
//}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

//    signal(SIGSEGV, CatchSIGSEGV);
    //signal(SIGFPE, handler_sigfpe);

    ui->setupUi(this);

    vkweb = new CastomVKwebview(0);
    vkm = new VKmanager(this);

    vfL = new QList<VideoFile*>();

    acL = new QList<Account*>();
    connect(vkm,SIGNAL(receivedNewAccount(QStringList&)),this,SLOT(onNewAccount(QStringList&)));
    connect(vkm,SIGNAL(searshVideoFinished(QStringList&)),this,SLOT(onSearshVideoFinished(QStringList&)));
    connect(vkm,SIGNAL(uploadfilesuccess()),this,SLOT(onUploadFileFinished()));
    connect(vkweb,SIGNAL(VideoFileisDownLoad()),this,SLOT(onDownloadFileFinished()));
    connect(vkweb,SIGNAL(FailDownUpLoadFile()),this,SLOT(failDownUploadFile()));
    connect(vkm,SIGNAL(uploadfilefail()),this,SLOT(failDownUploadFile()));
    connect(ui->lineEdit_group_from,SIGNAL(editingFinished()),this,SLOT(onSaveSetting()));
    connect(ui->lineEdit_group_to,SIGNAL(editingFinished()),this,SLOT(onSaveSetting()));
    connect(ui->lineEdit_dirname,SIGNAL(editingFinished()),this,SLOT(onSaveSetting()));
    connect(vkm,SIGNAL(toLog(QString)),this,SLOT(toLog(QString)));
    connect(vkweb,SIGNAL(toLog(QString)),this,SLOT(toLog(QString)));
    connect(vkweb,SIGNAL(DownloadProgress(qint64,qint64)),this,SLOT(downloadProgress(qint64,qint64)));
    connect(vkm,SIGNAL(UploadProgress(qint64,qint64)),this,SLOT(uploadProgress(qint64,qint64)));

    //connect(vkweb->timer,SIGNAL(timeout()),this,SLOT()
    this->loadVideoFileList();
    this->loadAccountList();
    this->loadSetting();
    this->status_work = false;
   // vfL->append(new VideoFile("proba2.avi","proba2.avi"));
   // acL->append(new Account("ee645321beea393e10ae6500d27cb85bbdaec243f95d0772494210d1012b8ccda48400d84938df78b2eeb","Иван","Иванов",46327767,""));

  //vkm->queryForUploadVideoFile(vfL->at(0),acL->at(0),"97840321");
  //
   // vkm->queryGetListVideoFile("66748",acL->at(0));
    index_account_in_list = 0;
    index_videofile_in_list = 0;
    type_downup = false;
    index_error_file =-1;


}

Widget::~Widget()
{
    delete ui;

}

void Widget::onNewAccount(QStringList &sl)
{
    Account *acc = new Account(sl.at(0),sl.at(1),sl.at(2),sl.at(3).toInt());
    acL->append(acc);
    ui->listWidget_accountList->addItem(acc->getName());
    this->saveAccount(acc);
}

void Widget::onSearshVideoFinished(QStringList &sl)
{
    VideoFile *vf;
    int k=9;
    for (int i = 0 ; i< sl.count()/k;i++){
        bool b = true;
        vf = new VideoFile(sl.at(i*k),sl.at(i*k+1),"",sl.at(i*k+2),sl.at(i*k+3),sl.at(i*k+4),sl.at(i*k+5),sl.at(i*k+6),"",sl.at(i*k+7)=="true"?true:false,sl.at(i*k+8)=="true"?true:false);
        for(int i=0;i<vfL->count();i++) if (*vf==vfL->at(i)) b=false;

        if (b)
            if (vf->GetLinkFile().contains(vf->GetVideo_id())){
                vfL->append(vf);
                ui->listWidget_videofileList->addItem(vf->GetNameFile());
                ui->label_kol_video->setText(QString::number(vfL->count()));
                this->saveVideoFile(vf);
            }
    }
}

void Widget::onUploadFileFinished()
{
    vfL->at(index_videofile_in_list)->SetStatusUpload(true);
    qDebug()<< "удаление";
    if (vfL->at(index_videofile_in_list)->GetContent()!=NULL) delete vfL->at(index_videofile_in_list)->GetContent();
    vfL->at(index_videofile_in_list)->SetContent(NULL);

    this->saveVideoFileList();
    qDebug() << "Финиш выгрузки";
    ui->plainTextEdit_log->appendPlainText("Финиш выгрузки");
    if (status_work) {
        if ((++index_videofile_in_list) >= vfL->count()){
            this->start();
            return;
        }
        if (type_downup) if(this->startupload()) return;
        if (this->startdownload()) return;
        this->start();
    }
}

void Widget::onDownloadFileFinished()
{
    vfL->at(index_videofile_in_list)->SetStatusDownload(true);
    vkweb->hide();
    vkweb->metod_download=true;
    this->saveVideoFileList();
    qDebug() << "Финиш загрузки";
    ui->plainTextEdit_log->appendPlainText("Финиш загрузки");
    if (status_work){
        if (!type_downup) if (this->startupload()) return;
        if ((++index_videofile_in_list) < vfL->count()) if (this->startdownload()) return;
        this->start();
    }
}



void Widget::loadVideoFileList()
{
       QFile file("videofile.txt");
       file.open(QIODevice::ReadOnly|QIODevice::Text);
       //qDebug() << file.isOpen();
       QTextStream in(&file);
       QString s0,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11;
       while (!in.atEnd()){
           while (s0!="-----//-----" && !in.atEnd())
           {
               s0 = in.readLine();
           }
           if (in.atEnd()) return;
           s1 = in.readLine();
           s1 = s1.right(s1.length()-s1.indexOf(":")-1);
           s2 = in.readLine();
           s2 = s2.right(s2.length()-s2.indexOf(":")-1);
           s3 = in.readLine();
           s3 = s3.right(s3.length()-s3.indexOf(":")-1);
           s4 = in.readLine();
           s4 = s4.right(s4.length()-s4.indexOf(":")-1);
           s5 = in.readLine();
           s5 = s5.right(s5.length()-s5.indexOf(":")-1);
           s6 = in.readLine();
           s6 = s6.right(s6.length()-s6.indexOf(":")-1);
           s7 = in.readLine();
           s7 = s7.right(s7.length()-s7.indexOf(":")-1);
           s8 = in.readLine();
           s8 = s8.right(s8.length()-s8.indexOf(":")-1);
           s9 = in.readLine();
           s9 = s9.right(s9.length()-s9.indexOf(":")-1);
           s10 = in.readLine();
           s10 = s10.right(s10.length()-s10.indexOf(":")-1);
           s11 = in.readLine();
           s11 = s11.right(s11.length()-s11.indexOf(":")-1);
           s0="";
           vfL->append(new VideoFile(s1,s2,s10,s3,s4,s5,s6,s7,s11,(s8=="true"?true:false),(s9=="true"?true:false)));
           ui->listWidget_videofileList->addItem(s1);
           ui->label_kol_video->setText(QString::number(vfL->count()));
       }


}

void Widget::loadAccountList()
{
    QFile file("account.txt");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    //qDebug() << file.isOpen();
    QTextStream in(&file);
    QString s0,s1,s2,s3,s4,s5,s6;
    while (!in.atEnd()){
        while (s0!="-----//-----" && !in.atEnd())
        {
            s0 = in.readLine();
        }
        if (in.atEnd()) return;
        s1 = in.readLine();
        s1=s1.right(s1.length()-s1.indexOf(":")-1);
        s2 = in.readLine();
        s2=s2.right(s2.length()-s2.indexOf(":")-1);
        s3 = in.readLine();
        s3=s3.right(s3.length()-s3.indexOf(":")-1);
        s4 = in.readLine();
        s4=s4.right(s4.length()-s4.indexOf(":")-1);
        s5 = in.readLine();
        s5=s5.right(s5.length()-s5.indexOf(":")-1);
        s6 = in.readLine();
        s6=s6.right(s6.length()-s6.indexOf(":")-1);
        s0="";
        acL->append(new Account(s1,s2,s3,s4.toInt(),s5,s6));
        ui->listWidget_accountList->addItem(s2+" "+s3);
    }





}

void Widget::loadSetting()
{
    QFile file("setting_VKvh.txt");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    //qDebug() << file.isOpen();
    if (!file.isOpen()) {
        qDebug()<< "Ошибка загрузки настроек!";
        return;
    }
    QString s0, s1;
    QTextStream in(&file);
    while (s0!="-----//-----" && !in.atEnd())
    {
        s0 = in.readLine();
    }
    if (in.atEnd()){
        qDebug()<< "Пустой файл настроек!";
        return;
    }
    s1 = in.readLine();
    s1=s1.right(s1.length()-s1.indexOf(":")-1);
    ui->lineEdit_group_from->setText(s1);
    s1 = in.readLine();
    s1=s1.right(s1.length()-s1.indexOf(":")-1);
    ui->lineEdit_group_to->setText(s1);
    s1 = in.readLine();
    s1=s1.right(s1.length()-s1.indexOf(":")-1);
    ui->lineEdit_dirname->setText(s1);
}

void Widget::saveVideoFile(VideoFile *vf)
{
    QFile file("videofile.txt");
    file.open(QIODevice::Append|QIODevice::Text);
    //qDebug() << file.isOpen();
    QTextStream out(&file);
    out << "-----//-----" << endl << "File name:"<<  vf->GetNameFile() << endl << "Link file:" << vf->GetLinkFile()<< endl<< "Description:"<<vf->GetDescriptionFile().remove("\n").remove("\r")<< endl << "Access_key:" <<vf->GetAccess_key()<< endl <<"Title:" << vf->GetTitle()<< endl << "Owner_id:"<<vf->GetOwner_id()<< endl<<"video_id:"  << vf->GetVideo_id()<< endl<< "upload status:"<< (vf->GetStatusUpload()==true?"true":"false")<<endl<<"download status:"<< (vf->GetStatusDownload()==true?"true":"false")<<endl<< "Name file on disk:" << vf->GetNameFileOnDisk()<< endl<<"new_video_id:"  << vf->GetNewVideo_id()<< endl;
    file.close();
}

void Widget::saveAccount(Account *ac)
{
    QFile file("account.txt");
    file.open(QIODevice::Append|QIODevice::Text);
    //qDebug() << file.isOpen();
    QTextStream out(&file);
    out << "-----//-----" << endl <<"Access token:"<< ac->getAccountToken() << endl <<"First name:"<< ac->getFirstName()<< endl <<"Last name:"<< ac->getLastName()<< endl << "id:"<<QString::number(ac->getID())<< endl <<"email:"<<ac->getPass() << endl <<"pass:"<<ac->getPass()<< endl;
    file.close();
}

void Widget::saveVideoFileList()
{
    QFile file("videofile.txt");
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    //qDebug() << file.isOpen();
    if (!file.isOpen()) {
        qDebug() << "Ошибка сохранения videofile.txt";
        return;
    }
    QTextStream out(&file);
    VideoFile *vf;
    for (int i=0 ; i<vfL->count();i++){
        vf=vfL->at(i);
    out << "-----//-----" << endl << "File name:"<<  vf->GetNameFile() << endl << "Link file:" << vf->GetLinkFile()<< endl << "Description:"<<vf->GetDescriptionFile().remove("\n").remove("\r")<< endl << "Access_key:" <<vf->GetAccess_key()<< endl <<"Title:" << vf->GetTitle()<< endl << "Owner_id:"<<vf->GetOwner_id()<< endl<<"video_id:"  << vf->GetVideo_id()<< endl<< "upload status:"<< (vf->GetStatusUpload()==true?"true":"false")<<endl<<"download status:"<< (vf->GetStatusDownload()==true?"true":"false")<<endl<< "Name file on disk:" << vf->GetNameFileOnDisk()<< endl<<"new_video_id:"  << vf->GetNewVideo_id()<< endl;
    }
    file.close();
}

//https://api.vk.com/method/users.get??user_id=46327767&v=5.34&access_token=775192af9b2d076ac7d09de3f89a6feb7afbaed742a03d6ac75d073e838b9ab7622d7ad02bcfe424d38d5




void Widget::on_pushButton_getVideoFileList_clicked()
{
    vkm->queryGetListVideoFile(ui->lineEdit_group_from->text(),acL->at(index_account_in_list));
}

void Widget::on_pushButton_start_clicked()
{
    vkweb->StopTimer();
    if (!status_work){
        ui->pushButton_start->setText("Остановка перекачки");
        status_work = true;
    }
    else {
        ui->pushButton_start->setText("Запуск перекачки");
        status_work = false;
        return;
    }
    vkweb->SetCurrentDir(ui->lineEdit_dirname->text());
    this->start();
}

void Widget::toLog(QString s)
{
    ui->plainTextEdit_log->appendPlainText(s);
}

void Widget::start()
{
    if (!vfL->isEmpty())
    {
        int i=0;
        while (i<vfL->count())
        {
            index_videofile_in_list = i;
            if (!type_downup)
            {
                if (this->startupload()) return;
//                if (!vfL->at(index_videofile_in_list)->GetStatusUpload())
//                    if (vfL->at(index_videofile_in_list)->GetStatusDownload()){
//                        vfL->at(index_videofile_in_list)->SetDescriptionFile(ui->textEdit_new_description->toPlainText());
//                        qDebug() << "Старт выгрузки";
//                        ui->plainTextEdit_log->appendPlainText("Старт выгрузки");
//                        ui->plainTextEdit_log->appendPlainText(vfL->at(index_videofile_in_list)->GetNameFile()+" : "+vfL->at(index_videofile_in_list)->GetLinkFile());
//                        vkm->queryForUploadVideoFile(vfL->at(index_videofile_in_list),acL->at(index_account_in_list),ui->lineEdit_group_to->text());
//                        return;
//                    }
            }
            if (this->startdownload()) return;

//            if (!vfL->at(i)->GetStatusDownload())
//            {
//                vkweb->show();
//                vkweb->raise();
//                vkweb->activateWindow();
//                qDebug() << "Старт загрузки";
//                ui->plainTextEdit_log->appendPlainText("Старт загрузки");
//                ui->plainTextEdit_log->appendPlainText(vfL->at(index_videofile_in_list)->GetNameFile()+" : "+vfL->at(index_videofile_in_list)->GetLinkFile());
//                vkweb->LoadVideoFilefromVK(vfL->at(index_videofile_in_list),acL->at(index_account_in_list));
//                return;
//            }
            i++;
        }
        i=0;
        while (i<vfL->count())
        {
            index_videofile_in_list = i;
            if (this->startupload()) return;
//            if (vfL->at(index_videofile_in_list)->GetStatusDownload())
//            {
//                if(!vfL->at(index_videofile_in_list)->GetStatusUpload())
//                {
//                vfL->at(index_videofile_in_list)->SetDescriptionFile(ui->textEdit_new_description->toPlainText());
//                qDebug() << "Старт выгрузки";
//                ui->plainTextEdit_log->appendPlainText("Старт выгрузки");
//                ui->plainTextEdit_log->appendPlainText(vfL->at(index_videofile_in_list)->GetNameFile()+" : "+vfL->at(index_videofile_in_list)->GetLinkFile());
//                vkm->queryForUploadVideoFile(vfL->at(index_videofile_in_list),acL->at(index_account_in_list),ui->lineEdit_group_to->text());
//                return;
//                }
//            }
            i++;
        }
    }
    vkweb->StopTimer();
    QMessageBox::information(this,"Информация","Перекачка завершена",QMessageBox::Ok);
    return;
}

bool Widget::startdownload()
{
    if (!vfL->at(index_videofile_in_list)->GetStatusDownload())
    {
        vkweb->show();
        vkweb->raise();
        vkweb->activateWindow();
        qDebug() << "Старт загрузки";
        ui->plainTextEdit_log->appendPlainText("Старт загрузки");
        ui->plainTextEdit_log->appendPlainText(vfL->at(index_videofile_in_list)->GetNameFile()+" : "+vfL->at(index_videofile_in_list)->GetLinkFile());
        vkweb->LoadVideoFilefromVK(vfL->at(index_videofile_in_list),acL->at(index_account_in_list));
        return true;
    }
    return false;
}

bool Widget::startupload()
{
    if (vfL->at(index_videofile_in_list)->GetStatusDownload())
    {
        if(!vfL->at(index_videofile_in_list)->GetStatusUpload())
        {
        vfL->at(index_videofile_in_list)->SetDescriptionFile(ui->textEdit_new_description->toPlainText());
        qDebug() << "Старт выгрузки";
        ui->plainTextEdit_log->appendPlainText("Старт выгрузки");
        ui->plainTextEdit_log->appendPlainText(vfL->at(index_videofile_in_list)->GetNameFile()+" : "+vfL->at(index_videofile_in_list)->GetLinkFile());
        vkm->queryForUploadVideoFile(vfL->at(index_videofile_in_list),acL->at(index_account_in_list),ui->lineEdit_group_to->text());
        return true;
        }
    }
    return false;
}

void Widget::on_checkBox_type_downup_stateChanged(int arg1)
{
    type_downup = ui->checkBox_type_downup->isChecked();
}

void Widget::on_listWidget_accountList_clicked(const QModelIndex &index)
{
   if (index.isValid()) index_account_in_list=index.row();
}

void Widget::on_pushButton_newAccount_clicked()
{
    vkm->queryNewAccount();
}

void Widget::downloadProgress(qint64 int1, qint64 int2)
{
    ui->progressBar->setInvertedAppearance(false);
    ui->progressBar->setMaximum(int2);
    ui->progressBar->setValue(int1);
}

void Widget::uploadProgress(qint64 int1, qint64 int2)
{
    ui->progressBar->setInvertedAppearance(true);
    ui->progressBar->setMaximum(int2);
    ui->progressBar->setValue(int2-int1);
}

void Widget::failDownUploadFile()
{
    if (vfL->at(index_videofile_in_list)->GetContent() != NULL)
    {
        qDebug()<< "удаление";
        delete vfL->at(index_videofile_in_list)->GetContent();
        vfL->at(index_videofile_in_list)->SetContent(NULL);
    }

    vfL->at(index_videofile_in_list)->SetStatusDownload(false);
   if  (index_error_file == index_videofile_in_list) {
       vfL->removeAt(index_videofile_in_list);
       index_error_file = -1;
       this->saveVideoFileList();
       }
   else {index_error_file = index_videofile_in_list;

         vkweb->metod_download=false;}

   this->start();
}

void Widget::onSaveSetting()
{
    QFile file("setting_VKvh.txt");
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    //qDebug() << file.isOpen();
    if (!file.isOpen()) {
        qDebug()<< "Ошибка сохранения настроек!";
        return;
    }
    QTextStream out(&file);
    out << "-----//-----" << endl <<"Group out:"<< ui->lineEdit_group_from->text() << endl <<"Group in:"<< ui->lineEdit_group_to->text()<< endl <<"Path for save:"<< ui->lineEdit_dirname->text();
    file.close();
}
