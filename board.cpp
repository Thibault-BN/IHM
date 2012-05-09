#include "board.h"

Board::Board()
{
    deck = NULL;
    columns = NULL;

    QPalette Pal(palette());
    QColor color(76,164,35,255);
    Pal.setColor(QPalette::Background, color);
    setAutoFillBackground(true);
    setPalette(Pal);
    newGame();
}

void Board::paintEvent(QPaintEvent *e) {
    QWidget::paintEvent(e);
    QPainter painter (this);

    deck->draw(painter,(this->width())/10);

    QRect rect(QPoint(100,100),QPoint(200,200));
    painter.drawImage(rect,QImage(":images/roiP.png"));

}

void Board::newGame()
{
    //Creation des 7 colonnes
    if (columns != NULL)
        delete [] columns;

    this->columns = new Column*[7];
    for (int i = 0; i< 7; i++)
    {
        columns[i] = new Column();
    }


    QVector<Card*> cards;
    for (int i=0; i < 52; i++)
    {
        cards.push_back(new Card(i));
    }
    random_shuffle(cards.begin(),cards.end());

    this->fillColumns(&cards);

    if (deck != NULL)
        delete deck;

    this->deck = new Deck();
    deck->fill(cards);

    deck->describe();
}

void Board::fillColumns(QVector<Card*> *cards)
{

    for (int i = 0; i<7; i++)
    {
        QVector<Card*> pile;

        cout << "Column " << i << endl
             << "    cartes ";

        for (int j=0; j<=i; j++) //1 carte dans la colonne 0, 2 cartes dans la collone 2...
        {
            pile.push_back(cards->back());
            cards->pop_back();
            cout << " " << pile.back()->getNumber();
        }

        cout << endl;
        columns[i]->add(pile);
    }

    cout << "Columns filled" << endl;
}
