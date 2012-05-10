#include "stack.h"

Stack::Stack()
{
    cards = NULL;
}

Stack::~Stack()
{
//    if(cards != NULL)
//    {
//        delete cards;
//    }
}

void Stack::addCard(Card * card)
{
}


Card* Stack::getCardI(int i) const
{
    int j=0;
    Card * card = cards;

    while (j < i)
    {
        card = card->getNextCard();
    }

    return card;
}

void Stack::draw(QPainter &painter){

    QRect rect(posX,posY,w,h);
    painter.drawRect(rect);

    if (cards != NULL) cards->getLeaf()->draw(painter);

}
