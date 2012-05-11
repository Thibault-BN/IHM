#ifndef STACK_H
#define STACK_H

#include "card.h"

#include <QVector>
#include <QPainter>

/*
  Stack correspond aux 4 piles du haut à remplir
  On ne peut les remplir que d'une couleur
  et les cartes se suivent dans l'ordre
  */
class Stack
{
public:
    Stack();
    ~Stack();

    //Manipulation des cartes
    void addCard(Card*);

    //Setters
    inline void setRootCard(Card* card_) {cards=card_;}
    inline void setPos(int x, int y) {posX=x; posY=y;}
    inline void setSize(int w_,int h_) {w = w_; h = h_;}

    //Getters
    Card* getCardI(int) const;
    inline Card* getRootCard() const { return cards;}
    inline int &getX() {return posX;}
    inline int &getY() {return posY;}
    inline int &getW() {return w;}
    inline int &getH() {return h;}
    int getSize();

    void draw(QPainter &painter);

private:
    Card* cards; //Adresse carte du dessous : NULL ou adresse d'un As
    int posX;
    int posY;
    int w;
    int h;
};

#endif // STACK_H
