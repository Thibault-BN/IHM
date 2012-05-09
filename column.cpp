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

void Column::draw(QPainter &painter) {

    QRect rect(posX,posY,w,h);
    painter.drawRect(rect);

    for (int j=0;j<cards.size();j++) {
        cards[j]->draw(painter);
    }
}
