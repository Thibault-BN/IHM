#include "column.h"

Column::Column()
{
}

void Column::add(vector<Card *> _stack)
{
    copy(_stack.begin(),cards.end(),back_inserter(cards));
}

string Column::describe()
{
}
