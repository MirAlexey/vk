#ifndef POST_H
#define POST_H

#include <tag.h>
#include <element_bd.h>
#include <listitems.h>
#define taglist  listitems<tag>

class fabrika_tg_gr_ac;

class post: public element_bd
{
public:

    QString GetTextPost(){return text_post;}
    QString GetAttachPost(){return attach_post.remove(" ");}
    QString GetNamePost(){return name;}

    bool operator==(post *right)
    {
        return this->getIdBd() == right->getIdBd();
    }
    bool operator==(post right)
    {
        return this->getIdBd() == right.getIdBd();
    }




    bool addtagforgroup(tag *t){t->upCountPost();return tagforgroup->additem(t);}
    bool removetagforgroup(tag *t){t->downCountPost();return tagforgroup->removeitem(t);}
    bool taginforgroup(tag *t){return tagforgroup->iteminlist(t);}
    bool addtagforaccount(tag *t){t->upCountPost();return tagforaccount->additem(t);}
    bool removetagforaccount(tag *t){t->downCountPost();return tagforaccount->removeitem(t);}
    bool taginforaccount(tag *t){return tagforaccount->iteminlist(t);}
    bool addtagforgroup(taglist *tg){
                tg->begin();
                for(int i =0; i<tg->countitem();i++) addtagforgroup(tg->nextitem());
                return true;
                }
    bool addtagforaccount(taglist *ta){
        ta->begin();
        for(int i =0; i<ta->countitem();i++) addtagforaccount(ta->nextitem());
        return true;
        }
    taglist *getTagforGroup(){ return tagforgroup;}
    taglist *getTagforAccount(){ return tagforaccount;}

    bool setTextPost(QString s){ text_post=s; return true;}
    bool setAttachPost(QString s){ attach_post=s;return true;}
    bool setNamePost(QString s){name = s; return true;}
    friend fabrika_tg_gr_ac;
private:

    post(int id_BD, QString name_table,QString name_post, QString text_post,QString attach_post);

QString name;
QString text_post;
QString attach_post;
taglist *tagforgroup;
taglist *tagforaccount;





// element_bd interface
public:
QString getName();
};

#endif // POST_H
