#ifndef CASTOMVKWEBVIEW_H
#define CASTOMVKWEBVIEW_H

#include <QUrl>
#include <QtWebKitWidgets/QWebPage>
#include <QtWebKitWidgets/QWebView>
#include <QtWebKit/QWebSettings>
#include <interceptoraccessmanager.h>
#include <QMessageBox>
#include <QWebElement>
#include <QWebFrame>
#include <QThread>
#include <QCursor>
#include <QMouseEvent>
#include <QApplication>
#include <QDateTime>
#include <account.h>
#include <videofile.h>
#include <QTimer>
#include <QEventLoop>
#include <QWebElementCollection>


#ifdef Q_OS_WIN32
    #define WINVER 0x0500
    #include <Windows.h>

#endif


class OperationVK;


class CastomVKwebview : public QWebView
{
    Q_OBJECT
public:
    explicit CastomVKwebview(QWidget *parent = 0);
    void LoadVideoFilefromVK(VideoFile *vf, Account *acc);
    //void LoadVideoFile(QString urlfile);
    void Reg_in_VK();
    QString GetCurrentUrlFile();
    QString GetCurrentFileName();
    void SetCurrentFileName();
    void SetCurrentDir(QString currentdir){this->currentdir = currentdir;}
    QString GetCurrentDir(){return currentdir;}
    VideoFile *tek_vf;
    Account *tek_acc;
    bool metod_download;
void StartTimer();
void StopTimer();
signals:
 void ScriptFinished();
 void VideoFileisDownLoad();
 void FailDownUpLoadFile();
 void toLog(QString);
 void DownloadProgress(qint64,qint64);
public slots:
 void onDownloadProgress(qint64 int1,qint64 int2);
 void onFailDownUpLoadFile();
 void onLoadFinished();
 void onFileLoadingFinished();
 void onReadyReadData();
 void onFoundFileName(QString s);

private:




friend class OperationVK;
void SetOperation(OperationVK *new_operationVK);
OperationVK *tek_operationVK;
InterceptorAccessManager *interceptor;

QString url_file, filename, currentdir;

bool type_saving_file;
QFile *file;
QNetworkReply * reply;
QNetworkAccessManager manager;

QTimer *timer;

};






class OperationVK : public QObject
{
    Q_OBJECT
public:
//    static OperationVK* Instance(QObject *parent = 0)
//    {
//        if (_instance)
//        {
//            _instance = new OperationVK(parent);
//        }
//        return _instance;
//    }
    virtual  bool  RunOperation(CastomVKwebview *vkweb){return true;}
signals:
    void SuccessOperation(bool);

public slots:

protected:
    explicit OperationVK(QObject *parent = 0):QObject(parent){}
    void NextOperation(CastomVKwebview *vkweb, OperationVK *next_operation)
    {
        vkweb->SetOperation(next_operation);
    }

private:
     //static OperationVK * _instance;
};
//OperationVK* OperationVK::_instance = 0;



class EnterLoginPass : public OperationVK
{
    Q_OBJECT
public:
    static EnterLoginPass* Instance(QObject *parent = 0)
    {
        if (_instance == 0){
            _instance = new EnterLoginPass(parent);
        }
      return _instance;
    }
    virtual bool RunOperation(CastomVKwebview *vkweb );
protected:
    explicit EnterLoginPass(QObject *parent = 0):OperationVK(parent){}
private:
    static EnterLoginPass* _instance;
};
//EnterLoginPass* EnterLoginPass::_instance = 0;




class EnterinVK : public OperationVK
{
    Q_OBJECT
public:
    static EnterinVK* Instance(QObject *parent = 0)
    {
        if (_instance == 0){
            _instance = new EnterinVK(parent);
        }
         return _instance;
    }

    virtual bool RunOperation(CastomVKwebview *vkweb);
    protected:
    explicit EnterinVK(QObject *parent = 0):OperationVK(parent){}
private:
    static EnterinVK* _instance;
};
//EnterinVK *EnterinVK::_instance = 0;



class GetFileNameVK : public OperationVK
{
    Q_OBJECT
public:
    static GetFileNameVK* Instance(QObject *parent = 0)
    {
        if (_instance == 0){
            _instance = new GetFileNameVK(parent);
        }
         return _instance;
    }
    virtual bool RunOperation(CastomVKwebview *vkweb);
    protected:
    explicit GetFileNameVK(QObject *parent = 0):OperationVK(parent){}
private:
    static GetFileNameVK* _instance;
};
//GetFileNameVK* GetFileNameVK::_instance = 0;



class NopOperationVK : public OperationVK
{
    Q_OBJECT
public:
    static NopOperationVK* Instance(QObject *parent = 0)
    {
        if (_instance == 0){
            _instance = new NopOperationVK(parent);
        }
         return _instance;
    }
    virtual bool RunOperation(CastomVKwebview *vkweb);
    protected:
    explicit NopOperationVK(QObject *parent = 0):OperationVK(parent){}
private:
    static NopOperationVK* _instance;
};
//NopOperationVK* NopOperationVK::_instance = 0;



class RunVideoVK : public OperationVK
{
    Q_OBJECT
public:
    static RunVideoVK* Instance(QObject *parent = 0)
    {
        if (_instance == 0){
            _instance = new RunVideoVK(parent);
        }
         return _instance;
    }
    virtual bool RunOperation(CastomVKwebview *vkweb);
    protected:
    explicit RunVideoVK(QObject *parent = 0):OperationVK(parent){}
private:
    static RunVideoVK* _instance;
};
//RunVideoVK* RunVideoVK::_instance = 0;

class GetFileNameVK2_1 : public OperationVK
{
    Q_OBJECT
public:
    static GetFileNameVK2_1* Instance(QObject *parent = 0)
    {
        if (_instance == 0){
            _instance = new GetFileNameVK2_1(parent);
        }
         return _instance;
    }
    virtual bool RunOperation(CastomVKwebview *vkweb);
    protected:
    explicit GetFileNameVK2_1(QObject *parent = 0):OperationVK(parent){}
private:
    static GetFileNameVK2_1* _instance;
};


class GetFileNameVK2_2 : public OperationVK
{
    Q_OBJECT
public:
    static GetFileNameVK2_2* Instance(QObject *parent = 0)
    {
        if (_instance == 0){
            _instance = new GetFileNameVK2_2(parent);
        }
         return _instance;
    }
    virtual bool RunOperation(CastomVKwebview *vkweb);
    protected:
    explicit GetFileNameVK2_2(QObject *parent = 0):OperationVK(parent){}
private:
    static GetFileNameVK2_2* _instance;
};


class GetFileNameVK2_3 : public OperationVK
{
    Q_OBJECT
public:
    static GetFileNameVK2_3* Instance(QObject *parent = 0)
    {
        if (_instance == 0){
            _instance = new GetFileNameVK2_3(parent);
        }
         return _instance;
    }
    virtual bool RunOperation(CastomVKwebview *vkweb);
    protected:
    explicit GetFileNameVK2_3(QObject *parent = 0):OperationVK(parent){}
private:
    static GetFileNameVK2_3* _instance;
};


class RunVideoVK2 : public OperationVK
{
    Q_OBJECT
public:
    static RunVideoVK2* Instance(QObject *parent = 0)
    {
        if (_instance == 0){
            _instance = new RunVideoVK2(parent);
        }
         return _instance;
    }
    virtual bool RunOperation(CastomVKwebview *vkweb);
    protected:
    explicit RunVideoVK2(QObject *parent = 0):OperationVK(parent){}
private:
    static RunVideoVK2* _instance;
};


class GetFileNameVK3_1 : public OperationVK
{
    Q_OBJECT
public:
    static GetFileNameVK3_1* Instance(QObject *parent = 0)
    {
        if (_instance == 0){
            _instance = new GetFileNameVK3_1(parent);
        }
         return _instance;
    }
    virtual bool RunOperation(CastomVKwebview *vkweb);
    protected:
    explicit GetFileNameVK3_1(QObject *parent = 0):OperationVK(parent){}
private:
    static GetFileNameVK3_1* _instance;
};






#endif // CASTOMVKWEBVIEW_H
