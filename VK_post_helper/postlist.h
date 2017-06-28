#ifndef POSTLIST_H
#define POSTLIST_H

#include <QObject>
#include <post.h>




class postlist
{

public:
    explicit postlist();
    post* firstpost();
    post* nextpost();
    void begin();
    bool postinlist(post *p);
    post* lastpost();
    bool addpost(post *p);
    bool removepost(post *p);
    int countpost();
    bool hasnextpost();
    post *at(int i){if (i<0 || i> list_post->count()) return lastpost();
                        else return list_post->at(i);}

private:
    QList<post*> *list_post;
    QListIterator<post*> *itr;//(list_post);
    QListIterator<post*> *itr2;//(list_post);
};

#endif // POSTLIST_H
