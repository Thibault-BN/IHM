#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setMinimumSize(800,500);

    board = new Board(this);

    QAction * actionNewGame = new QAction(tr("&Nouvelle partie"),this); //QIcon(":/Images/Icones/")
    actionNewGame->setShortcut(tr("Ctrl+N"));
    connect(actionNewGame, SIGNAL(triggered()), board, SLOT(newGame()));

    QAction * actionQuit = new QAction(tr("&Quitter"),this);
    actionQuit->setShortcut(tr("Ctrl+Q"));
    connect(actionQuit,SIGNAL(triggered()),this,SLOT(close()));

    QAction * actionRestart = new QAction(tr("&Recommencer partie"),this);

    //Menus déroulants
    QMenuBar* menubar = menuBar();
    QMenu * fileMenu = menubar->addMenu(tr("&Fichier"));
    fileMenu->addAction(actionNewGame);
    fileMenu->addAction(actionQuit);

    //Tool Bar
    QToolBar* toolBar = addToolBar("Fichier");
    toolBar->addAction(actionNewGame);

    this->setCentralWidget(board);
}

MainWindow::~MainWindow()
{
    if (board != NULL)
        delete board;
}
