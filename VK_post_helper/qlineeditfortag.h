#ifndef QLINEEDITFORTAG_H
#define QLINEEDITFORTAG_H

#include <QWidget>
#include <QLabel>
#include <tag.h>
#include <post.h>

class QLineEditforTag : public QLabel
{
    Q_OBJECT
public:
    explicit QLineEditforTag(tag *t,QWidget *parent = 0);
    tag *getTag(){return t;}
private:
    tag *t;

signals:

public slots:

};

class QLabelforPost : public QLabel
{
    Q_OBJECT
public:
    explicit QLabelforPost(post *p,QWidget *parent = 0);
    post *getpost(){return p;}
private:
    post *p;

signals:

public slots:

};

#endif // QLINEEDITFORTAG_H
