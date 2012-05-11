#ifndef BOARD_H
#define BOARD_H

#include "column.h"
#include "deck.h"
#include "card.h"
#include "stack.h"
#include "savedboard.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
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

private:

    //Deal 1 ou deal 3
    static int dealType;

    //Variables contenant les cartes
    Column** columns;
    Stack** stack;
    Deck * deck;

    //De ou provient la carte que l'on veut déplacer
    bool cardIsSelectedFromStack;
    bool cardIsSelectedFromColumn;
    bool cardIsSelectedFromDeck;

    //Création du jeu
    void fillColumns(Card**);
    void randomize(int*);

    //Mise à jour de l'affichage
    void updatePos();
    void paintEvent(QPaintEvent * e);

    //Gestion des événements
    void resizeEvent(QResizeEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);

    //Logique du jeu
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

    //Carte qui se déplace
    Card* currentCard;
    int shiftX;
    int shiftY;
    int lastX;
    int lastY;
    int currCol;
    int currStack;

    //Sauvegarde
    QList<SavedBoard*> savedBoards;
    void saveBoard();

    //Time
    int gameTime;

    //Stats
    int nPlayedGames;
    int nDeal1Games;
    int nDeal3Games;
    int nWonGames;
    int nWonDeal1Games;
    int nWonDeal3Games;
    int totalPLayedTime;

    string fileName;

    void readStatsFile();
    void saveStatsFile();

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
