#ifndef CARD_H
#define CARD_H


using namespace std;

class Card
{
public:
    Card(int);

    void draw(); //arguments : coordonnees

    //Ajouter listener

private:
    int number;
    bool faceDown;

};

#endif // CARD_H