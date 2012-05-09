#include "board.h"

Board::Board()
{
    deck = NULL;
    columns = NULL;
    mouseIsPressed = false;
    setMinimumSize(800,600);
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

    deck->draw(painter);
    for (int i = 0; i<7;i++) {
        columns[i]->draw(painter);
    }
    for (int k=0;k<4;k++){
        stack[k]->draw(painter);
    }
    if (mouseIsPressed) {
        //On redessine la dernière carte pour qu'elle soit au dessus
        currentCard->draw(painter);
    }
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

    this->stack = new Stack*[4];
    for (int k=0;k<4;k++) {
        stack[k] = new Stack();
    }

    QVector<Card*> cards;
    int tab[52];

    randomize(tab);

    for (int i=0; i < 52; i++)
    {
        cards.push_back(new Card(tab[i],true));
    }

    this->fillColumns(&cards);

    if (deck != NULL)
        delete deck;

    this->deck = new Deck();
    deck->fill(cards);

    deck->describe();

    updatePos();
    update();
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
            if(j==i){
                cards->back()->setFace(false);
            }
            pile.push_back(cards->back());
            cards->pop_back();
            cout << " " << pile.back()->getNumber();
        }

        cout << endl;
        columns[i]->add(pile);
    }

    cout << "Columns filled" << endl;
}

void Board::randomize(int tab[])
{
    srand(time(NULL));
    for (int i=0; i<52; i++)
    {
        tab[i] = -1;
    }

    for (int i=0; i<52; i++)
    {
        int position = rand() % (52-i);

        int idNotFilled = -1;
        for (int j = 0; j<52; j++)
        {
            if (tab[j] == -1) idNotFilled++;
            if (idNotFilled == position)
            {
                tab[j] = i;
                break;
            }
        }
    }

}

void Board::updatePos(){

    int card_height = 0.19*this->height();
    int card_width = 0.67*card_height;
    int ecartV = (width()-(7*card_width))/8;
    int ecartH = 30;

    deck->setPos(ecartV,ecartH);
    deck->setSize(card_width,card_height);
    for (int i = 0; i<7;i++) {
        columns[i]->setPos((i+1)*ecartV+i*card_width,2*ecartH+card_height);
        columns[i]->setSize(card_width,card_height);
        for (int j=0;j<columns[i]->getCards().size();j++) {
            columns[i]->getCards()[j]->setPos((i+1)*ecartV+i*card_width,2*ecartH+card_height+j*10);
            columns[i]->getCards()[j]->setSize(card_width,card_height);
        }
    }
    for (int k=0;k<4;k++) {
        stack[k]->setPos((k+4)*ecartV+(k+3)*card_width,ecartH);
        stack[k]->setSize(card_width,card_height);
    }
}

void Board::resizeEvent(QResizeEvent *) {
    updatePos();
    update();
}

void Board::mousePressEvent(QMouseEvent * e) {

    int numCol;
    int numCard;
    if (clickOnDeck(e->x(),e->y())) {
        cout<<"on deck!"<<endl;
    }
    else if (clickOnColumn(e->x(),e->y(),numCol,numCard)){
        cout<<"Col : "<<numCol<<" card : "<< numCard<<endl;
        currentCard = columns[numCol]->getCards()[numCard];
        mouseIsPressed = true;
    }
}

void Board::mouseReleaseEvent(QMouseEvent *e) {
    mouseIsPressed = false;
}

void Board::mouseMoveEvent(QMouseEvent *e) {
    if (mouseIsPressed) {
        //On bouge la carte courante
        currentCard->setPos(e->x()-shiftX,e->y()-shiftY);
        update();
    }
}

bool Board::clickOnDeck(int x, int y) {

    if (x>deck->getX() && x<(deck->getX()+deck->getW()) && y>deck->getY() && y<(deck->getY()+deck->getH()))
        return true;
    return false;
}

bool Board::clickOnColumn(int x, int y, int &col, int &card) {
    //On teste d'abord par la largeur
    for (int i = 0; i<7; i++) {
        if ( x>columns[i]->getX() && x<(columns[i]->getX()+columns[i]->getW()) ) {
            //On teste ensuite sur la hauteur
            if (columns[i]->getCards().size()==0) return false;
            else if (y>columns[i]->getY() && y<(columns[i]->getY()+columns[i]->getH()+(columns[i]->getCards().size()-1)*10) ) {
                //On test sur quelle carte on est tombé et si elle est retournée
                for (int j=0; j<(columns[i]->getCards().size()-1);j++) {
                    if (y>(columns[i]->getY()+j*10) && y<(columns[i]->getY()+(j+1)*10)) {
                        //C'est la carte j qui est cliquée
                        if (columns[i]->getCards()[j]->getFace()) return false;
                        else {
                            col = i;
                            card = j;
                            shiftX = x-columns[i]->getX();
                            shiftY = y-columns[i]->getY()+j*10;
                            return true;
                        }
                    }
                }
                //C'est la carte du dessus qui est cliquée
                col = i;
                card = columns[i]->getCards().size()-1;
                shiftX = x-columns[i]->getX();
                shiftY = y-columns[i]->getY()-card*10;
                return true;
            }
            return false;
        }
    }
    return false;
}
