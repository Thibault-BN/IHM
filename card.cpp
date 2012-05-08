#include "card.h"

Card::Card(int i)
{
    this->number = i;
}

int & Card::getNumber()
{
    return number;
}
