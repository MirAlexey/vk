#ifndef BDMANAGER_H
#define BDMANAGER_H

#include <QObject>
#include <conector.h>
#include <tag.h>
#include <account.h>
#include <group.h>
#include <post.h>
#include <QDebug>
#include <QtSql/QtSql>
#include <fabrika_tg_gr_ac.h>
#include <QMessageBox>

#define str_rzr "---------------str-rzr-------------"

#include <listitems.h>
#define taglist  listitems<tag>
#define grouplist  listitems<group>
#define accountlist  listitems<account>
#define postlist  listitems<post>



class BDManager : public QObject
{
    Q_OBJECT
public:
    explicit BDManager(QObject *parent = 0);
    bool           openBD();

    taglist       *getTagGroupList();
    taglist       *getTagAccountList();
    grouplist     *getGroupList();
    accountlist   *getAccountList();
    postlist      *getPostList();
    taglist       *getTagForGroup(group *g);
    taglist       *getTagForAccount(account *a);
    grouplist     *getGroupForPost(post *p);
    accountlist   *getAccountForPost(post *p);
    taglist       *getPostTagforGroup(post *p);
    taglist       *getPostTagforAccount(post *p);
    postlist      *getPostinQueue();
    grouplist     *getGroupRemforPost(post *p);

    grouplist     *getCopyGroupList(grouplist *gl);
    accountlist   *getCopyAccountList(accountlist *al);
    postlist      *getCopyPostList(postlist *pl);

    group         *addgroup(int id_VK,QString name, QString screen_name ="",QString type_group = "");
    account       *addaccount(int id_VK,QString account_token, QString first_name, QString last_name);
    post          *addpost(QString name_post, QString text_post,QString attach_post);
    tag           *addtaggroup(QString tagname);
    tag           *addtagaccount(QString tagname);
    bool           addtag(group *g,tag *t);
    bool           addtag(account *a,tag *t);
    bool           addtag(group *g,taglist *t);
    bool           addtag(account *a,taglist *t);
    bool           addTagtoPostGroup(post *p, tag *t);
    bool           addTagtoPostAccount(post *p, tag *t);
    bool           addPosttoQueue(post *p);
    bool           addSendPost(post *p,group *g, account *a, QString id_post_VK);

    bool           removetag(tag *t);
    bool           removetag(group *g, tag *t);
    bool           removetag(account *a, tag *t);
    bool           removeposttagforgroup(post *p, tag *t);
    bool           removeposttagforaccount(post *p,tag *t);
    bool           removegroup(group *g);
    bool           removeaccount(account *a);
    bool           removepost(post *p);
    bool           removePostfromQueue(post *p);

    bool           updatepost(post *p,QString name,QString text_post,QString attach_post);
    bool           updatetag(tag *t, QString tagname);


    //    bool addgroup(post *p,group *g);
    //    bool addgroup(post *p,grouplist *g);
    //    bool addaccount(post *p,account *a);
    //    bool addaccount(post *p,accountlist *a);
private:
    fabrika_tg_gr_ac *fabrika;
    Conector         *con;


signals:

public slots:

};

#endif // BDMANAGER_H
