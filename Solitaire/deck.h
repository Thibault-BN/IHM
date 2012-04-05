#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <vector>

class Deck
{
public:
    Deck();

    //Manips cards
    void fill(vector<Card*>);
    void deal(int); //Deal 3 ou 1 ?



private:
    vector<Card*> deck;
    int iCardUp; //i Card sur le dessus
};

#endif // DECK_H
