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
    void draw(QPainter &painter, int card_width, int card_height,int poscolX, int posColY, int j); //arguments : coordonnees

    //Ajouter listener

private:
    int number;
    bool faceDown;
    int width;
    int posX;
    int posY;

};

#endif // CARD_H
