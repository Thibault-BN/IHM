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

void Deck::deal(int dealType)
{
}

void Deck::draw(QPainter &painter){

    QRect rect(posX,posY,w,h);
    painter.drawImage(rect,QImage(":images/dos3.png"));
}
