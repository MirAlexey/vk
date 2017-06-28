#include "fabrika_tg_gr_ac.h"

fabrika_tg_gr_ac::fabrika_tg_gr_ac()
{
   tgl = new taglist();
   tal = new taglist();
   grl = new grouplist();
   acl = new accountlist();
   pl = new postlist();
}

tag *fabrika_tg_gr_ac::getNewTag(QString name, int id_BD, QString name_table)
{
   if (name_table == "TagAccountTable")
   {tal->begin();
     for (int i = 0; i< tal->countitem();i++){
          tag *t = tal->nextitem();
          if (name == t->GetNameTag()) return t;

     }
   tag *t=new tag(name,id_BD,name_table);
   tal->additem(t);
   return t;
   }
   tgl->begin();
        for (int i = 0; i< tgl->countitem();i++){
             tag *t = tgl->nextitem();
             if (name == t->GetNameTag()) return t;

        }
      tag *t=new tag(name,id_BD,name_table);
      tgl->additem(t);
      return t;
}



group *fabrika_tg_gr_ac::getNewGroup(int id_DB, QString name_table, int id, QString name, QString screen_name, QString type_group)
{
     grl->begin();
            for (int i = 0; i< grl->countitem();i++){
            group *g = grl->nextitem();
            if (id == g->getID()) return g;
        }



    group *g = new group(id_DB, name_table, id, name, screen_name, type_group);
    grl->additem(g);
    return g;
}

account *fabrika_tg_gr_ac::getNewAccount(int id, QString account_token, QString first_name, QString last_name, int id_bd, QString table_name, int counterofpost)
{
    acl->begin();
        for (int i = 0; i< acl->countitem();i++){
            account *a = acl->nextitem();
            if (id == a->getID()) return a;
        }

    account *a = new account(id,account_token, first_name, last_name, id_bd, table_name, counterofpost);
    acl->additem(a);
    return a;
}

post *fabrika_tg_gr_ac::getNewPost(int id_BD, QString name_table, QString name_post, QString text_post, QString attach_post)
{
    if (pl->countitem()>0){pl->begin();
        for (int i = 0; i< pl->countitem();i++){
            post *p = pl->nextitem();
            if ((name_post == p->GetNamePost())&&(text_post == p->GetTextPost())&&(attach_post == p->GetAttachPost())) return p;
        }
    }

    post *p = new post(id_BD, name_table, name_post, text_post, attach_post);
    pl->additem(p);
    return p;
}

group *fabrika_tg_gr_ac::getCopy(group *g)
{
    return new group(g->getIdBd(),g->getNameTable(),g->getID(),g->getName(),g->getScreenName(),g->getScreenName());
}

account *fabrika_tg_gr_ac::getCopy(account *a)
{
    return new account(a->getID(),a->getAccountToken(),a->getFirstName(),a->getLastName(),a->getIdBd(),a->getNameTable(),a->getCountPost());
}

post *fabrika_tg_gr_ac::getCopy(post *p)
{
    return new post(p->getIdBd(),p->getNameTable(),p->GetNamePost(),p->GetTextPost(),p->GetAttachPost());
}

bool fabrika_tg_gr_ac::remove(tag *t)
{
    if (t->getNameTable() == "TagAccountTable") return this->tal->removeitem(t);
    return this->tgl->removeitem(t);
}

bool fabrika_tg_gr_ac::remove(group *g)
{
    return this->grl->removeitem(g);
}

bool fabrika_tg_gr_ac::remove(account *a)
{
    return this->acl->removeitem(a);
}

bool fabrika_tg_gr_ac::remove(post *p)
{
    return this->pl->removeitem(p);
}

bool fabrika_tg_gr_ac::updatepost(post *p, QString name, QString text_post, QString attach_post)
{
    p->setAttachPost(attach_post);
    p->setNamePost(name);
    p->setTextPost(text_post);
    return true;

}

bool fabrika_tg_gr_ac::updatetag(tag *t, QString tagname)
{
    t->setTagName(tagname);
}
