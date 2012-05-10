#include "savedboard.h"

SavedBoard::SavedBoard()
{
    stacks = new Card**[4];
    columns = new Card**[7];
    deck = NULL;
    iLastFaceDownColumns = new int[7];
}

void SavedBoard::saveStack(int iStack, Card * _root)
{
    if (_root != NULL)
    {
        int nCards = _root->getLengthToLeaf() + 1;
        stacks[iStack] = new Card*[nCards];

        for (int i = 0; i < nCards; i++)
        {
            stacks[iStack][i] = _root;
            _root = _root->getNextCard();
        }
    }
    else
    {
        stacks[iStack] = NULL;
    }
}

void SavedBoard::saveColumn(int iColumn, Card * _root)
{
    iLastFaceDownColumns[iColumn] = 0;
    if (_root != NULL)
    {
        int nCards = _root->getLengthToLeaf() + 1;
        columns[iColumn] = new Card*[nCards];

        bool faceDown = true;

        for (int i = 0; i < nCards; i++)
        {
            if (faceDown && !_root->getFace())
            {
                faceDown = false;
                iLastFaceDownColumns[iColumn] = i;
            }

            columns[iColumn][i] = _root;
            _root = _root->getNextCard();
        }
    }
}

void SavedBoard::saveDeck(Card *)
{

}

