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
    void saveDeck(Card*);

private:
    Card*** stacks;
    Card** deck;
    Card*** columns;
    int * iLastFaceDownColumns;

    //Rajouter le temps
};

#endif // SAVEDBOARD_H
