#ifndef SAVEDBOARD_H
#define SAVEDBOARD_H

#include <QList>
#include "card.h"

/* Classe qui contient un état du jeu à un instant donné
 * "Remplie" à chaque action et est utilisée lors du restart de la partie ou d'un undo
 * On stocke des pointeurs : pas beaucoup de mémoire.
 */

class SavedBoard
{
public:
    SavedBoard();

    //Fonctions de sauvegarde des éléments du board
    void saveColumn(int,Card*);
    void saveStack(int,Card*);
    void saveDeck(Card*, int);

    //Fonctions qui sont appelées lors de la restauration du board correspondant à cette instance
    inline Card*** getStacks() const {return stacks;}
    inline int * getNCardsStacks() const {return nCardsStacks;}

    inline Card** getDeck() const {return deck;}
    inline int getNCardsDeck() const {return nCardsDeck;}
    inline int getICardUpDeck() const {return iCardUpDeck;}

    inline Card*** getColumns() const {return columns;}
    inline int * getNCardsColumns() const {return nCardsColumns;}
    inline int * getILastFaceDownColumns() const {return iLastFaceDownColumns;}


private:
    Card*** stacks;     //On stocke un tableau de taille 4 de Card**
    int * nCardsStacks; //Longueur de chaque stack

    Card** deck;
    int nCardsDeck;     //nombre de cartes du deck
    int iCardUpDeck;    //indice de la carte retournee

    Card*** columns;    //Tableau de taille 7 de Card**
    int * nCardsColumns;
    int * iLastFaceDownColumns; //Utilisé pour rétablir les bons faceUp ou faceDown des cartes
};

#endif // SAVEDBOARD_H
