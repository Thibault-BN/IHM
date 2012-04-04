#ifndef COLUMN_H
#define COLUMN_H

#include <vector>

using namespace std;

class Column
{
public:
    Column();

    void add(vector<Card*>);

private:
    vector<Card*> stack;

};

#endif // COLUMN_H
