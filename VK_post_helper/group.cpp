#include <grouplist.h>

bool group::operator==(group *right)
{
    return this->id==right->id;
}

bool group::operator==(group right)
{
    return this->id==right.id;
}
