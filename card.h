#ifndef CARD_H
#define CARD_H


using namespace std;

class Card
{
public:
    Card(int);

    int & getNumber();
    void draw(); //arguments : coordonnees

    //Ajouter listener

private:
    int number;
    bool faceDown;
    int width;
    int posX;
    int posY;

};

#endif // CARD_H
