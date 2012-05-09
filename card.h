#ifndef CARD_H
#define CARD_H

#include <QPainter>

using namespace std;

class Card
{
public:
    Card(int, bool face);

    int & getNumber();
    void setFace(bool face);
    void draw(QPainter &painter); //arguments : coordonnees
    inline void setPos(int x, int y) {posX=x; posY=y;}
    inline void setSize(int w_, int h_) {w=w_; h=h_;}

    //Ajouter listener

private:
    int number;
    bool faceDown;
    int w;
    int h;
    int posX;
    int posY;

};

#endif // CARD_H
