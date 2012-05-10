#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>

#include "board.h"

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Board* board;
    QAction * actionUndo;

public slots:
    inline void actionPerformed() { this->actionUndo->setEnabled(true); }
};

#endif // MAINWINDOW_H
