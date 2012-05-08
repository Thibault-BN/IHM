#include "column.h"

Column::Column()
{
}

void Column::add(QVector<Card *> _stack)
{
    copy(_stack.begin(),cards.end(),back_inserter(cards));
}

string Column::describe()
{
}
