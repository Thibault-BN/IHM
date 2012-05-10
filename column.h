#ifndef COLUMN_H
#define COLUMN_H

#include <QVector>
#include <string>

#include "card.h"
#include <QPainter>

#include <QPen>

using namespace std;

class Column
{
public:
    Column();
//    ~Column();

    //Manip cards
    void add(Card*);
    Card * getLeaf() const;

    inline Card* getRootCard() const { return cards;}
    Card * getCardI(int i) const;

    //dessin
    void draw(QPainter &painter); //... arguments
    inline void setPos(int x, int y) {posX=x; posY=y;}
    inline void setSize(int w_, int h_) {w=w_; h=h_;}
    inline int &getX() {return posX;}
    inline int &getY() {return posY;}
    inline int &getW() {return w;}
    inline int &getH() {return h;}



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
