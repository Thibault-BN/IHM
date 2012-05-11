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


public slots:
    inline void actionPerformed() { this->actionUndo->setEnabled(true); this->actionRestart->setEnabled(true); }
    inline void noMoreSavedBoards() {this->actionUndo->setEnabled(false); this->actionRestart->setEnabled(false);}
    void updateTimer(int &);
    inline void startTimer() {this->timer->start(1000);}
    inline void stopTimer() {this->timer->stop();}

signals:


};

#endif // MAINWINDOW_H
