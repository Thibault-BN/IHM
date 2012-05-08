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

using namespace std;

class Board : public QWidget
{
public:
    Board();
    ~Board();


private:
    Column * columns;
    Deck * deck;
    void fillColumns(QVector<Card*>*);
    void paintEvent(QPaintEvent * e);
};

#endif // BOARD_H
