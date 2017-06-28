#ifndef VIDEOFILE_H
#define VIDEOFILE_H

#include <QObject>
#include <QDebug>
#include <QByteArray>

class VideoFile : public QObject
{
    Q_OBJECT

public:
    explicit VideoFile(QString name_file, QString link_file, QString namefile_on_disk = "", QString  description_file = "",QString access_key ="",QString title="",QString owner_id="",QString video_id="",QString new_video_id="",bool status_upload = false,bool status_download = false ,QObject *parent = 0);

    QString GetNameFile(){return namefile;}
    QString GetLinkFile(){return linkfile;}
    QString GetNameFileOnDisk(){return namefile_on_disk;}
    QString GetDescriptionFile() {return descriptionfile;}
    QString GetAccess_key(){return access_key;}
    QString GetTitle(){return title;}
    QString GetOwner_id() {return owner_id;}
    QString GetVideo_id() {return video_id;}
    QString GetNewVideo_id() {return new_video_id;}
    bool    GetStatusUpload(){return status_upload;}
    bool    GetStatusDownload(){return status_download;}
    QByteArray* GetContent(){return content;}
    void SetAccess_key(QString access_key){this->access_key=access_key;}
    void SetTitle(QString title){this->title=title;}
    void SetOwner_id(QString owner_id) {this->owner_id=owner_id;}
    void SetVideo_id(QString video_id) {this->video_id=video_id;}
    void SetNewVideo_id(QString new_video_id) {this->new_video_id=new_video_id;}
    void SetNameFile(QString namefile){this->namefile=namefile;}
    void SetLinkFile(QString linkfile){this->linkfile=linkfile;}
    void SetNameFileOnDisk(QString namefile_on_disk){this->namefile_on_disk=namefile_on_disk;}
    void SetDescriptionFile(QString descriptionfile) {this->descriptionfile=descriptionfile;}
    void SetStatusUpload(bool b){status_upload = b ;}
    void SetStatusDownload(bool b){status_download = b;}
    void SetContent(QByteArray *content){this->content = content;}

    bool operator==(VideoFile *right);
    bool operator==(VideoFile right);



private:
    QString namefile, linkfile, descriptionfile, access_key,title,owner_id,video_id, new_video_id,namefile_on_disk;
    bool status_upload,status_download;
    QByteArray *content;
signals:

public slots:

};

#endif // VIDEOFILE_H
