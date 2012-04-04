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
    vector<Cards*> pile;

    for (int i = 0; i<7; i++)
    {
        for (int j=0; j<=i; j++)
        {
            pile.push_back(cards.back());
            cards.pop_back();
        }

        columns[i].add(pile);
    }
}
