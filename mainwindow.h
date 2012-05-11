#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QAction>
#include <QTimer>
#include <QTime>
#include <QString>

#include "board.h"

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    QTimer * timer;
    Board* board;
    QStatusBar * st;
    QAction * actionUndo;
    QAction * actionRestart;
    QAction * deal1;
    QAction * deal3;


public slots:
    inline void actionPerformed() { this->actionUndo->setEnabled(true); this->actionRestart->setEnabled(true); }
    inline void noMoreSavedBoards() {this->actionUndo->setEnabled(false); this->actionRestart->setEnabled(false);}
    inline void setDeal1() { deal1->setEnabled(true); deal3->setEnabled(false);}
    inline void setDeal3() { deal1->setEnabled(false);deal3->setEnabled(true);}
    void updateTimer(int &);
    inline void startTimer() {this->timer->start(1000);}
    inline void stopTimer() {this->timer->stop();}

signals:


};

#endif // MAINWINDOW_H
