#ifndef STACK_H
#define STACK_H

#include <QVector>

#include "card.h"

class Stack
{
public:
    Stack();
    ~Stack();

    void addCard(Card*);

private:
    QVector<Card*> cards;

};

#endif // STACK_H
