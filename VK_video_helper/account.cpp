#include <account.h>


/*bool Account::operator==(account *right)
{
    return this->id==right->id;
}

bool Account::operator==(account right)
{
    return this->id==right.id;
}*/


QString Account::getName()
{
    return this->getFirstName()+" "+this->getLastName();
}


