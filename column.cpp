#include "column.h"

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
