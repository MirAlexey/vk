#include "videofile.h"




VideoFile::VideoFile(QString name_file, QString link_file, QString namefile_on_disk ,QString description_file,QString access_key,QString title,QString owner_id,QString video_id,QString new_video_id, bool status_upload, bool status_download,QObject *parent):
    QObject(parent)
{
    namefile=  name_file;
    linkfile = link_file;
    descriptionfile = description_file;
    this->access_key =access_key;
    this->title = title;
    this->owner_id = owner_id;
    this->video_id = video_id;
    this->status_upload = status_upload;
    this->status_download = status_download;
    content = NULL;
   this->namefile_on_disk = namefile_on_disk;
    this->new_video_id = new_video_id;
}
bool VideoFile::operator==(VideoFile *right)
{
    //qDebug()<< "vf == *";
    return this->video_id==right->video_id;
}

bool VideoFile::operator==(VideoFile right)
{
   // qDebug()<< "vf == ";
    return this->video_id==right.video_id;
}
