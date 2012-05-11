#ifndef COLUMN_H
#define COLUMN_H

#include "card.h"

#include <QVector>
#include <string>
#include <QPainter>
#include <QPen>
#include <iostream>

using namespace std;

class Column
{
public:
    Column();

    //Manip cards
    void add(Card*);

    inline Card* getRootCard() const { return cards;}
    Card * getCardI(int i) const;
    inline void setRootCard(Card* card_) {cards=card_;}

    //dessin
    void draw(QPainter &painter); //... arguments
    inline void setPos(int x, int y) {posX=x; posY=y;}
    inline void setSize(int w_, int h_) {w=w_; h=h_;}
    inline int &getX() {return posX;}
    inline int &getY() {return posY;}
    inline int &getW() {return w;}
    inline int &getH() {return h;}
    int getSize();

    //dev
    void describe();

private:
    Card * cards;
    int posX;
    int posY;
    int w;
    int h;

};

#endif // COLUMN_H
