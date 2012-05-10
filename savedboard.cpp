#include "savedboard.h"

SavedBoard::SavedBoard()
{
    stacks = new Card**[4];
    nCardsStacks = new int[4];

    columns = new Card**[7];
    nCardsColumns = new int[7];

    deck = NULL;
    iCardUpDeck = -1;
    iLastFaceDownColumns = new int[7];
}

void SavedBoard::saveStack(int iStack, Card * _root)
{
    cout << "Stack " << iStack << endl;

    if (_root != NULL)
    {
        int nCards = _root->getLengthToLeaf() + 1;
        stacks[iStack] = new Card*[nCards];

        for (int i = 0; i < nCards; i++)
        {
            cout << _root->getNumber() << " ";
            stacks[iStack][i] = _root;
            _root = _root->getNextCard();
        }
        nCardsStacks[iStack] = nCards;
        cout << endl;
    }
    else
    {
        stacks[iStack] = NULL;
        nCardsStacks[iStack] = 0;
    }
}

void SavedBoard::saveColumn(int iColumn, Card * _root)
{
    cout << "Column " << iColumn << endl;
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
                iLastFaceDownColumns[iColumn] = i-1;
            }

            cout << _root->getNumber() << "(" << faceDown << ") ";
            columns[iColumn][i] = _root;
            _root = _root->getNextCard();
        }

        cout << endl;

        nCardsColumns[iColumn] = nCards;
    }
    else
    {
        columns[iColumn] = NULL;
        nCardsColumns[iColumn] = 0;
    }
}

void SavedBoard::saveDeck(Card * _root, int _iCardUp)
{
    if (_root != NULL)
    {
        int nCards = _root->getLengthToLeaf() + 1;
        deck = new Card*[nCards];
        iCardUpDeck = _iCardUp;

        for (int i = 0; i < nCards; i++)
        {
            deck[i] = _root;
            _root = _root->getNextCard();
        }
        nCardsDeck = nCards;
    }
    else
    {
        deck = NULL;
        nCardsDeck = 0;
    }

}

