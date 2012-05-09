#include "column.h"
#include <iostream>

using namespace std;

Column::Column()
{
}

Column::~Column()
{
    if(!cards.empty())
    {
        QVector<Card*>::iterator it;
        for (it = cards.begin(); it != cards.end(); it++)
        {
            delete it;
        }
    }
}

void Column::add(QVector<Card *> &_stack)
{
    QVector<Card*>::iterator it;

    for(it = _stack.begin(); it != _stack.end(); it++)
    {
        cards.push_back(*it);
    }
}

void Column::describe()
{
}

void Column::draw(QPainter &painter, int card_width, int card_height,int ecartV, int ecartH, int i) {

    int posColX = (i+1)*ecartV+i*card_width;
    int posColY = 2*ecartH+card_height;
    QRect rect(posColX,posColY,card_width,card_height);
    painter.drawRect(rect);

    for (int j=0;j<cards.size();j++) {
        cards[j]->draw(painter,card_width,card_height,posColX,posColY,j);
    }
}
