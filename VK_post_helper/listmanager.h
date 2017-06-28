#ifndef LISTMANAGER_H
#define LISTMANAGER_H

#include <QObject>
#include <bdmanager.h>


class Listmanager : public QObject
{
    Q_OBJECT
public:
    explicit Listmanager(QObject *parent = 0);

    taglist     *getTagGroupList();
    taglist     *getTagAccountList();
    grouplist   *getGroupList();
    accountlist *getAccountList();
    postlist    *getPostList();
    postlist    *getQueuePostList();

    accountlist *getAccountforPost(post *p);
    grouplist   *getGroupforPost(post *p);
    grouplist   *getGroupforPostRem(post *p);
    post        *getCopyPost(post *p);
    accountlist *getCopyAccountList(accountlist *al);
    grouplist   *getCopyGroupList(grouplist *gl);

    QStringList  getNameTagGroupList();
    QStringList  getNameTagGroupList(taglist *tl);
    QStringList  getNameTagAccountList();
    QStringList  getNameTagAccountList(taglist *tl);

    QStringList  getNameGroupList();
    QStringList  getNameAccountList();
    QStringList  getNamePostList();


    int countTagGroup();
    int countTagAccount();
    int countGroup();
    int countAccount();
    int countPost();
    int countQueuePost();

    tag  *addTagGroup(QString tagname);
    tag  *addTagAccount(QString tagname);
    post *addPost(QString name_post,QString text_post, QString attach_post);
    bool  addTagto(tag *t,group *g);
    bool  addTagto(tag *t,account *a);
    bool  addPostTagtoAccount(tag *t,post *p);
    bool  addPostTagtoGroup(tag *t,post *p);
    bool  addPosttoQueue(post *p);
    bool  addSendPost(post *p,group *g, account *a,QString id_post_vk,bool b);
    bool  addAccount(QStringList sl);
    bool  addGroup(QStringList sl);


    bool  removetag(tag *t);
    bool  removetagfrom(tag *t,account *a);
    bool  removetagfrom(tag *t,group *g);
    bool  removeGroup(group *g);
    bool  removeAccount(account *a);
    bool  removePost(post *p);
    bool  removePostTagfromAccount(tag *t,post *p);
    bool  removePostTagfromGroup(tag *t,post *p);
    bool  removePostfromQueue(post *p);

    bool updatePost(post *p,QString name,QString text_post,QString attach_post);
    bool updateTagGroup(tag *t,QString tagname);
    bool updateTagAccount(tag *t,QString tagname);


    void setCurrentPost(post *p){ current_post = p;}
    void setCurrentGroup(group *g){ current_group = g;}
    void setCurrentAccount(account *a) {current_account = a;}
    void setCurrentTagGroup(tag *t){if (t->getNameTable()=="TagGroupTable") current_tag_group = t;}
    void setCurrentTagAccount(tag *t){if (t->getNameTable()=="TagAccountTable") current_tag_account = t;}

    void setCurrentQueuePost(post *p){
                  if (this->getQueuePostList()->iteminlist(p)) current_queuepost = p;}


    post    *getCurrentPost(){ return current_post;}
    group   *getCurrentGroup(){ return current_group;}
    account *getCurrentAccount() {return current_account;}
    tag     *getCurrentTagGroup(){return current_tag_group;}
    tag     *getCurrentTagAccount(){return current_tag_account;}
    post    *getCurrentQueuePost(){return current_queuepost;}


    int    CountSearshGroupList(){return countSearshGroupList;}
    void   setCountSearshGroupList(int countsearshgrouplist){ this->countSearshGroupList = countsearshgrouplist;}
    group *groupingrouplist(QStringList sl);
    int    getCountMaxSending(){return countmaxsending;}
private:
    BDManager    *bdm;
    postlist     *plist;
    postlist     *queueplist;
    grouplist    *glist;
    accountlist  *alist;
    taglist      *tglist;
    taglist      *talist;



    post *current_post = NULL;
    group *current_group = NULL;
    account *current_account = NULL;
    tag *current_tag_group = NULL;
    tag *current_tag_account = NULL;
    post *current_queuepost = NULL;

    int countSearshGroupList, countmaxsending;
signals:

public slots:

};

#endif // LISTMANAGER_H
