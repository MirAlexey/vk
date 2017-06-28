#include "postlist.h"


postlist::postlist()

{
    list_post = new QList<post*>();

    itr = new QListIterator<post*>(*list_post);
    itr2 = new QListIterator<post*>(*list_post);
    itr->toFront();
}

post* postlist::firstpost()
{
    itr2 = new QListIterator<post*>(*list_post);
    itr2->toFront();
    return itr2->next();
}

post* postlist::nextpost()
{
   return itr->next();
}

void postlist::begin()
{
    itr = new QListIterator<post*>(*list_post);
    itr->toFront();
}

bool postlist::postinlist(post *p)
{
    itr2 = new QListIterator<post*>(*list_post);
    itr2->toFront();
    while (itr2->hasNext()){
        post* pt = itr2->next();
        if (pt->getIdBd()==p->getIdBd()) return true;
    }
    return false;
    //return list_post->contains(p);
}

post* postlist::lastpost()
{
    itr2 = new QListIterator<post*>(*list_post);
    itr2->toBack();

    return itr2->previous();
}

bool postlist::addpost(post *p)
{
   if (!postinlist(p)) {
               list_post->append(p);
               return true;
                      }
   return true;
}

bool postlist::removepost(post *p)
{
   return list_post->removeOne(p);
}

int postlist::countpost()
{
    return list_post->count();
}

bool postlist::hasnextpost()
{
    return itr->hasNext();
}




