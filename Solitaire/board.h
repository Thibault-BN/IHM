#ifndef BOARD_H
#define BOARD_H

#include "column.h"
#include "deck.h"
#include "card.h"

#include <algorithm>

using namespace std;

class Board
{
public:
    Board();
    ~Board();


private:
    Column* columns;
    Deck deck;
    void fillColumns(vector<Card*>);
};

#endif // BOARD_H
