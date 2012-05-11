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
#include <sstream>

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

    //D'ou provient la carte que l'on veut déplacer
    bool cardIsSelectedFromStack;
    bool cardIsSelectedFromColumn;
    bool cardIsSelectedFromDeck;

    //Création du jeu
    void fillColumns(Card**);
    void randomize(int*); //mélange aléatoire d'un tableau d'index

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

    void hasWon();

    Card* currentCard;     //Carte qui se déplace
    int currCol;
    int currStack;

    int shiftX;
    int shiftY;
    int lastX;
    int lastY;


    //Sauvegarde
    //On a une "pile" d'états du board
    QList<SavedBoard*> savedBoards;
    void saveBoard(); //A chaque action (déplacement...), on crée un SavedBoard, qu'on ajoute à la pile

    //Temps de jeu
    int gameTime;

    //Stats
    int nPlayedGames;
    int nDeal1Games;
    int nDeal3Games;
    int nWonGames;
    int nWonDeal1Games;
    int nWonDeal3Games;
    int totalPLayedTime;
    bool firstGame;


    //Sauvegarde du fichier stats de nom fileName
    string fileName;

    void readStatsFile();
    void saveStatsFile();

public slots:
    void newGame();
    void restorePreviousBoard(); //Appelée lors d'un undo
    void restartGame();
    void updateTime(); //appelée chaque seconde
    void autoComplete(); //méthode qui "monte" les cartes dans les stacks automatiquement
    void deal1();
    void deal3();
    void showStats();
    void reiniStats();

signals:
    void boardSaved();
    void savedBoardsEmpty();
    void startTime();
    void stopTime();
    void newTime(int &);

};

#endif // BOARD_H
