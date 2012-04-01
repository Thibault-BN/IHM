#ifndef BOARD_H
#define BOARD_H

#include "column.h"


using namespace std;

class Board
{
public:
    Board();
    ~Board();


private:
    Column* columns;
    void fillColumns();
};

#endif // BOARD_H
