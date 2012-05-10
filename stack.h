#ifndef STACK_H
#define STACK_H

#include <QVector>
#include <QPainter>

#include "card.h"

class Stack
{
public:
    Stack();
    ~Stack();

    void addCard(Card*);
    Card* getCardI(int) const;
    inline Card* getRootCard() const { return cards;}


    inline void setPos(int x, int y) {posX=x; posY=y;}
    inline void setSize(int w_,int h_) {w = w_; h = h_;}
    void draw(QPainter &painter);

private:
    Card* cards;
    int posX;
    int posY;
    int w;
    int h;
};

#endif // STACK_H
