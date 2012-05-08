#include "stack.h"

Stack::Stack()
{
}

Stack::~Stack()
{
}

void Stack::addCard(Card * card)
{
    cards.push_back(card);
}
