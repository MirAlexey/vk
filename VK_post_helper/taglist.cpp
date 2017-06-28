#include "taglist.h"

taglist::taglist()

{
    list_tag = new QList<tag*>();

    itr = new QListIterator<tag*>(*list_tag);
    itr2 = new QListIterator<tag*>(*list_tag);
    itr->toFront();
}

tag* taglist::firstTag()
{
    itr2 = new QListIterator<tag*>(*list_tag);
    itr2->toFront();
    return itr2->next();
}

tag* taglist::nextTag()
{
   return itr->next();
}

void taglist::begin()
{
   itr = new QListIterator<tag*>(*list_tag);
   itr->toFront();
}

bool taglist::taginlist(tag *t)
{
    itr2 = new QListIterator<tag*>(*list_tag);
    itr2->toFront();
    while (itr2->hasNext()){
        tag* tgt = itr2->next();
        if (tgt->GetNameTag()==t->GetNameTag()) return true;
    }
    return false;
    //return list_tag->contains(t);
}

tag* taglist::lasttag()
{
    itr2 = new QListIterator<tag*>(*list_tag);
    itr2->toBack();

    return itr2->previous();
}

bool taglist::addTag(tag *t)
{
   if (!taginlist(t)) {
               list_tag->append(t);
               return true;
                      }
   return false;
}

bool taglist::removeTag(tag *t)
{
    return list_tag->removeOne(t);
}

int taglist::countTag()
{
    return list_tag->count();
}

bool taglist::hasnextTag()
{
    return itr->hasNext();
}
