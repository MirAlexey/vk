#include "listmanager.h"

Listmanager::Listmanager(QObject *parent) :
    QObject(parent)
{
    bdm = new BDManager(this);
    if (!bdm->openBD()) {QMessageBox::warning(0,"Ошибка базы данных!","Файл базы данных не найден. Поместите его в папку с исполняемым файлом.",QMessageBox::Ok);exit(-1);}
    plist = bdm->getPostList();
    glist = bdm->getGroupList();
    alist = bdm->getAccountList();
    tglist = bdm->getTagGroupList();
    talist = bdm->getTagAccountList();

    queueplist = new postlist();
    postlist *tempplist = bdm->getPostinQueue();
    countmaxsending=0;
    plist->begin();
    glist->begin();
    alist->begin();
    tglist->begin();
    talist->begin();
    for (int i =0;i<plist->countitem();i++){
        post *p = plist->nextitem();
        p->addtagforaccount(bdm->getPostTagforAccount(p));
        p->addtagforgroup(bdm->getPostTagforGroup(p));
        if (tempplist->iteminlist(p))queueplist->additem(p);
    }
    for (int i =0;i<glist->countitem();i++){
        group *g = glist->nextitem();
        g->addtag(bdm->getTagForGroup(g));
    }
    for (int i =0;i<alist->countitem();i++){
        account *a = alist->nextitem();
        a->addtag(bdm->getTagForAccount(a));
        countmaxsending+=a->getMaxCountPost()-a->getCountPost();
    }
    countSearshGroupList = 0;
}



taglist *Listmanager::getTagGroupList(){return this->tglist;}
taglist *Listmanager::getTagAccountList(){return this->talist;}

grouplist *Listmanager::getGroupList()
{
    return this->glist;
}

accountlist *Listmanager::getAccountList()
{
    return this->alist;
}

postlist *Listmanager::getPostList()
{
    return this->plist;
}

postlist *Listmanager::getQueuePostList()
{
    return this->queueplist;
}

accountlist *Listmanager::getAccountforPost(post *p)
{
    return bdm->getAccountForPost(p);
}

grouplist *Listmanager::getGroupforPost(post *p)
{
    return bdm->getGroupForPost(p);
}

grouplist *Listmanager::getGroupforPostRem(post *p)
{
    return bdm->getGroupRemforPost(p);

}

post *Listmanager::getCopyPost(post *p)
{
    postlist *pl=new postlist();
    pl->additem(p);
    bdm->getCopyPostList(pl);
    return pl->firstitem();
}

accountlist *Listmanager::getCopyAccountList(accountlist *al)
{
    return bdm->getCopyAccountList(al);
}

grouplist *Listmanager::getCopyGroupList(grouplist *gl)
{
    return bdm->getCopyGroupList(gl);
}


tag* Listmanager::addTagGroup(QString tagname)
{
    tag *t = bdm->addTagGroup(tagname);
    if (tglist->additem(t)) return t;
    return NULL;

}
tag* Listmanager::addTagAccount(QString tagname)
{
    tag *t = bdm->addTagAccount(tagname);
    if (talist->additem(t))
                 return t;
    return NULL;

}

post *Listmanager::addPost(QString name_post, QString text_post, QString attach_post)
{
   post *p = bdm->addpost(name_post,text_post,attach_post);
   if (plist->additem(p)) return p;
   return NULL;
}

bool Listmanager::removetag(tag *t)
{
   bool gr = true;
   if (t->getNameTable()== "TagAccountTable") {gr = false; talist->removeitem(t);}
   else tglist->removeitem(t);
   plist->begin();
   glist->begin();
   alist->begin();

   for (int i=0 ; i<plist->countitem();i++){
       post *p = plist->nextitem();
       if(gr) p->removetagforaccount(t);
       if(gr) p->removetagforgroup(t);
   }
   if(gr) for (int i=0 ; i<glist->countitem();i++) glist->nextitem()->removetag(t);
   if(gr) for (int i=0 ; i<alist->countitem();i++) alist->nextitem()->removetag(t);
   bdm->removeTag(t);
   return true;
}

QStringList Listmanager::getNameTagGroupList()
{
    QStringList sl;
    tglist->begin();
    for (int i=0 ; i<tglist->countitem();i++) sl<<tglist->nextitem()->GetNameTag();
    return sl;

}

QStringList Listmanager::getNameTagGroupList(taglist *tl)
{
    QStringList sl;
    tl->begin();
    for (int i=0 ; i<tl->countitem();i++) sl<<tl->nextitem()->GetNameTag();
    return sl;
}
QStringList Listmanager::getNameTagAccountList()
{
    QStringList sl;
    talist->begin();
    for (int i=0 ; i<talist->countitem();i++) sl<<talist->nextitem()->GetNameTag();
    return sl;

}

QStringList Listmanager::getNameTagAccountList(taglist *tl)
{
    QStringList sl;
    tl->begin();
    for (int i=0 ; i<tl->countitem();i++) sl<<tl->nextitem()->GetNameTag();
    return sl;
}
QStringList Listmanager::getNameGroupList()
{
    QStringList sl;
    glist->begin();
    for (int i=0 ; i<glist->countitem();i++) sl<<glist->nextitem()->getName();
    return sl;
}

QStringList Listmanager::getNameAccountList()
{
    QStringList sl;
    alist->begin();
    for (int i=0 ; i<alist->countitem();i++) {
                account *a = alist->nextitem();
                sl<<a->getFirstName()+" "+a->getLastName();}
    return sl;
}

QStringList Listmanager::getNamePostList()
{
    QStringList sl;
    plist->begin();
    for (int i=0 ; i<plist->countitem();i++) sl<<plist->nextitem()->GetNamePost();
    return sl;
}

int Listmanager::countTagGroup()
{
    return tglist->countitem();
}
int Listmanager::countTagAccount()
{
    return talist->countitem();
}

int Listmanager::countGroup()
{
    return glist->countitem();
}

int Listmanager::countAccount()
{
    return alist->countitem();
}

int Listmanager::countPost()
{
    return plist->countitem();
}

int Listmanager::countQueuePost()
{
    return queueplist->countitem();
}

bool Listmanager::addTagto(tag *t, group *g)
{
    bdm->addTag(g,t);
    //g->addtag(t);
    return true;
}

bool Listmanager::removetagfrom(tag *t, group *g)
{
    bdm->removeTag(g,t);
    //g->removetag(t);
    return true;
}
bool Listmanager::addTagto(tag *t, account *a)
{
    bdm->addTag(a,t);
    //a->addtag(t);
    return true;
}

bool Listmanager::removetagfrom(tag *t, account *a)
{
    bdm->removeTag(a,t);
    //a->removetag(t);
    return true;
}

bool Listmanager::addPostTagtoGroup(tag *t, post *p)
{
    if (t->getNameTable() == "TagAccountTable") return false;
    bdm->addTagtoPostGroup(p,t);
    //p->addtagforgroup(t);
    return true;
}

bool Listmanager::addPosttoQueue(post *p)
{
    if (!bdm->addPosttoQueue(p)) return false;
    queueplist->additem(p);
    return true;
}

bool Listmanager::addSendPost(post *p, group *g, account *a, QString id_post_vk, bool b)
{

    alist->begin();
    while(alist->hasnextitem())
    {
        account *at = alist->nextitem();
        if (at->getID() == a->getID()) at->upcounter();

    }
    if (b) return bdm->addSendPost(p,g,a,id_post_vk);
    return true;
}

bool Listmanager::addAccount(QStringList sl)
{
    if (sl.count()<4) return false;
    return alist->additem(bdm->addaccount(sl[0].toInt(),sl[1],sl[2],sl[3]));

}

bool Listmanager::addGroup(QStringList sl)
{
    if (sl.count()<6) return false;
    group *g = bdm->addgroup(sl[3].toInt(),sl[0],sl[4],sl[1]);
    if (g == NULL) {
         return false;}
    return glist->additem(g);
}

bool Listmanager::removePostTagfromGroup(tag *t, post *p)
{
    if (t->getNameTable() == "TagAccountTable") return false;
    if (!bdm->removePostTagForGroup(p,t))  return false;
    //p->removetagforgroup(t);
    return true;
}

bool Listmanager::removePostfromQueue(post *p)
{
    if (!bdm->removePostfromQueue(p)) return false;
    queueplist->removeitem(p);
    return true;
}

bool Listmanager::updatePost(post *p,QString name,QString text_post,QString attach_post)
{
    return bdm->updatePost(p,name,text_post,attach_post);
}

bool Listmanager::updateTagGroup(tag *t, QString tagname)
{
    if (t==NULL) return false;
    return bdm->updateTag(t, tagname);
}

bool Listmanager::updateTagAccount(tag *t, QString tagname)
{
    if (t==NULL) return false;
    return bdm->updateTag(t, tagname);
}

group *Listmanager::groupingrouplist(QStringList sl)
{
    for(int i=0;i<this->countGroup(); i++)
        if (sl.at(3) == QString::number(glist->at(i)->getID()))
                    return glist->at(i);
    return NULL;

}

bool Listmanager::addPostTagtoAccount(tag *t, post *p)
{
    if (t->getNameTable() == "TagGroupTable") return false;
    if (!bdm->addTagtoPostAccount(p,t)) return false;
    //p->addtagforaccount(t);
    return true;
}

bool Listmanager::removePostTagfromAccount(tag *t, post *p)
{
    if (t->getNameTable() == "TagGroupTable") return false;
    if (!bdm->removePostTagForAccount(p,t))  return false;
    //p->removetagforaccount(t);
    return true;
}

bool Listmanager::removeGroup(group *g)
{
   if (!bdm->removeGroup(g)) return false;
   glist->removeitem(g);
   return true;
}

bool Listmanager::removeAccount(account *a)
{
    if (!bdm->removeAccount(a)) return false;
    alist->removeitem(a);
    return true;
}

bool Listmanager::removePost(post *p)
{
    if (!bdm->removePost(p)) return false;
    plist->removeitem(p);
    queueplist->removeitem(p);
    return true;
}
