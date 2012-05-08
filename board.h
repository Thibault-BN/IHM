#ifndef BOARD_H
#define BOARD_H

#include "column.h"
#include "deck.h"
#include "card.h"

#include <algorithm>
#include <iostream>
#include <QVector>

using namespace std;

class Board
{
public:
    Board();
    ~Board();


private:
    Column * columns;
    Deck * deck;
    void fillColumns(QVector<Card*>*);
};

#endif // BOARD_H
