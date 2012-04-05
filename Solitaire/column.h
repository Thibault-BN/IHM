#ifndef COLUMN_H
#define COLUMN_H

#include <vector>
#include <string>

#include "card.h"

using namespace std;

class Column
{
public:
    Column();

    //Manip cards
    void add(vector<Card*>);

    //dessin
    void draw(int); //... arguments

    //dev
    string describe();

private:
    vector<Card*> cards;

};

#endif // COLUMN_H
