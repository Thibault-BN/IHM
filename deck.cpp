#include "deck.h"

Deck::Deck()
{
    cards = NULL;
}

Deck::~Deck()
{
//    if(cards != NULL)
//    {
//        delete cards;
//    }
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

void Deck::describe()
{
    cout << "Deck " << endl;

    Card * card = cards;
    while (card != NULL)
    {
        cout << " " << card->getNumber();
        card = card->getNextCard();
    }
    cout << endl;

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

void Deck::draw(QPainter &painter){

    QRect rect(posX,posY,w,h);
    if (index!=cards->getLengthToLeaf()) {
        painter.drawImage(rect,QImage(":images/dos3.png"));
    }
    else {
        painter.drawRect(rect);
    }
    QRect rect2(posX+ecart,posY,w,h);
    painter.drawRect(rect2);

    if(index!=-1) {
        if (index>0) {
            getCardI(index-1)->draw(painter);
        }
        getCardI(index)->draw(painter);
    }
}

void Deck::deal(int i) {
    if (index == cards->getLengthToLeaf()) {
        index = -1;
    }
    else {
        index += i;
    }
}
