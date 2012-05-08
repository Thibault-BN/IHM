#ifndef DECK_H
#define DECK_H

#include "card.h"

#include <QVector>
#include <iostream>

using namespace std;

class Deck
{
public:
    Deck();

    //Manips cards
    void fill(QVector<Card*> &);

    void deal(int); //Deal 3 ou 1 ?
    void describe();

private:
    QVector<Card*> deck;
    int iCardUp; //i Card sur le dessus
};

#endif // DECK_H
