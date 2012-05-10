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

    inline Card*** getStacks() const {return stacks;}
    inline int * getNCardsStacks() const {return nCardsStacks;}

    inline Card** getDeck() const {return deck;}
    inline int getNCardsDeck() const {return nCardsDeck;}
    inline int getICardUpDeck() const {return iCardUpDeck;}

    inline Card*** getColumns() const {return columns;}
    inline int * getNCardsColumns() const {return nCardsColumns;}
    inline int * getILastFaceDownColumns() const {return iLastFaceDownColumns;}


private:
    Card*** stacks;
    int * nCardsStacks;

    Card** deck;
    int nCardsDeck;
    int iCardUpDeck;

    Card*** columns;
    int * nCardsColumns;
    int * iLastFaceDownColumns;

    //Rajouter le temps
};

#endif // SAVEDBOARD_H
