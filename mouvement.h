#ifndef MOUVEMENT_H
#define MOUVEMENT_H

#include "card.h"

class Mouvement
{
public:
    Mouvement();

private:
    /*
     Type :
     1 => Carte de colonne vers stack
     2 => Carte de colonne vers colonne
     3 => Carte de deck vers colonne
     4 => Carte de deck vers stack
     5 => Clic sur deck
     */
    int type;
    Card* movedCard;
    bool facePrevCard;

};

class ColumnToColumn
{

};

class ColumToStack
{

};

class DeckToColumn
{

};

class DeckToStack
{

};

class ClickOnDeck
{

};

#endif // MOUVEMENT_H
