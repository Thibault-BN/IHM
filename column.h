#ifndef COLUMN_H
#define COLUMN_H

#include "card.h"

#include <QVector>
#include <string>
#include <QPainter>
#include <QPen>
#include <iostream>

using namespace std;

/*
 * Classe qui représente une colonne du jeu (il y en a 7)
 * Les cartes contenue sont stockées dans une liste chainee, qui commence à la carte root
 * On accède aux cartes indirectement, en passant par la carte racine (root, celle du dessous de la colonne)
 *
 */
class Column
{
public:
    Column();

    //Manipulation cards
    void add(Card*);

    inline Card* getRootCard() const { return cards;}
    inline void setRootCard(Card* card_) {cards=card_;}
    Card * getCardI(int i) const;

    //dessin
    void draw(QPainter &painter); //... arguments
    inline void setPos(int x, int y) {posX=x; posY=y;}
    inline void setSize(int w_, int h_) {w=w_; h=h_;}
    inline int &getX() {return posX;}
    inline int &getY() {return posY;}
    inline int &getW() {return w;}
    inline int &getH() {return h;}
    int getSize();

private:
    Card * cards; //Contient l'adresse de la carte du dessous de la colonne, ou NULL
    int posX;
    int posY;
    int w;
    int h;

};

#endif // COLUMN_H
