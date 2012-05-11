#ifndef CARD_H
#define CARD_H

#include <QPainter>
#include <iostream>

using namespace std;

/* Classe instanciee pour chaque carte du jeu (52 fois)
 * Structure de liste chainee : chaque carte contient l'adresse de la carte du dessus et celle de la carte du dessous
 *
 */
class Card
{
public:
    Card(int, bool face);

    void draw(QPainter &painter);

    //Getters
    inline int &getX() {return posX;}
    inline int &getY() {return posY;}
    inline int &getW() {return w;}
    inline int &getH() {return h;}
    inline int getNumber() const { return number; }
    inline bool getFace() const { return faceDown; }

    //Fonctions de structures
    inline Card * getNextCard() const { return nextCard; }
    inline Card * getPreviousCard() const { return previousCard; }
    Card * getLeaf();
    int getLengthToLeaf();

    //Setters
    inline void setPos(int x, int y) {posX=x; posY=y;}
    inline void setSize(int w_, int h_) {w=w_; h=h_;}
    inline void setNextCard(Card* _card) {nextCard = _card;}
    inline void setPreviousCard(Card* _card) { previousCard = _card; }
    inline void setFace(bool face) {faceDown = face;}

private:
    int number; //valeur de la carte
    bool faceDown; //carte face contre terre ou pas
    int w;
    int h;
    int posX;
    int posY;

    Card* previousCard;
    Card* nextCard;
};

#endif // CARD_H
