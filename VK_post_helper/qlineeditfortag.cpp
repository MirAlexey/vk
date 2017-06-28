#include "qlineeditfortag.h"




QLineEditforTag::QLineEditforTag(tag *t, QWidget *parent):
    QLabel(parent)
{
 this->t=t;
 this->setText(this->t->GetNameTag());
    this->setAlignment(Qt::AlignCenter);
}


QLabelforPost::QLabelforPost(post *p, QWidget *parent):
    QLabel(parent)
{
    this->p = p;
    this->setText(this->p->GetNamePost());
    this->setAlignment(Qt::AlignCenter);
}
