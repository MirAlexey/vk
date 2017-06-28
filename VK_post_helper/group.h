#ifndef GROUP_H
#define GROUP_H



#include <tag.h>
#include <QString>


#include <listitems.h>
#define taglist  listitems<tag>


class fabrika_tg_gr_ac;



class group : public element_bd
{

public:

    int getID(){return id;}
    QString getName(){return name;}
    QString getScreenName(){return screen_name;}
    QString getTypeGroup(){return type_group;}
    bool issend(){return send;}
    void setsend(bool send){this->send = send;}
    bool addtag(tag *t){ t->upCountItem(); return tl->additem(t);}
    bool addtag(taglist *tlt)
    {
        tlt->begin();
        for(int i =0; i<tlt->countitem();i++) addtag(tlt->nextitem());
        return true;
    }
    bool removetag(tag *t){t->downCountItem();return tl->removeitem(t);}
    bool tagin(tag *t){return tl->iteminlist(t);}

    bool operator==(group *right);
    bool operator==(group right);
    friend fabrika_tg_gr_ac;
private:
    explicit group(int id_DB,QString name_table,int id, QString name, QString screen_name = "",QString type_group=""): element_bd(id_DB,name_table)
    {
        this->id = id;
        this->name = name;
        this->screen_name=screen_name;
        this->type_group =type_group;
        tl = new taglist();
    }
    int id;
    QString name;
    QString screen_name;
    QString type_group;
    taglist *tl;
    bool send;
};

typedef group groupp;

#endif // GROUP_H
