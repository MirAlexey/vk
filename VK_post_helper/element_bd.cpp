#include <element_bd.h>

QString element_bd::getNameTable()
{
    return name_table;
}


element_bd::element_bd(int id_BD, QString name_table)
{
    this->id_BD=id_BD;
    this->name_table=name_table;
}

int element_bd::getIdBd()
{
    return id_BD;
}
