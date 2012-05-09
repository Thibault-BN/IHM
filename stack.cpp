#include "stack.h"
#include <iostream>

using namespace std;

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

void Stack::draw(QPainter &painter){
    QRect rect(posX,posY,w,h);
    painter.drawRect(rect);

    if (cards.size()!=0) {
        cards.last()->draw(painter);
    }
}
