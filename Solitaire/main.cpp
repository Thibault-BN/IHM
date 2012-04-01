#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setStyleSheet("background-image: url(:images/grass.png);"
                    "background-position: top left;"
                    );
    w.show();
    
    return a.exec();
}
