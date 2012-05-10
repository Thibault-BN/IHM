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
    bool mouseIsPressed;

    void fillColumns(Card**);
    void randomize(int*);
    void paintEvent(QPaintEvent * e);
    void updatePos();
    void resizeEvent(QResizeEvent *);

    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    bool clickOnDeck(int x, int y);
    bool clickOnColumn(int x, int y, int &col, int &card);

    Card* currentCard;
    int shiftX;
    int shiftY;


public slots:
    void newGame();

};

#endif // BOARD_H
