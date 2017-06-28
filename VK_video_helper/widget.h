#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <castomvkwebview.h>
#include <videofile.h>
#include <account.h>
#include <QList>
#include <vkmanager.h>


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();


public slots:
    void failDownUploadFile();
private slots:
    void onNewAccount(QStringList &sl);
    void onSearshVideoFinished(QStringList &sl);
    void onUploadFileFinished();
    void onDownloadFileFinished();

    void onSaveSetting();
    void on_pushButton_getVideoFileList_clicked();
    void on_pushButton_start_clicked();
    void toLog(QString s);

    void on_checkBox_type_downup_stateChanged(int arg1);

    void on_listWidget_accountList_clicked(const QModelIndex &index);

    void on_pushButton_newAccount_clicked();

    void downloadProgress(qint64 int1,qint64 int2);
    void uploadProgress(qint64 int1,qint64 int2);
private:
    void start();
    bool startdownload();
    bool startupload();

    void loadVideoFileList();
    void loadAccountList();
    void loadSetting();
    void saveVideoFile(VideoFile *vf);
    void saveAccount(Account *ac);
    void saveVideoFileList();
    Ui::Widget *ui;
    CastomVKwebview *vkweb;
    VKmanager *vkm;
    QList<VideoFile*> *vfL;
    QList<Account*> *acL;
    int index_videofile_in_list, index_account_in_list,index_error_file;
    bool status_work,type_downup;
};

#endif // WIDGET_H
