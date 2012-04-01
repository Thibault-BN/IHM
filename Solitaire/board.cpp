#include "board.h"

Board::Board()
{
    //Creation des 7 colonnes
    columns = new Column[7];
    vector<Card*> cards;

    for (int i=0; i < 52; i++)
    {
        cards.push_back(new Card(i));
    }

    random_shuffle(cards.begin(),cards.end());

    fillColumns(cards);
}


Board::~Board()
{
    delete [] colums;
}

Board::fillColumns(vector<Card*> cards)
{

}
