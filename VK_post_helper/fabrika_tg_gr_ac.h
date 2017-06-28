#ifndef FABRIKA_TG_GR_AC_H
#define FABRIKA_TG_GR_AC_H

#include <tag.h>
#include <group.h>
#include <account.h>
#include <post.h>

#include <listitems.h>
#define taglist  listitems<tag>
#define grouplist  listitems<group>
#define accountlist  listitems<account>
#define postlist  listitems<post>

class fabrika_tg_gr_ac
{
public:
    fabrika_tg_gr_ac();
    tag     *getNewTag(QString name,int id_BD, QString name_table);


    group   *getNewGroup(int id_DB,QString name_table,int id, QString name, QString screen_name = "",QString type_group="");
    account *getNewAccount(int id,QString account_token, QString first_name, QString last_name,int id_bd,QString table_name,int counterofpost = 0);
    post    *getNewPost(int id_BD, QString name_table,QString name_post, QString text_post,QString attach_post);

    group   *getCopy(group *g);
    account *getCopy(account *a);
    post    *getCopy(post *p);

    bool     remove(tag *t);
    bool     remove(group *g);
    bool     remove(account *a);
    bool     remove(post *p);
    bool     updatepost(post *p,QString name,QString text_post,QString attach_post);
    bool     updatetag(tag *t,QString tagname);


private:
taglist *tgl;
taglist *tal;
grouplist *grl;
accountlist *acl;
postlist *pl;

};

#endif // FABRIKA_TG_GR_AC_H
