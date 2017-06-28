#ifndef ACCOUNT_H
#define ACCOUNT_H


#include <element_bd.h>
#include <tag.h>

#include <listitems.h>
#define taglist  listitems<tag>

class fabrika_tg_gr_ac;

class account : public element_bd
{

public:

    int getID(){return id;}
    QString getFirstName(){return first_name;}
    QString getLastName(){return last_name;}
    QString getAccountToken(){ return account_token;}
    int     getCountPost(){return counterofpost;}
    int     getMaxCountPost(){ return maxcontpost;}
    bool isready(){return counterofpost<maxcontpost;}
    void upcounter(){counterofpost++;}
    bool operator==(account *right);
    bool operator==(account right);
    bool addtag(tag *t){
        t->upCountItem();
        return tl->additem(t);
    }
    bool removetag(tag *t){t->downCountItem();return tl->removeitem(t);}
    bool tagin(tag *t){return tl->iteminlist(t);}
    bool addtag(taglist *t)
    {
        t->begin();
        for(int i =0; i<t->countitem();i++) addtag(t->nextitem());
        return true;
    }

    friend fabrika_tg_gr_ac;


private:
    explicit account(int id,QString account_token, QString first_name, QString last_name,int id_bd,QString table_name, int counterofpost = 0): element_bd(id_bd,table_name)
    {this->id=id;
     this->account_token = account_token;
     this->first_name=first_name;
     this->last_name=last_name;
     maxcontpost = 100;
     this->counterofpost = counterofpost;
     tl = new taglist();
    }




   int id;
   QString first_name;
   QString last_name;
   QString account_token;
   int counterofpost;
   int maxcontpost;
   taglist *tl;




   // element_bd interface
public:
   QString getName();
};

#endif // ACCOUNT_H
