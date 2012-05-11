#include "deck.h"

Deck::Deck()
{
    cards = NULL;
}

Deck::~Deck()
{

}

void Deck::fill(Card * _deck)
{
    if (cards == NULL)
        cards = _deck;
    else
    {
        getLeaf()->setNextCard(_deck);
        _deck->setPreviousCard(getLeaf());
    }
}

Card * Deck::getLeaf() const
{
    Card * card = cards;

    while (card != NULL)
    {
        card = card->getNextCard();
    }
    return card;
}

Card * Deck::getCardI(int i) const
{
    int j=0;
    Card * card = cards;

    while (j < i)
    {
        card = card->getNextCard();
        j++;
    }
    return card;
}

void Deck::draw(QPainter &painter, int dealT){

    QRect rect(posX,posY,w,h);
    if (cards!=NULL) {
        if (index!=cards->getLengthToLeaf()) {
            painter.drawImage(rect,QImage(":images/dos3.png"));
        }
        else {
            painter.drawRect(rect);
        }
    }
    else {
        painter.drawRect(rect);
    }
    QRect rect2(posX+ecart,posY,w,h);
    painter.drawRect(rect2);

    if (index != -1) {
        if (dealT == 1) {
            if (index>0) {
                //On affiche aussi la carte du dessous
                getCardI(index-1)->draw(painter);
            }
            getCardI(index)->draw(painter);
        }
        else if (dealT==3) {
            //On affiche les 3 cartes ou les cartes restantes
            if (index<2) {
                for (int i=0;i<=index;i++) {
                    getCardI(i)->draw(painter);
                }
            }
            else {
                for (int j=0;j<3;j++) {
                    getCardI(index-2+j)->draw(painter);
                }
            }
        }
    }
}

void Deck::deal(int i) {
    if (i==1) {
        if (index == cards->getLengthToLeaf()) {
            index = -1;
        }
        else {
            index += i;
        }
    }
    else if (i==3) {
        if (index<cards->getLengthToLeaf()) {
            index += i;
            if (index>cards->getLengthToLeaf()) {
                index = cards->getLengthToLeaf();
            }
        }
        else {
            index = -1;
        }
    }
}
