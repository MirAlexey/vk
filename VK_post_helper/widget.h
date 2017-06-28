#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <listmanager.h>
#include <qlineeditfortag.h>
#include <checkboxtagforgroup.h>
#include <vkmanager.h>
#include <QDesktopServices>
#include <QTextBrowser>
#include <myitemmodel.h>
#include <QDebug>
#include <QScrollBar>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <mymodel2.h>
#include <myproxymodel.h>
#include <myfiltermodel.h>
#include <QHeaderView>



namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void setTagforGroup(int row, int col,int stat);
    void setTagforAccount(int row, int col, int stat);
    void setPostTagforGroup(int row, int col,int stat);
    void setPostTagforAccount(int row, int col, int stat);


signals:
    void SentPostFinishw();
    void putActiveSendingPost(bool);
    void StringtoLog(QString&,bool,QColor);

private slots:

    void mySlotGroupTagH(int numCol);
    void mySlotGroupTagV(int numRow);
    void mySlotAccountTagH(int numCol);
    void mySlotAccountTagV(int numRow);

    void on_pushButton_2_newtag_clicked();
    void on_pushButton_3_deltag_clicked();
    void on_pushButton_7_delgroup_clicked();
    void on_pushButton_10_delaccount_clicked();
    void on_pushButton_18_addpost_clicked();
    void on_pushButton_19_delpost_clicked();
    void on_pushButton_2_updatepost_clicked();
    void on_pushButton_12_posttoQueue_clicked();
    void on_pushButton_2_removepostfromqueue_clicked();
    void on_pushButton_addnewaccount_clicked();
    void on_pushButton_addgroup_clicked();
    void on_pushButton_searchgroup_clicked();
    void on_pushButton_4_addnewgroup_clicked();
    void on_pushButton_15_startsendingpost_clicked();
    void on_pushButton_17_stopsendingpost_clicked();
    void on_pushBatton_opengroupinbr_clicked();
    void on_pushButton_13_testpost_clicked();
    void on_pushButton_newtagaccount_clicked();
    void on_pushButton_deltagaccount_clicked();
    void on_pushButton_addnewgroup_alltag_clicked();
    void on_pushButton_14_testallpost_clicked();
    void on_pushButton_6_addgroupfromfile_clicked();



//    void on_tableWidget_taglist_clicked                  (const QModelIndex &index);
//    void on_tableWidget_grouptag_clicked                 (const QModelIndex &index);
//    void on_tableWidget_accounttag_clicked               (const QModelIndex &index);
//    void on_tableWidget_post_clicked                     (const QModelIndex &index);
//    void on_tableWidget_tagpostforgroup_clicked          (const QModelIndex &index);
//    void on_tableWidget_tagpostforaccount_clicked        (const QModelIndex &index);
//    void on_tableWidget_queuepost_clicked                (const QModelIndex &index);

    void on_tableWidget_resultSearshGroup_clicked        (const QModelIndex &index);
    void on_tableWidget_resultSearshGroup_doubleClicked  (const QModelIndex &index);
    void on_tableWidget_tagforsearshgroup_clicked        (const QModelIndex &index);
//    void reloadgroupslot(int index);
    void on_tableView_2_grouptag_clicked(const QModelIndex &index);
    void on_tableView_3_accounttag_clicked(const QModelIndex &index);
    void on_tableView_8_taggroupfotpost_clicked(const QModelIndex &index);
    void on_tableView_9_tagaccountforpost_clicked(const QModelIndex &index);
    void on_tableView_4_taglistforgroup_clicked(const QModelIndex &index);
    void on_tableView_5_taglistforaccount_clicked(const QModelIndex &index);
    void on_tableView_6_post_clicked(const QModelIndex &index);
    void on_tableView_7_queuepost_clicked(const QModelIndex &index);
    void on_tableView_12_taggroupfotqueuepost_clicked(const QModelIndex &index);
    void on_tableView_13_tagaccountforqueuepost_clicked(const QModelIndex &index);



    void on_pushButton_updatetaggroupname_clicked();

    void on_pushButton_updatetagaccountname_clicked();

public slots:
    void newAccount                    (QStringList &sl);
    void newGroup                      (QStringList &sl);
    void newSearshGroupResult          (QStringList &sl, int count_all_items, int max_item);
    void newSentPost                   (post* p,group* g,account* a,QString &id_post_on_wall,bool b);
    void startSendNextPost();
    void toLog                         (QString &s, bool b, QColor color);

private:
//    void reloadtag();
//    void reloadgroup();
//    void reloadaccount();
//    void reloadpost();
//    void reloadPostTagforGroup         (post *p);
//    void reloadPostTagforAccount       (post *p);
//    void reloadPostTag();
//    void reloadQueuePost();
//    void reloadQueuePostTagforGroup    (post *p);
//    void reloadQueuePostTagforAccount  (post *p);
//    void reloadQueuePostTag();
    void pushPosttoSendQueue           (int col,int row);

    Ui::Widget *ui;
    Listmanager *lm;
    VKmanager  *vkm;
    int count_queue, max_items_in_searshgrouplist ;
    bool activequeue;
    MyItemModel *myitemmodel;
    MyItemModel *myitemmodel_foraccounttag;
    MyModel2 *mymodel_all;
    MyProxyModelGT *myproxymodel1;
    MyProxyModelGT *myproxymodel2;
    MyProxyModelGT *myproxymodel3;
    MyProxyModelGT *myproxymodel4;
    MyProxyModelGT *myproxymodel5;
    MyProxyModelGT *myproxymodel6;
    MyProxyModelGT *myproxymodel7;
    MyProxyModelGT *myproxymodel8;
    MyProxyModelGT *myproxymodel9;
    MyProxyModelGT *myproxymodel10;
    MyProxyModelGT *myproxymodel11;
    MyProxyModelGT *myproxymodel12;

    myfiltermodel   *myfiltermodel1;
    myfiltermodel   *myfiltermodel2;

    int maxsending,errorsending, successsending;

    QFile *log_file;

   // int row_indexTableQueuePost, col_indexTableQueuePost;

};

#endif // WIDGET_H
