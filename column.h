#ifndef COLUMN_H
#define COLUMN_H

#include <QVector>
#include <string>

#include "card.h"

using namespace std;

class Column
{
public:
    Column();

    //Manip cards
    void add(QVector<Card*>);

    //dessin
    void draw(int); //... arguments

    //dev
    string describe();

private:
    QVector<Card*> cards;

};

#endif // COLUMN_H
