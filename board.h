#ifndef BOARD_H
#define BOARD_H
#include "column.h"
#include "deck.h"
#include "card.h"
#include "stack.h"
#include "savedboard.h"

#include <algorithm>
#include <iostream>
#include <QList>
#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QPoint>
#include <QImage>
#include <QRect>
#include <QBrush>
#include <QTime>
#include <QMouseEvent>
#include <QMainWindow>
#include <QMessageBox>

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
    bool cardIsSelectedFromDeck;

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
    bool clickOnReverseDeck(int x, int y);
    bool clickOnColumn(int x, int y, int &col, int &card);
    bool clickOnStack(int x, int y, int &numStack);

    bool releaseOnColumn(int x, int y);
    bool releaseOnStack(int x, int y);

    bool movePossible(int lastCard, int newCard);
    bool moveOnStackPossible(int lastCard, int newCard);

    bool autoCompleteB();

    void gagne();

    Card* currentCard;
    int shiftX;
    int shiftY;
    int lastX;
    int lastY;
    int currCol;
    int currStack;
    static int dealType;

    //Sauvegarde
    QList<SavedBoard*> savedBoards;
    void saveBoard();

    //Time
    int gameTime;

public slots:
    void newGame();
    void restorePreviousBoard();
    void restartGame();
    void updateTime();
    void autoComplete();
    void deal1();
    void deal3();

signals:
    void boardSaved();
    void savedBoardsEmpty();
    void startTime();
    void stopTime();
    void newTime(int &);

};

#endif // BOARD_H
