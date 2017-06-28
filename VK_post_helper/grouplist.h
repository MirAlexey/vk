#ifndef GROUPLIST_H
#define GROUPLIST_H

#include <QObject>
#include <group.h>

class grouplist : public QObject
{
    Q_OBJECT
public:
    explicit grouplist(QObject *parent = 0);
    group* firstgroup();
    group* nextgroup();
    void begin();
    bool groupinlist(group *g);
    group *lastgroup();
    bool addgroup(group *g);
    bool removegroup(group *g);
    int countgroup();
    bool hasnextgroup();
    group *at(int i){if (i<0 || i> list_group->count())return lastgroup();
            else  return list_group->at(i);}


private:

    QList<group*> *list_group;
    QListIterator<group*> *itr;//(list_group);
    QListIterator<group*> *itr2;//(list_group);
signals:

public slots:

};

#endif // GROUPLIST_H
