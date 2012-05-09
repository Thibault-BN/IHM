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

    void draw(QPainter &painter);

    inline void setPos(int x, int y) {posX=x; posY=y;}
    inline void setSize(int w_,int h_) {w = w_; h = h_;}
    inline int &getX() {return posX;}
    inline int &getY() {return posY;}
    inline int &getW() {return w;}
    inline int &getH() {return h;}

private:
    QVector<Card*> cards;
    int iCardUp; //i Card sur le dessus
    int posX;
    int posY;
    int w;
    int h;
};

#endif // DECK_H
