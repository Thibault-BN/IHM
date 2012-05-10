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
    void fill(Card*);
    Card * getLeaf() const;
    Card * getCardI(int i) const;

    void deal(int); //Deal 3 ou 1 ?
    void describe();

    void draw(QPainter &painter);

    inline void setPos(int x, int y) {posX=x; posY=y;}
    inline void setSize(int w_,int h_) {w = w_; h = h_;}
    inline int &getX() {return posX;}
    inline int &getY() {return posY;}
    inline int &getW() {return w;}
    inline int &getH() {return h;}
    inline void setIndex(int i) {index = i;}
    inline void setEcart(int ec) {ecart=ec;}
    inline int getEcart() {return ecart;}
    inline Card* getRootCard() {return cards;}
    inline void setRoot(Card* card) {cards = card;}
    inline int getIndex() {return index;}

private:
    Card* cards;
    int index;
    int posX;
    int posY;
    int w;
    int h;
    int ecart;
};

#endif // DECK_H
