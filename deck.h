#ifndef DECK_H
#define DECK_H

#include "card.h"

#include <QVector>
#include <iostream>
#include <QPainter>

using namespace std;

class Deck
{
public:
    Deck();
    ~Deck();

    //Manips cards
    void fill(QVector<Card*> &);

    void deal(int); //Deal 3 ou 1 ?
    void describe();

    void draw(QPainter &painter, int width);

private:
    QVector<Card*> cards;
    int iCardUp; //i Card sur le dessus
};

#endif // DECK_H
