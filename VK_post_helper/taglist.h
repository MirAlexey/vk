#ifndef TAGLIST_H
#define TAGLIST_H

#include <QObject>
#include <tag.h>



class taglist
{

public:
    explicit taglist();
    tag* firstTag();
    tag* nextTag();
    void begin();
    bool taginlist(tag *t);
    tag* lasttag();
    bool addTag(tag *t);
    bool removeTag(tag *t);
    int countTag();
    bool hasnextTag();
    tag *at(int i){if (i<0 || i> list_tag->count())return lasttag();
                        else return list_tag->at(i);}
private:
    QList<tag*> *list_tag;
    QListIterator<tag*> *itr;//(list_tag);
    QListIterator<tag*> *itr2;//(list_tag);

};


#endif // TAGLIST_H
