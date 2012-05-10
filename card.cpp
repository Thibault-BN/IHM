#include "card.h"

Card::Card(int i,bool face)
{
    this->number = i;
    this->faceDown = face;
    this->nextCard = NULL;
    this->previousCard = NULL;
}

//Card::~Card()
//{
//    cout << "Carte deleted :" << this->number << endl;
//    if (nextCard != NULL)
//    {
//        delete nextCard;
//    }
//}

Card * Card::getLeaf()
{
    Card * card = this;

    while (card->getNextCard() != NULL)
    {
        card = card->getNextCard();
    }
    return card;
}

int Card::getLengthToLeaf() const
{
    int i = 0;

    Card * card = nextCard;

    while (card != NULL)
    {
        card = card->getNextCard();
        i++;
    }
    return i;
}

void Card::draw(QPainter &painter){

    QRect rect(posX,posY,w,h);
    if (faceDown) {
        painter.drawImage(rect,QImage(":images/dos3.png"));
    }
    else {
        switch(number) {

        case 0:
            painter.drawImage(rect,QImage(":images/asP.png"));
            break;
        case 1:
            painter.drawImage(rect,QImage(":images/deuxP.png"));
            break;
        case 2:
            painter.drawImage(rect,QImage(":images/troisP.png"));
            break;
        case 3:
            painter.drawImage(rect,QImage(":images/quatreP.png"));
            break;
        case 4:
            painter.drawImage(rect,QImage(":images/cinqP.png"));
            break;
        case 5:
            painter.drawImage(rect,QImage(":images/sixP.png"));
            break;
        case 6:
            painter.drawImage(rect,QImage(":images/septP.png"));
            break;
        case 7:
            painter.drawImage(rect,QImage(":images/huitP.png"));
            break;
        case 8:
            painter.drawImage(rect,QImage(":images/neufP.png"));
            break;
        case 9:
            painter.drawImage(rect,QImage(":images/dixP.png"));
            break;
        case 10:
            painter.drawImage(rect,QImage(":images/valetP.png"));
            break;
        case 11:
            painter.drawImage(rect,QImage(":images/dameP.png"));
            break;
        case 12:
            painter.drawImage(rect,QImage(":images/roiP.png"));
            break;
        case 13:
            painter.drawImage(rect,QImage(":images/asCO.png"));
            break;
        case 14:
            painter.drawImage(rect,QImage(":images/deuxCO.png"));
            break;
        case 15:
            painter.drawImage(rect,QImage(":images/troisCO.png"));
            break;
        case 16:
            painter.drawImage(rect,QImage(":images/quatreCO.png"));
            break;
        case 17:
            painter.drawImage(rect,QImage(":images/cinqCO.png"));
            break;
        case 18:
            painter.drawImage(rect,QImage(":images/sixCO.png"));
            break;
        case 19:
            painter.drawImage(rect,QImage(":images/septCO.png"));
            break;
        case 20:
            painter.drawImage(rect,QImage(":images/huitCO.png"));
            break;
        case 21:
            painter.drawImage(rect,QImage(":images/neufCO.png"));
            break;
        case 22:
            painter.drawImage(rect,QImage(":images/dixCO.png"));
            break;
        case 23:
            painter.drawImage(rect,QImage(":images/valetCO.png"));
            break;
        case 24:
            painter.drawImage(rect,QImage(":images/dameCO.png"));
            break;
        case 25:
            painter.drawImage(rect,QImage(":images/roiCO.png"));
            break;
        case 26:
            painter.drawImage(rect,QImage(":images/asCA.png"));
            break;
        case 27:
            painter.drawImage(rect,QImage(":images/deuxCA.png"));
            break;
        case 28:
            painter.drawImage(rect,QImage(":images/troisCA.png"));
            break;
        case 29:
            painter.drawImage(rect,QImage(":images/quatreCA.png"));
            break;
        case 30:
            painter.drawImage(rect,QImage(":images/cinqCA.png"));
            break;
        case 31:
            painter.drawImage(rect,QImage(":images/sixCA.png"));
            break;
        case 32:
            painter.drawImage(rect,QImage(":images/septCA.png"));
            break;
        case 33:
            painter.drawImage(rect,QImage(":images/huitCA.png"));
            break;
        case 34:
            painter.drawImage(rect,QImage(":images/neufCA.png"));
            break;
        case 35:
            painter.drawImage(rect,QImage(":images/dixCA.png"));
            break;
        case 36:
            painter.drawImage(rect,QImage(":images/valetCA.png"));
            break;
        case 37:
            painter.drawImage(rect,QImage(":images/dameCA.png"));
            break;
        case 38:
            painter.drawImage(rect,QImage(":images/roiCA.png"));
            break;
        case 39:
            painter.drawImage(rect,QImage(":images/asT.png"));
            break;
        case 40:
            painter.drawImage(rect,QImage(":images/deuxT.png"));
            break;
        case 41:
            painter.drawImage(rect,QImage(":images/troisT.png"));
            break;
        case 42:
            painter.drawImage(rect,QImage(":images/quatreT.png"));
            break;
        case 43:
            painter.drawImage(rect,QImage(":images/cinqT.png"));
            break;
        case 44:
            painter.drawImage(rect,QImage(":images/sixT.png"));
            break;
        case 45:
            painter.drawImage(rect,QImage(":images/septT.png"));
            break;
        case 46:
            painter.drawImage(rect,QImage(":images/huitT.png"));
            break;
        case 47:
            painter.drawImage(rect,QImage(":images/neufT.png"));
            break;
        case 48:
            painter.drawImage(rect,QImage(":images/dixT.png"));
            break;
        case 49:
            painter.drawImage(rect,QImage(":images/valetT.png"));
            break;
        case 50:
            painter.drawImage(rect,QImage(":images/dameT.png"));
            break;
        case 51:
            painter.drawImage(rect,QImage(":images/roiT.png"));
            break;
        default:
            break;
        }
    }
}

void Card::setFace(bool face){
    faceDown=face;
}
