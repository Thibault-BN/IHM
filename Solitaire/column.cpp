#include "column.h"

Column::Column()
{
}

Column::add(vector<Card *> _stack)
{
    copy(_stack.begin(),stack.end(),back_inserter(stack));
}
