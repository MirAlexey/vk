#ifndef ELEMENT_BD_H
#define ELEMENT_BD_H


#include <QString>

class element_bd
{

public:
    explicit element_bd(int id_BD,QString name_table);
    int getIdBd();
    QString getNameTable();
    virtual QString getName() = 0;
private:
    int id_BD;
    QString name_table;

};

#endif // ELEMENT_BD_H
