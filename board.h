#ifndef BOARD_H
#define BOARD_H
#include "column.h"
#include "deck.h"
#include "card.h"
#include "stack.h"

#include <algorithm>
#include <iostream>
#include <QVector>
#include <QWidget>
#include <QPainter>
#include <QPoint>
#include <QImage>
#include <QRect>
#include <QBrush>
#include <QMouseEvent>
#include <QMainWindow>

using namespace std;

class Board : public QWidget
{
    Q_OBJECT
public:
    Board();
    //    ~Board();

private:
    Column** columns;
    Stack** stack;
    Deck * deck;
    bool cardIsSelectedFromStack;
    bool cardIsSelectedFromColumn;

    void fillColumns(Card**);
    void randomize(int*);
    void paintEvent(QPaintEvent * e);
    void updatePos();
    void resizeEvent(QResizeEvent *);

    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);

    bool clickOnDeck(int x, int y);
    bool clickOnColumn(int x, int y, int &col, int &card);
    bool clickOnStack(int x, int y, int &numStack);

    bool releaseOnColumn(int x, int y);
    void releaseOnStack(int x, int y);

    bool movePossible(int lastCard, int newCard);
    bool moveOnStackPossible(int lastCard, int newCard);

    Card* currentCard;
    int shiftX;
    int shiftY;
    int lastX;
    int lastY;
    int currCol;
    int currStack;

public slots:
    void newGame();

};

#endif // BOARD_H
