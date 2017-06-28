#include "accountlist.h"

accountlist::accountlist()
{
    list_account = new QList<account*>();
    itr = new QListIterator<account*>(*list_account);
    itr2 = new QListIterator<account*>(*list_account);
    itr2->toFront();
    itr->toFront();
}
account* accountlist::firstaccount()
{
    itr2 = new QListIterator<account*>(*list_account);
    itr2->toFront();
    return itr2->next();
}

account* accountlist::nextaccount()
{

   if (itr->hasNext())return itr->next();
   itr->toFront();
   return itr->next();
}

void accountlist::begin()
{
   itr = new QListIterator<account*>(*list_account);
   itr->toFront();
}

bool accountlist::accountinlist(account *a)
{
    itr2 = new QListIterator<account*>(*list_account);
    itr2->toFront();
    while (itr2->hasNext()){
        account* at = itr2->next();
        if (at->getID()==a->getID()) return true;
    }
    return false;
    //return list_account->contains(a);
}

account *accountlist::lastaccount()
{
    itr2 = new QListIterator<account*>(*list_account);
    itr2->toBack();
    return itr2->previous();
}

bool accountlist::addaccount(account *a)
{
   if (!accountinlist(a)) list_account->append(a);
   return true;
}

bool accountlist::removeaccount(account *a)
{
   return list_account->removeOne(a);
}

int accountlist::countaccount()
{
    return list_account->count();
}

bool accountlist::hasnextaccount()
{
    return itr->hasNext();
}
