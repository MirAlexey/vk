#include <tag.h>


tag::tag(QString name, int id_BD, QString name_table): element_bd(id_BD,name_table)
{
    this->tag_name = name;
    count_item = 0;
    count_post = 0;
}

QString tag::getName()
{
    return tag_name;
}

QString tag::GetNameTag() {return tag_name;}
