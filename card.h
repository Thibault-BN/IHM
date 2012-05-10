#ifndef CARD_H
#define CARD_H

#include <QPainter>
#include <iostream>

using namespace std;

class Card
{
public:
    Card(int, bool face);
//    ~Card();

    inline const int & getNumber() const { return number; }
    inline bool getFace() const { return faceDown; }
    inline Card * getPreviousCard() const { return previousCard; }
    inline void setPreviousCard(Card* _card) { previousCard = _card; }
    inline Card * getNextCard() const { return nextCard; }
    inline void setNextCard(Card* _card) { nextCard = _card; }
    Card * getLeaf() const;
    int getLengthToLeaf() const;

    inline void setPos(int x, int y) {posX=x; posY=y;}
    inline void setSize(int w_, int h_) {w=w_; h=h_;}
    inline int &getX() {return posX;}
    inline int &getY() {return posY;}
    inline int &getW() {return w;}
    inline int &getH() {return h;}

    void setFace(bool face);
    void draw(QPainter &painter);

    //Ajouter listener

private:
    int number;
    bool faceDown;
    int w;
    int h;
    int posX;
    int posY;

    Card* previousCard;
    Card* nextCard;


};

#endif // CARD_H
