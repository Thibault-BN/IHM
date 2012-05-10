#ifndef SAVEDBOARD_H
#define SAVEDBOARD_H

#include <QList>
#include "card.h"

class SavedBoard
{
public:
    SavedBoard();

    void saveColumn(int,Card*);
    void saveStack(int,Card*);
    void saveDeck(Card*, int);

private:
    Card*** stacks;
    Card** deck;
    int iCardUpDeck;
    Card*** columns;
    int * iLastFaceDownColumns;

    //Rajouter le temps
};

#endif // SAVEDBOARD_H
