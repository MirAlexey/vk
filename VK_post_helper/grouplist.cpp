#include "grouplist.h"

grouplist::grouplist(QObject *parent) :
    QObject(parent)
{
    this->list_group = new QList<group*>();
    this->itr = new QListIterator<group*>(*list_group);
    this->itr2 = new QListIterator<group*>(*list_group);
    itr2->toFront();
    itr->toFront();
}
group* grouplist::firstgroup()
{
    this->itr2 = new QListIterator<group*>(*list_group);
    itr2->toFront();
    return itr2->next();
}

group* grouplist::nextgroup()
{
   return itr->next();
}

void grouplist::begin()
{
   this->itr = new QListIterator<group*>(*list_group);
   itr->toFront();
}

bool grouplist::groupinlist(group *g)
{
    this->itr2 = new QListIterator<group*>(*list_group);
    itr2->toFront();
    while (itr2->hasNext()){
        group* gt = itr2->next();
        if (gt->getID()==g->getID()) return true;
    }
    return false;
    // return list_group->contains(g);
}

group* grouplist::lastgroup()
{
    this->itr2 = new QListIterator<group*>(*list_group);
    itr2->toBack();
    return itr2->previous();
}

bool grouplist::addgroup(group *g)
{
   if (!groupinlist(g)) {
       list_group->append(g);}

   return true;
}

bool grouplist::removegroup(group *g)
{
   return list_group->removeOne(g);
}

int grouplist::countgroup()
{
    return list_group->count();
}

bool grouplist::hasnextgroup()
{
 return itr->hasNext();
}
