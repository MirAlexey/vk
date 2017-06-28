#include "checkboxtagforgroup.h"

QCheckBoxTagforGroup::QCheckBoxTagforGroup(tag *t, groupp *g, QWidget *parent, bool visibletext) :
    QWidget(parent)
{
    this->t = t;
    this->g = g;
    visible_text = visibletext;
    QLabel *lb = new QLabel(this);
//    if (visibletext) cb->setText(t->GetNameTag());
//            else cb->setText("");
    if (g->tagin(t)) lb->setText("V");
    lb->setAlignment(Qt::AlignCenter);
    this->label = lb;
    QHBoxLayout *hbl = new QHBoxLayout(this);
    hbl->addWidget(lb);
    hbl->setAlignment(Qt::AlignCenter);
    hbl->setContentsMargins(0,0,0,0);
    this->setLayout(hbl);

}

void QCheckBoxTagforGroup::checkedBox()
{
    if (this->label->text()== "V") this->label->setText(" ");
       else this->label->setText("V");
}


QCheckBoxTagforAccount::QCheckBoxTagforAccount(tag *t, account *a, QWidget *parent, bool visibletext):
    QWidget(parent)
{
    this->t = t;
    this->a = a;
    visible_text = visibletext;
    QLabel *lb = new QLabel(this);
    if (a->tagin(t)) lb->setText("V");
    lb->setAlignment(Qt::AlignCenter);
    this->label = lb;
    QHBoxLayout *hbl = new QHBoxLayout(this);
    hbl->addWidget(lb);
    hbl->setAlignment(Qt::AlignCenter);
    hbl->setContentsMargins(0,0,0,0);
    this->setLayout(hbl);
}


void QCheckBoxTagforAccount::checkedBox()
{
    if (this->label->text()== "V") this->label->setText(" ");
       else this->label->setText("V");
}


QCheckBoxPostTagforAG::QCheckBoxPostTagforAG(tag *t, post *p,bool true_for_group_false_for_account , QWidget *parent):
    QWidget(parent)
{
    this->t = t;
    this->p = p;
   // visible_text = visibletext;
    QLabel *lb = new QLabel(this);
    if (true_for_group_false_for_account?p->getTagforGroup()->iteminlist(t):p->getTagforAccount()->iteminlist(t)) lb->setText("V");
    lb->setAlignment(Qt::AlignCenter);
    this->label = lb;
    QHBoxLayout *hbl = new QHBoxLayout(this);
    hbl->addWidget(lb);
    hbl->setAlignment(Qt::AlignCenter);
    hbl->setContentsMargins(0,0,0,0);
    this->setLayout(hbl);
}

void QCheckBoxPostTagforAG::checkedBox()
{
    if (this->label->text()== "V") this->label->setText(" ");
       else this->label->setText("V");
}
