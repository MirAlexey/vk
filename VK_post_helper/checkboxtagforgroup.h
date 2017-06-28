#ifndef CHECKBOXTAGFORGROUP_H
#define CHECKBOXTAGFORGROUP_H

#include <group.h>
#include <QObject>
#include <QCheckBox>
#include <tag.h>
#include <account.h>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <post.h>



class QCheckBoxTagforGroup : public QWidget
{
    Q_OBJECT
public:
    explicit QCheckBoxTagforGroup(tag *t ,groupp *g, QWidget *parent = 0, bool visibletext = false);
    void checkedBox();
    bool ischekedBox(){return this->label->text()=="V"?true:false;}
    tag *getTag() {return t;}
    group *getGroup(){return g;}
private:
     tag *t;
     groupp *g;
     QLabel *label;
     bool visible_text;

signals:

public slots:

};

class QCheckBoxTagforAccount : public QWidget
{
    Q_OBJECT
public:
    explicit QCheckBoxTagforAccount(tag *t ,account *a, QWidget *parent = 0, bool visibletext = false);
    void checkedBox();
    bool ischekedBox(){return this->label->text()=="V"?true:false;}
    tag *getTag() {return t;}
    account *getAccount(){return a;}
private:
     tag *t;
     account *a;
     QLabel *label;
     bool visible_text;

signals:

public slots:

};

class QCheckBoxPostTagforAG : public QWidget
{
    Q_OBJECT
public:
    explicit QCheckBoxPostTagforAG(tag *t ,post *p, bool true_for_group_false_for_account, QWidget *parent = 0);
    void checkedBox();
    bool ischekedBox(){return this->label->text()=="V"?true:false;}
    tag *getTag() {return t;}
    post *getPost(){return p;}
private:
     tag *t;
     post *p;
     QLabel *label;
     //bool visible_text;

signals:

public slots:

};



#endif // CHECKBOXTAGFORGROUP_H
