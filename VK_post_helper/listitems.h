#ifndef LISTITEMS_H
#define LISTITEMS_H
#include <QList>

template<class T> class listitems
{
public:
    listitems(){

        list_items = new QList<T*>();
        list_items->clear();
        itr = new QListIterator<T*>(*list_items);
        itr2 = new QListIterator<T*>(*list_items);
        itr2->toFront();
        itr->toFront();

    }
    T *firstitem();
    T *nextitem();
    void begin();
    bool iteminlist(T *i);
    T *lastitem();
    bool additem(T *i);
    bool removeitem(T *i);
    int countitem();
    bool hasnextitem();
    T *at(int i);

private:
    QList<T*> *list_items;
    QListIterator<T*> *itr;//(list_account);
    QListIterator<T*> *itr2;//(list_account);


};
//template<class T> listitems<T>::listitems()
//{

//    list_items = new QList<T*>();
//    itr = new QListIterator<T*>(*list_items);
//    itr2 = new QListIterator<T*>(*list_items);
//    itr2->toFront();
//    itr->toFront();

//}

template<class T> T* listitems<T>::firstitem()
{
    itr2 = new QListIterator<T*>(*list_items);
    itr2->toFront();
    return itr2->next();
}

template<class T> T* listitems<T>::nextitem()
{

   if (itr->hasNext())return itr->next();
   itr->toFront();
   return itr->next();
}

template<class T> void listitems<T>::begin()
{
   itr = new QListIterator<T*>(*list_items);
   itr->toFront();
}

template<class T> bool listitems<T>::iteminlist(T *i)
{
    itr2 = new QListIterator<T*>(*list_items);
    itr2->toFront();
    while (itr2->hasNext()){
        T* it = itr2->next();
        if (*it==*i) return true;
    }
    return false;

}


template<class T> T *listitems<T>::lastitem()
{
    itr2 = new QListIterator<T*>(*list_items);
    itr2->toBack();
    return itr2->previous();
}

template<class T> bool listitems<T>::additem(T *i)
{
   if (!iteminlist(i)) {list_items->append(i);return true;}
   return false ;
}

template<class T> bool listitems<T>::removeitem(T *i)
{
    if (iteminlist(i)) list_items->removeOne(i);
    return true;
}

template<class T> int listitems<T>::countitem()
{
    return list_items->count();
}

template<class T> bool listitems<T>::hasnextitem()
{
    return itr->hasNext();
}

template<class T> T *listitems<T>::at(int i){return list_items->at(i%list_items->count());}


#endif // LISTITEMS_H
