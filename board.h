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
<<<<<<< HEAD

=======
>>>>>>> 5e1366037b6b2a5e7fc2a137c9997bbb0739a21c

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

<<<<<<< HEAD
    void fillColumns(Card**);
=======
    void fillColumns(QVector<Card*>*);
>>>>>>> 5e1366037b6b2a5e7fc2a137c9997bbb0739a21c
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
<<<<<<< HEAD

=======
>>>>>>> 5e1366037b6b2a5e7fc2a137c9997bbb0739a21c

public slots:
    void newGame();

};

#endif // BOARD_H
