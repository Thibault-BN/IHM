#include "stack.h"

Stack::Stack()
{
}

Stack::~Stack()
{
    delete [] cards;
}

Stack::addCard(Card * card)
{
    cards.push_back(card);
}
