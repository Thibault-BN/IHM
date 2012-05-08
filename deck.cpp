#include "deck.h"

Deck::Deck()
{
}

void Deck::fill(QVector<Card*> & _deck)
{
    deck = _deck;
}

void Deck::describe()
{
    cout << "Deck " << endl;

    for (QVector<Card*>::iterator it = deck.begin(); it != deck.end(); it++)
    {
        cout << " " << (*it)->getNumber();
    }
    cout << endl;
}
