#include "stack.h"

Stack::Stack()
{
    cards = NULL;
}

Stack::~Stack()
{

}

void Stack::addCard(Card * card)
{
    if (cards == NULL) {
        cards = card;
    }
    else
    {
        card->setPreviousCard(cards->getLeaf());
        cards->getLeaf()->setNextCard(card);
        card->setNextCard(NULL);
    }
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

    if (cards != NULL){
        cards->draw(painter);
    }
}

int Stack::getSize() {
    if (cards==NULL) {
        return 0;
    }
    else return (cards->getLengthToLeaf()+1);
}
