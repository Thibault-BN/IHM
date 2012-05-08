#include "board.h"

Board::Board()
{
    //Creation des 7 colonnes
    columns = new Column[7];
    QVector<Card*> cards;

    for (int i=0; i < 52; i++)
    {
        cards.push_back(new Card(i));
    }

    random_shuffle(cards.begin(),cards.end());

    fillColumns(&cards);

    deck = new Deck();
    deck->fill(cards);
    deck->describe();
}


Board::~Board()
{
    delete [] columns;
}

void Board::fillColumns(QVector<Card*> *cards)
{

    for (int i = 0; i<7; i++)
    {
        QVector<Card*> pile;

        cout << "Column " << i << endl
             << "    cartes ";

        for (int j=0; j<=i; j++) //1 carte dans la colonne 0, 2 cartes dans la collone 2...
        {
            pile.push_back(cards->back());
            cards->pop_back();
            cout << " " << pile.back()->getNumber();
        }

        cout << endl;
        columns[i].add(pile);
    }

    cout << "Columns filled" << endl;
}
