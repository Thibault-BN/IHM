#ifndef BOARD_H
#define BOARD_H

#include "column.h"
#include "deck.h"
#include "card.h"

#include <algorithm>
#include <iostream>
#include <QVector>
#include <QWidget>
#include <QPainter>
#include <QPoint>
#include <QImage>
#include <QRect>
#include <QBrush>

using namespace std;

class Board : public QWidget
{
    Q_OBJECT
public:
    Board();
    //~Board();

private:
    Column** columns;
    Deck * deck;
    void fillColumns(QVector<Card*>*);
    void paintEvent(QPaintEvent * e);

public slots:
    void newGame();

};

#endif // BOARD_H
