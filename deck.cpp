#include "deck.h"

Deck::Deck()
{
}

Deck::~Deck()
{
    if (cards.empty())
    {
        QVector<Card*>::iterator it;
        for (it = cards.begin(); it != cards.end(); it++)
        {
            delete it;
        }
    }
}

void Deck::fill(QVector<Card*> & _deck)
{
    cards = _deck;
    iCardUp = cards.size() - 1;
}

void Deck::describe()
{
    cout << "Deck " << endl;

    for (QVector<Card*>::iterator it = cards.begin(); it != cards.end(); it++)
    {
        cout << " " << (*it)->getNumber();
    }
    cout << endl;

}

void Deck::deal(int dealType)
{
    iCardUp = (iCardUp - dealType);
}

void Deck::draw(QPainter &painter, int card_width, int card_height, int ecartV, int ecartH){

    QRect rect(ecartV,ecartH,card_width,card_height);
    painter.drawImage(rect,QImage(":images/dos3.png"));
}
