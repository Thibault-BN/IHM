#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setMinimumSize(800,500);

    Board * board = new Board();
}

MainWindow::~MainWindow()
{
}
