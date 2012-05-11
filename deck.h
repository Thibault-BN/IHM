#ifndef DECK_H
#define DECK_H

#include "card.h"

#include <QVector>
#include <iostream>
#include <QPainter>

using namespace std;

/*
 * Le deck est la pile de carte qui va être retournée par le joueur au cours du jeu
 * Peut être retournée une carte par une (deal 1) ou trois carte par trois (deal 3)
 */

class Deck
{
public:
    Deck();
    ~Deck();

    //Manips cards
    void fill(Card*);
    Card * getLeaf() const;
    Card * getCardI(int i) const;

    void deal(int); //Deal 3 ou 1 ?

    //Dessin
    void draw(QPainter &painter, int dealT);

    //Setters
    inline void setPos(int x, int y) {posX=x; posY=y;}
    inline void setSize(int w_,int h_) {w = w_; h = h_;}
    inline void setIndex(int i) {index = i;}
    inline void setEcart(int ec) {ecart=ec;}
    inline void setRootCard(Card* _c) { cards = _c;}

    //Getters
    inline int getEcart() {return ecart;}
    inline int &getX() {return posX;}
    inline int &getY() {return posY;}
    inline int &getW() {return w;}
    inline int &getH() {return h;}
    inline Card* getRootCard() {return cards;}
    inline int getIndex() {return index;}

private:
    Card* cards; //Adresse carte du dessous
    int index;  //index de la carte retournee
    int posX;
    int posY;
    int w;
    int h;
    int ecart;
};

#endif // DECK_H
