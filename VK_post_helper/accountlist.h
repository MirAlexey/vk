#ifndef ACCOUNTLIST_H
#define ACCOUNTLIST_H

#include <QObject>
#include <account.h>

class accountlist
{

public:
    explicit accountlist();
    account* firstaccount();
    account* nextaccount();
    void begin();
    bool accountinlist(account *a);
    account* lastaccount();
    bool addaccount(account *a);
    bool removeaccount(account *a);
    int countaccount();
    bool hasnextaccount();
    account *at(int i){if (i<0 || i> list_account->count())return lastaccount();
            else  return list_account->at(i);}

private:
    QList<account*> *list_account;
    QListIterator<account*> *itr;//(list_account);
    QListIterator<account*> *itr2;//(list_account);


};


#endif // ACCOUNTLIST_H
