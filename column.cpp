#include "column.h"
#include <iostream>

using namespace std;

Column::Column()
{
    cards = NULL;
}

//Column::~Column()
//{
//    if(cards != NULL)
//    {
//        delete cards;
//    }
//}

void Column::add(Card * _cards)
{
    if (cards == NULL)
        cards = _cards;
    else
    {
        getLeaf()->setNextCard(_cards);
        _cards->setPreviousCard(getLeaf());
    }
}

Card * Column::getLeaf() const
{
    Card * card = cards;

    while (card != NULL)
    {
        card = card->getNextCard();
    }
    return card;
}

void Column::describe()
{
    cout << "Column " << endl;

    Card * card = cards;
    while (card != NULL)
    {
        cout << " " << card->getNumber();
        card = card->getNextCard();
    }
    cout << endl;
}

Card * Column::getCardI(int i) const
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

void Column::draw(QPainter &painter) {

    QRect rect(posX,posY,w,h);
    painter.drawRect(rect);

    Card * card = cards;

    while (card != NULL)
    {
        card->draw(painter);
        card = card->getNextCard();
    }
}
