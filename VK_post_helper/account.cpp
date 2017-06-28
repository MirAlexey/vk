#include <account.h>


bool account::operator==(account *right)
{
    return this->id==right->id;
}

bool account::operator==(account right)
{
    return this->id==right.id;
}


QString account::getName()
{
    return this->getFirstName()+" "+this->getLastName();
}
