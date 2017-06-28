#include "bdmanager.h"

BDManager::BDManager(QObject *parent) :
    QObject(parent)
{
    this->con = new Conector();
    this->fabrika = new fabrika_tg_gr_ac();

}

bool BDManager::openBD()
{
  if  (!con->OpenDB("QSQLITE","","","VKposthelperBD","","")) {qDebug()<< "База не найдена!";return false;}
  return true;

}

taglist *BDManager::getTagGroupList()
{
 QString  s, srzr;
 taglist *tg;
 QStringList sl;
 tg = new taglist();
 sl.clear();
 s="SELECT * FROM TagGroupTable";
 srzr = str_rzr;
 if (!con->QueryDB(s,sl,srzr))
          {
       qDebug()<< "Запрос не выполнен";
          }
 qDebug()<< sl;
 if (sl.count()>0)
    for (int i =0 ; i< sl.count(); i++) {
       QStringList slt = sl.at(i).split(srzr);
       tg->additem(fabrika->getNewTag(slt[1],slt[0].toInt(),"TagGroupTable"));
    }
 return tg;
}

taglist *BDManager::getTagAccountList()
{
 QString  s, srzr;
 taglist *tg;
 QStringList sl;
 tg = new taglist();
 sl.clear();
 s="SELECT * FROM TagAccountTable";
 srzr = str_rzr;
 if (!con->QueryDB(s,sl,srzr))
          {
       qDebug()<< "Запрос не выполнен";
          }
 qDebug()<< sl;
 if (sl.count()>0)
    for (int i =0 ; i< sl.count(); i++) {
       QStringList slt = sl.at(i).split(srzr);
       tg->additem(fabrika->getNewTag(slt[1],slt[0].toInt(),"TagAccountTable"));
    }
 return tg;
}




grouplist *BDManager::getGroupList()
{
    QString  s, srzr;
    grouplist *gl;
    QStringList sl;
    gl = new grouplist();
    sl.clear();
    s="SELECT * FROM GroupTable";
    srzr = str_rzr;
    if (!con->QueryDB(s,sl,srzr))
             {
          qDebug()<< "Запрос не выполнен";
              }
    qDebug()<< sl;
    if (sl.count()>0)
       for (int i =0 ; i< sl.count(); i++) {
         QStringList slt = sl.at(i).split(srzr);
         gl->additem(fabrika->getNewGroup(slt[0].toInt(),"GroupTable",slt[1].toInt(),slt[2],slt[3],slt[4]));
       }
    return gl;
}

accountlist *BDManager::getAccountList()
{
    QString  s, srzr;
    accountlist *al;
    QStringList sl;
    al = new accountlist();
    sl.clear();
    s="SELECT * FROM AccountTable";
    srzr = str_rzr;
    if (!con->QueryDB(s,sl,srzr))
             {
          qDebug()<< "Запрос не выполнен";

             }
    qDebug()<< sl;
    if (sl.count()>0)
       for (int i =0 ; i< sl.count(); i++) {
         QStringList slac;
         int counterofpost = 0;
         QStringList slt = sl.at(i).split(srzr);
         s = QString("select count(*) from SendPostTB where id_account_fk_accounttable = %1 and data = date();").arg(slt[0].toInt());
                 if (con->QueryDB(s,slac,srzr))
                          {
                       counterofpost = slac.at(0).toInt();
                           }


         al->additem(fabrika->getNewAccount(slt[1].toInt(),slt[2],slt[3],slt[4],slt[0].toInt(),"AccountTable",counterofpost));
       }
    return al;
}

postlist *BDManager::getPostList()
{
    QString  s, srzr;
    postlist *pl;
    QStringList sl;
    pl = new postlist();
    sl.clear();
    s="SELECT * FROM PostTable";
    srzr = str_rzr;
    if (!con->QueryDB(s,sl,srzr))
             {
          qDebug()<< "Запрос не выполнен";
          return pl;
             }
    qDebug()<< sl;
    if (sl.count()>0)
       for (int i =0 ; i< sl.count(); i++) {
         QStringList slt = sl.at(i).split(srzr);
         pl->additem(fabrika->getNewPost(slt[0].toInt(),"PostTable",slt[1],slt[2],slt[3]));
       }
    return pl;
}

taglist *BDManager::getTagForGroup(group *g)
{
    QString  s, srzr;
    taglist *tg;
    QStringList sl;
    tg = new taglist();
    sl.clear();
    s=QString("select * from TagGroupTable where id_tag in (select id_tag_fk_tagtable from GroupTagTB where id_group_fk_grouptable = %1);").arg(g->getIdBd());
    srzr = str_rzr;
    if (!con->QueryDB(s,sl,srzr))
             {
          qDebug()<< "Запрос не выполнен";
             }
    qDebug()<< sl;
    if (sl.count()>0)
       for (int i =0 ; i< sl.count(); i++) {
          QStringList slt = sl.at(i).split(srzr);
          tg->additem(fabrika->getNewTag(slt[1],slt[0].toInt(),"TagGroupTable"));
       }
    return tg;

}

taglist* BDManager::getTagForAccount(account *a)
{
    QString  s, srzr;
    taglist *tg;
    QStringList sl;
    tg = new taglist();
    sl.clear();
    s=QString("select * from TagAccountTable where id_tag in (select id_tag_fk_tagtable from AccountTagtb where id_account_fk_accounttable = %1);").arg(a->getIdBd());
    srzr = str_rzr;
    if (!con->QueryDB(s,sl,srzr))
             {
          qDebug()<< "Запрос не выполнен";

             }
    qDebug()<< sl;
    if (sl.count()>0)
        for (int i =0 ; i< sl.count(); i++) {
           QStringList slt = sl.at(i).split(srzr);
           tg->additem(fabrika->getNewTag(slt[1],slt[0].toInt(),"TagAccountTable"));
       }
    return tg;
}

grouplist* BDManager::getGroupForPost(post *p)
{
    QString  s, srzr;
    grouplist *gl;
    QStringList sl;
    gl = new grouplist();
    sl.clear();
    s=QString("select * from GroupTable where id_group in (select id_group_fk_grouptable from GroupTagTB where id_tag_fk_tagtable in (select id_tag_fk_tagtable from PostTagforGroupTB  where id_post_fk_posttable = %1));").arg(p->getIdBd());
    srzr = str_rzr;
    if (!con->QueryDB(s,sl,srzr))
             {
          qDebug()<< "Запрос не выполнен";
              }
    qDebug()<< sl;
    if (sl.count()>0)
       for (int i =0 ; i< sl.count(); i++) {
         QStringList slt = sl.at(i).split(srzr);
         gl->additem(fabrika->getNewGroup(slt[0].toInt(),"GroupTable",slt[1].toInt(),slt[2],slt[4],slt[3]));
       }
    return gl;
}

accountlist *BDManager::getAccountForPost(post *p)
{
    QString  s, srzr;
    accountlist *al;
    QStringList sl;
    al = new accountlist();
    sl.clear();
    s=QString("select * from AccountTable where id_account in (select id_account_fk_accounttable from AccountTagTB where id_tag_fk_tagtable in (select id_tag_fk_tagtable from PostTagforAccountTB  where id_post_fk_posttable = %1));").arg(p->getIdBd());
    srzr = str_rzr;
    if (!con->QueryDB(s,sl,srzr))
             {
          qDebug()<< "Запрос не выполнен";

             }
    qDebug()<< sl;
    if (sl.count()>0)
       for (int i =0 ; i< sl.count(); i++) {
         QStringList slt = sl.at(i).split(srzr);
         al->additem(fabrika->getNewAccount(slt[1].toInt(),slt[2],slt[3],slt[4],slt[0].toInt(),"AccountTable"));
       }
    return al;
}

taglist *BDManager::getPostTagforGroup(post *p)
{
    QString  s, srzr;
    taglist *tg;
    QStringList sl;
    tg = new taglist();
    sl.clear();
    s=QString("select * from TagGroupTable where id_tag in (select id_tag_fk_tagtable from PostTagforGroupTB where id_post_fk_posttable = %1);").arg(p->getIdBd());
    srzr = str_rzr;
    if (!con->QueryDB(s,sl,srzr))
             {
          qDebug()<< "Запрос не выполнен";
          return tg;
             }
    qDebug()<< sl;
    if (sl.count()>0)
        for (int i =0 ; i< sl.count(); i++) {
           QStringList slt = sl.at(i).split(srzr);
           tg->additem(fabrika->getNewTag(slt[1],slt[0].toInt(),"TagGroupTable"));
       }
    return tg;
}




taglist *BDManager::getPostTagforAccount(post *p)
{

    QString  s, srzr;
    taglist *tg;
    QStringList sl;
    tg = new taglist();
    if (p == NULL) return tg;
    sl.clear();
    s=QString("select * from TagAccountTable where id_tag in (select id_tag_fk_tagtable from PostTagforAccountTB where id_post_fk_posttable = %1);").arg(p->getIdBd());
    srzr = str_rzr;
    if (!con->QueryDB(s,sl,srzr))
             {
          qDebug()<< "Запрос не выполнен";
          return tg;
             }
    qDebug()<< sl;
    if (sl.count()>0)
        for (int i =0 ; i< sl.count(); i++) {
           QStringList slt = sl.at(i).split(srzr);
           tg->additem(fabrika->getNewTag(slt[1],slt[0].toInt(),"TagAccountTable"));
       }
    return tg;
}

postlist *BDManager::getPostinQueue()
{
    QString  s, srzr;
    postlist *pl;
    QStringList sl;
    pl = new postlist();
    sl.clear();
    s="SELECT * FROM PostTable WHERE id_post in (SELECT * FROM QueuePost)";
    srzr = str_rzr;
    if (!con->QueryDB(s,sl,srzr))
             {
          qDebug()<< "Запрос не выполнен";
          return pl;
             }
    qDebug()<< sl;
    if (sl.count()>0)
       for (int i =0 ; i< sl.count(); i++) {
         QStringList slt = sl.at(i).split(srzr);
         pl->additem(fabrika->getNewPost(slt[0].toInt(),"PostTable",slt[1],slt[2],slt[3]));
       }
    return pl;
}

grouplist *BDManager::getGroupRemforPost(post *p)
{
    QString  s, srzr;
    grouplist *gl;
    QStringList sl;
    gl = new grouplist();
    sl.clear();
    s=QString("SELECT * FROM GroupTable WHERE id_group NOT IN (SELECT id_group_fk_grouptable FROM SendPostTB WHERE id_post_fk_posttable = %1) INTERSECT SELECT * FROM GroupTable WHERE id_group IN (SELECT id_group_fk_grouptable FROM GroupTagTB WHERE id_tag_fk_tagtable IN (SELECT id_tag_fk_tagtable FROM PostTagforGroupTB  WHERE id_post_fk_posttable = %1));").arg(p->getIdBd());
    srzr = str_rzr;
    if (!con->QueryDB(s,sl,srzr))
             {
          qDebug()<< "Запрос не выполнен";
          return gl;
             }
    qDebug()<< sl;
    if (sl.count()>0)
       for (int i =0 ; i< sl.count(); i++) {
         QStringList slt = sl.at(i).split(srzr);
         gl->additem(fabrika->getNewGroup(slt[0].toInt(),"GroupTable",slt[1].toInt(),slt[2],slt[4],slt[3]));
       }
    return gl;
}

grouplist *BDManager::getCopyGroupList(grouplist *gl)
{
   grouplist *glcopy = new grouplist();
   gl->begin();
   while(gl->hasnextitem()) glcopy->additem(fabrika->getCopy(gl->nextitem()));
   return glcopy;

}

accountlist *BDManager::getCopyAccountList(accountlist *al)
{
    accountlist *alcopy = new accountlist();
    al->begin();
    while(al->hasnextitem()) alcopy->additem(fabrika->getCopy(al->nextitem()));
    return alcopy;

}

postlist *BDManager::getCopyPostList(postlist *pl)
{
    postlist *plcopy = new postlist();
    pl->begin();
    while(pl->hasnextitem()) plcopy->additem(fabrika->getCopy(pl->nextitem()));
    return plcopy;
}

tag *BDManager::addtaggroup(QString tagname)
{
    QString  s, srzr;
    QStringList sl;
    sl.clear();
    s=QString("insert into TagGroupTable (tagname) values ('%1');").arg(tagname);
    srzr = str_rzr;
    if (!con->QueryDB(s,sl,srzr))
             {
             qDebug()<< "Запрос не выполнен";
             if (!sl[0].contains("UNIQUE"))   return NULL;
             }
     qDebug()<< sl;
     s="select last_insert_rowid();";
     sl.clear();
     if (!con->QueryDB(s,sl,srzr))
             {
             qDebug()<< "Запрос не выполнен";
             return NULL;
             }
     qDebug()<< sl;
     tag *p;
     p=fabrika->getNewTag(tagname,sl.at(0).toInt(),"TagGroupTable");
     return p;

}

tag *BDManager::addtagaccount(QString tagname)
{
    QString  s, srzr;
    QStringList sl;
    sl.clear();
    s=QString("insert into TagAccountTable (tagname) values ('%1');").arg(tagname);
    srzr = str_rzr;
    if (!con->QueryDB(s,sl,srzr))
             {
             qDebug()<< "Запрос не выполнен";
             if (!sl[0].contains("UNIQUE"))   return NULL;
             }
     qDebug()<< sl;
     s="select last_insert_rowid();";
     sl.clear();
     if (!con->QueryDB(s,sl,srzr))
             {
             qDebug()<< "Запрос не выполнен";
             return NULL;
             }
     qDebug()<< sl;
     tag *p;
     p=fabrika->getNewTag(tagname,sl.at(0).toInt(),"TagAccountTable");
     return p;

}


bool BDManager::addtag(group *g, tag *t)
{
    QString  s, srzr;
    QStringList sl;
    sl.clear();
    s=QString("insert into GroupTagTB values ('%1','%2');").arg(g->getIdBd()).arg(t->getIdBd());
    srzr = str_rzr;
    if (!con->QueryDB(s,sl,srzr))
             {
             qDebug()<< "Запрос не выполнен";
             return false;
             }
     qDebug()<< sl;
     g->addtag(t);
     return true;
}

bool BDManager::addtag(account *a, tag *t)
{
    QString  s, srzr;
    QStringList sl;
    sl.clear();
    s=QString("insert into AccountTagTB values ('%1','%2');").arg(a->getIdBd()).arg(t->getIdBd());
    srzr = str_rzr;
    if (!con->QueryDB(s,sl,srzr))
             {
             qDebug()<< "Запрос не выполнен";
             return false;
             }
     qDebug()<< sl;
     a->addtag(t);
     return true;
}

bool BDManager::addtag(group *g, taglist *t)
{
    t->begin();
    tag *tt;
    for (int i=0;i< t->countitem();i++ ){
      tt=t->nextitem();
      this->addtag(g,tt);
      }
    return true;
}

bool BDManager::addtag(account *a, taglist *t)
{
    t->begin();
    tag *tt;
    for (int i=0;i< t->countitem();i++ ){
      tt=t->nextitem();
      this->addtag(a,tt);
      }
    return true;
}

group *BDManager::addgroup(int id_VK, QString name, QString screen_name, QString type_group)
{
    QString  s, srzr;
    QStringList sl;
    sl.clear();
    s=QString("insert into GroupTable (id_VK, name, screen_name, type_group) values ('%1','%2','%3','%4');").arg(id_VK).arg(name).arg(screen_name).arg(type_group);
    srzr = str_rzr;
    if (!con->QueryDB(s,sl,srzr))
             {
             qDebug()<< "Запрос не выполнен";
             if (!sl[0].contains("UNIQUE"))   return NULL;
             }
     qDebug()<< sl;
     s="select last_insert_rowid();";
     sl.clear();
     if (!con->QueryDB(s,sl,srzr))
             {
             qDebug()<< "Запрос не выполнен";
             return NULL;
             }
     qDebug()<< sl;
     group *g;
     g=fabrika->getNewGroup(sl.at(0).toInt(),"GroupTable",id_VK,name,screen_name,type_group);
     return g;

}



account *BDManager::addaccount(int id_VK, QString account_token, QString first_name, QString last_name)
{
    QString  s, srzr;
    QStringList sl;
    sl.clear();
    s=QString("insert into AccountTable (id_VK, account_token,first_name, last_name) values ('%1','%2','%3','%4');").arg(id_VK).arg(account_token).arg(first_name).arg(last_name);
    srzr = str_rzr;
    if (!con->QueryDB(s,sl,srzr))
             {
             qDebug()<< "Запрос не выполнен";
             if (!sl[0].contains("UNIQUE"))   return NULL;
             }
     qDebug()<< sl;
     s="select last_insert_rowid();";
     sl.clear();
     if (!con->QueryDB(s,sl,srzr))
             {
             qDebug()<< "Запрос не выполнен";
             return NULL;
             }
     qDebug()<< sl;
     account *a;
     a=fabrika->getNewAccount(id_VK,account_token,first_name,last_name,sl[0].toInt(),"AccountTable");
     return a;
}

post *BDManager::addpost(QString name_post, QString text_post, QString attach_post)
{
    QString  s, srzr;
    QStringList sl;
    sl.clear();
    s=QString("insert into PostTable (name_post, text_post, attach_post) values ('%1','%2','%3');").arg(name_post).arg(text_post).arg(attach_post);
    srzr = str_rzr;
    if (!con->QueryDB(s,sl,srzr))
             {
             qDebug()<< "Запрос не выполнен";
             if (!sl[0].contains("UNIQUE"))   return NULL;
             }
     qDebug()<< sl;
     s="select last_insert_rowid();";
     sl.clear();
     if (!con->QueryDB(s,sl,srzr))
             {
             qDebug()<< "Запрос не выполнен";
             return NULL;
             }
     qDebug()<< sl;
     post *p;
     p=fabrika->getNewPost(sl.at(0).toInt(),"PostTable",name_post,text_post,attach_post);
     return p;
}

bool BDManager::addTagtoPostGroup(post *p, tag *t)
{
    if (t->getNameTable() == "TagAccountTable") return false;
    QString  s, srzr;
    QStringList sl;
    sl.clear();
    s=QString("insert into PostTagforGroupTB values ('%1','%2');").arg(p->getIdBd()).arg(t->getIdBd());
    srzr = str_rzr;
    if (!con->QueryDB(s,sl,srzr))
             {
             qDebug()<< "Запрос не выполнен";
             return false;
             }
     qDebug()<< sl;
     p->addtagforgroup(t);
     return true;

}

bool BDManager::addTagtoPostAccount(post *p, tag *t)
{
    if (t->getNameTable() == "TagGroupTable") return false;
    QString  s, srzr;
    QStringList sl;
    sl.clear();
    s=QString("insert into PostTagforAccountTB values ('%1','%2');").arg(p->getIdBd()).arg(t->getIdBd());
    srzr = str_rzr;
    if (!con->QueryDB(s,sl,srzr))
             {
             qDebug()<< "Запрос не выполнен";
             return false;
             }
     qDebug()<< sl;
     p->addtagforaccount(t);
     return true;
}

bool BDManager::addPosttoQueue(post *p)
{
    QString  s, srzr;
    QStringList sl;
    sl.clear();
    s=QString("INSERT INTO QueuePost VALUES (%1)").arg(p->getIdBd());
    srzr = str_rzr;
    if (!con->QueryDB(s,sl,srzr))
             {
             qDebug()<< "Запрос не выполнен";
             return false;
             }
     qDebug()<< sl;

     return true;
}

bool BDManager::addSendPost(post *p, group *g, account *a, QString id_post_VK)
{
    QString  s, srzr;
    QStringList sl;
    sl.clear();
    s=QString("insert into SendPostTB (id_post_fk_posttable, id_group_fk_grouptable, id_account_fk_accounttable,data, time,id_post_vk) values ('%1','%2','%3',date(),time(),'%4');").arg(p->getIdBd()).arg(g->getIdBd()).arg(a->getIdBd()).arg(id_post_VK);
    srzr = str_rzr;
    if (!con->QueryDB(s,sl,srzr))
             {
             qDebug()<< "Запрос не выполнен";
             return false;
             }
     qDebug()<< sl;

     return true;
}





bool BDManager::removetag(tag *t)
{
    QString  s, srzr;
    QStringList sl, sm;
    srzr = str_rzr;
    sm.clear();
    if (t->getNameTable()=="TagAccountTable")  sm << "AccountTagTB"<< "PostTagforAccountTB";
    else  sm <<  "GroupTagTB" << "PostTagforGroupTB";
        for (int i = 0; i<2 ;i++){
        sl.clear();
        s=QString("DELETE FROM %1  WHERE id_tag_fk_tagtable = %2;").arg(sm.at(i)).arg(t->getIdBd());
        if (!con->QueryDB(s,sl,srzr)){qDebug()<< "Запрос не выполнен";}
    }
    sl.clear();
    s=QString("DELETE FROM %1  WHERE id_tag = %2;").arg(t->getNameTable()).arg(t->getIdBd());
    if (!con->QueryDB(s,sl,srzr)){qDebug()<< "Запрос не выполнен";return false;}
    this->fabrika->remove(t);
    return true;

}

bool BDManager::removetag(group *g, tag *t)
{

   if (t->getNameTable()=="TagAccountTable") return false;
    QString  s, srzr;
    QStringList sl;
    srzr = str_rzr;
    sl.clear();
    s=QString("DELETE FROM GroupTagTB  WHERE id_tag_fk_tagtable = %1 AND id_group_fk_grouptable = %2;").arg(t->getIdBd()).arg(g->getIdBd());
    if (!con->QueryDB(s,sl,srzr)){qDebug()<< "Запрос не выполнен"; return false;}
    g->removetag(t);
    return true;
}

bool BDManager::removetag(account *a, tag *t)
{
    if (t->getNameTable()=="TagGroupTable") return false;
    QString  s, srzr;
    QStringList sl;
    srzr = str_rzr;
    sl.clear();
    s=QString("DELETE FROM AccountTagTB  WHERE id_tag_fk_tagtable = %1 AND id_account_fk_accounttable = %2;").arg(t->getIdBd()).arg(a->getIdBd());
    if (!con->QueryDB(s,sl,srzr)){qDebug()<< "Запрос не выполнен"; return false;}
    a->removetag(t);
    return true;
}

bool BDManager::removeposttagforgroup(post *p, tag *t)
{
    qDebug()<<t->getNameTable();
    if (t->getNameTable() != "TagGroupTable") return false;
    QString  s, srzr;
    QStringList sl;
    srzr = str_rzr;
    sl.clear();
    s=QString("DELETE FROM PostTagforGroupTB  WHERE id_tag_fk_tagtable = %1 AND id_post_fk_posttable = %2;").arg(t->getIdBd()).arg(p->getIdBd());
    if (!con->QueryDB(s,sl,srzr)){qDebug()<< "Запрос не выполнен"; return false;}
    p->removetagforgroup(t);
    return true;
}

bool BDManager::removeposttagforaccount(post *p, tag *t)
{
    if (t->getNameTable() != "TagAccountTable") return false;
    QString  s, srzr;
    QStringList sl;
    srzr = str_rzr;
    sl.clear();
    s=QString("DELETE FROM PostTagforAccountTB  WHERE id_tag_fk_tagtable = %1 AND id_post_fk_posttable = %2;").arg(t->getIdBd()).arg(p->getIdBd());
    if (!con->QueryDB(s,sl,srzr)){qDebug()<< "Запрос не выполнен"; return false;}
    p->removetagforaccount(t);
    return true;
}

bool BDManager::removegroup(group *g)
{
    QString  s, srzr;
    QStringList sl;
    srzr = str_rzr;

   // QString sm[]= {"" , "PostTagforGroupTB"};
   // for (int i = 0; i<2 ;i++){
        sl.clear();
        s=QString("DELETE FROM GroupTagTB  WHERE id_group_fk_grouptable = %1;").arg(g->getIdBd());
        if (!con->QueryDB(s,sl,srzr)){qDebug()<< "Запрос не выполнен";}
   // }
    sl.clear();
    s=QString("DELETE FROM GroupTable  WHERE id_group = %1;").arg(g->getIdBd());
    if (!con->QueryDB(s,sl,srzr)){qDebug()<< "Запрос не выполнен";return false;}

    sl.clear();
    s=QString("UPDATE SendPostTB SET id_group_fk_grouptable=-1 WHERE id_group_fk_grouptable = %1;").arg(g->getIdBd());
    if (!con->QueryDB(s,sl,srzr)){qDebug()<< "Запрос не выполнен";return false;}
    this->fabrika->remove(g);

    return true;

}

bool BDManager::removeaccount(account *a)
{
    QString  s, srzr;
    QStringList sl;
    srzr = str_rzr;


    sl.clear();
    s=QString("UPDATE SendPostTB SET id_account_fk_accounttable=-1 WHERE id_account_fk_accounttable = %1;").arg(a->getIdBd());
    if (!con->QueryDB(s,sl,srzr)){qDebug()<< "Запрос не выполнен. Не удален аккаунт из отправленных постов.";return false;}

    sl.clear();
    s=QString("DELETE FROM AccountTagTB  WHERE id_account_fk_accounttable = %1;").arg(a->getIdBd());
    if (!con->QueryDB(s,sl,srzr)){qDebug()<< "Запрос не выполнен";return false;}

    sl.clear();
    s=QString("DELETE FROM AccountTable  WHERE id_account = %1;").arg(a->getIdBd());
    if (!con->QueryDB(s,sl,srzr)){qDebug()<< "Запрос не выполнен"; return false;}

    this->fabrika->remove(a);
    return true;
}

bool BDManager::removepost(post *p)
{
    QString  s, srzr;
    QStringList sl;
    srzr = str_rzr;

    QString sm[]= {"PostTagforGroupTB" , "PostTagforAccountTB"};
    for (int i = 0; i<2 ;i++){
        sl.clear();
        s=QString("DELETE FROM %1  WHERE id_post_fk_posttable = %2;").arg(sm[i]).arg(p->getIdBd());
        if (!con->QueryDB(s,sl,srzr)){qDebug()<< "Запрос не выполнен";}
    }
    sl.clear();
    s=QString("DELETE FROM PostTable  WHERE id_post = %1;").arg(p->getIdBd());
    if (!con->QueryDB(s,sl,srzr)){qDebug()<< "Запрос не выполнен";return false;}
    sl.clear();
    s=QString("UPDATE SendPostTB SET id_post_fk_posttable=-1 WHERE id_post_fk_posttable = %1;").arg(p->getIdBd());
    if (!con->QueryDB(s,sl,srzr)){qDebug()<< "Запрос не выполнен";return false;}
    this->fabrika->remove(p);
    removePostfromQueue(p);
    return true;
}

bool BDManager::removePostfromQueue(post *p)
{
    QString  s, srzr;
    QStringList sl;
    srzr = str_rzr;
    sl.clear();
    s=QString("DELETE FROM QueuePost  WHERE id_post_fk_posttable = %1;").arg(p->getIdBd());
    if (!con->QueryDB(s,sl,srzr)){qDebug()<< "Запрос не выполнен"; return false;}
    return true;
}

bool BDManager::updatepost(post *p,QString name,QString text_post,QString attach_post)
{
    QString  s, srzr;
    QStringList sl;
    srzr = str_rzr;
    sl.clear();
    s=QString("UPDATE PostTable SET name_post = '%1', text_post = '%2',attach_post = '%3' WHERE id_post = %4;").arg(name).arg(text_post).arg(attach_post).arg(p->getIdBd());
    if (!con->QueryDB(s,sl,srzr)){qDebug()<< "Запрос не выполнен"; return false;}
    this->fabrika->updatepost(p,name,text_post,attach_post);
    return true;
}

bool BDManager::updatetag(tag *t,QString tagname)
{
    QString  s, srzr;
    QStringList sl;
    srzr = str_rzr;
    sl.clear();
    s=QString("UPDATE %1 SET tagname = '%2' WHERE id_tag = %3;").arg(t->getNameTable()).arg(tagname).arg(t->getIdBd());
    if (!con->QueryDB(s,sl,srzr)){qDebug()<< "Запрос не выполнен"; return false;}
    this->fabrika->updatetag(t,tagname);
    return true;
}



