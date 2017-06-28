#include "post.h"

post::post(int id_BD, QString name_table, QString name_post, QString text_post, QString attach_post): element_bd(id_BD,name_table)
{
    this->name = name_post;
    this->text_post = text_post;
    this->attach_post=attach_post;
    this->tagforgroup = new taglist();
    this->tagforaccount = new taglist();
}


QString post::getName()
{
    return this->name;
}
