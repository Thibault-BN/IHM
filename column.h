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
    ~Column();

    //Manip cards
    void add(QVector<Card*> &);

    //dessin
    void draw(QPainter &painter); //... arguments

    //dev
    void describe();

    inline void setPos(int x, int y) {posX=x; posY=y;}
    inline void setSize(int w_, int h_) {w=w_; h=h_;}
    inline QVector<Card*> & getCards() {return cards;}

private:
    QVector<Card*> cards;
    int posX;
    int posY;
    int w;
    int h;

};

#endif // COLUMN_H
