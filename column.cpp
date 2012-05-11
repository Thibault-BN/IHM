#include "column.h"

using namespace std;

Column::Column()
{
    cards = NULL;
}

//Ajout d'une liste chainee de carte à la colonne
void Column::add(Card * _cards)
{
    if (cards == NULL) {
        cards = _cards;
    }
    else
    {
        //On connecte la carte terminale de la colonne (s'il existe) à _cards
        Card* leaf = cards->getLeaf();
        _cards->setPreviousCard(leaf);
        leaf->setNextCard(_cards);
    }
}

//Fonction de pseudo accès direct
Card * Column::getCardI(int i) const {
    int j=0;
    Card * card = cards;

    while (j < i) {
        card = card->getNextCard();
        j++;
    }
    return card;
}

void Column::draw(QPainter &painter) {

    QRect rect(posX,posY,w,h);
    painter.drawRect(rect);

    //On dessine la première carte, les autres suivront
    if (cards!=NULL) cards->draw(painter);
}

int Column::getSize() {
    if (cards==NULL) return 0;
    else return (cards->getLengthToLeaf() + 1);
}
