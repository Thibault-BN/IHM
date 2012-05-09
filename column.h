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
    void draw(QPainter &painter, int card_width, int card_height, int ecartV, int ecartH, int i); //... arguments

    //dev
    void describe();

private:
    QVector<Card*> cards;

};

#endif // COLUMN_H
