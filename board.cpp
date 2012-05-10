#include "board.h"

Board::Board()
{
    deck = NULL;
    columns = NULL;
<<<<<<< HEAD
    stack = NULL;
=======
    mouseIsPressed = false;
>>>>>>> 5e1366037b6b2a5e7fc2a137c9997bbb0739a21c
    setMinimumSize(800,600);
    QPalette Pal(palette());
    QColor color(76,164,35,255);
    Pal.setColor(QPalette::Background, color);
    setAutoFillBackground(true);
    setPalette(Pal);
    newGame();
    cout << "Partie cree" << endl;
}

//Board::~Board()
//{
//    if (columns != NULL) delete [] columns;
//}

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
    if (columns != NULL) {
        delete [] columns;
        cout << "colonnes deleted" << endl;
    }

    this->columns = new Column*[7];
    for (int i = 0; i< 7; i++)
    {
        columns[i] = new Column();
    }

    this->stack = new Stack*[4];
    for (int k=0;k<4;k++) {
        stack[k] = new Stack();
    }

    int tab[52];
    randomize(tab);

    Card * cards = NULL;
    cards = new Card(tab[0], false);
    Card* root = cards;

    for (int i=1; i < 52; i++)
    {
        Card * nextCard = new Card(tab[i], true);
        cards->setNextCard(nextCard);
        nextCard->setPreviousCard(cards);
        cards = nextCard;
    }

    this->fillColumns(&root);

    if (deck != NULL)
        delete deck;

    this->deck = new Deck();
    deck->fill(root);

    deck->describe();

    updatePos();
    update();
}

void Board::fillColumns(Card** root)
{
    Card * pileEnd = *root;

    for (int i = 0; i<7; i++)
    {

        for (int j=0; j<=i; j++) //1 carte dans la colonne 0, 2 cartes dans la collone 2...
        {

            pileEnd = pileEnd->getNextCard();

            if(j==i){
                pileEnd->getPreviousCard()->setFace(false);
            }
        }

        pileEnd->getPreviousCard()->setNextCard(NULL);
        pileEnd->setPreviousCard(NULL);
        columns[i]->add(*root);
        columns[i]->describe();
        *root = pileEnd;
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

        int columnSize = columns[i]->getRootCard()->getLengthToLeaf() + 1;

        for (int j=0; j < columnSize; j++)
        {
            columns[i]->getCardI(j)->setPos((i+1)*ecartV+i*card_width,2*ecartH+card_height+j*10);
            columns[i]->getCardI(j)->setSize(card_width,card_height);
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
<<<<<<< HEAD
        currentCard = columns[numCol]->getCardI(numCard);
=======
        currentCard = columns[numCol]->getCards()[numCard];
>>>>>>> 5e1366037b6b2a5e7fc2a137c9997bbb0739a21c
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
<<<<<<< HEAD
            if (columns[i]->getRootCard()->getLengthToLeaf() + 1 == 0) return false;
            else if (y>columns[i]->getY() && y<(columns[i]->getY()+columns[i]->getH()+(columns[i]->getRootCard()->getLengthToLeaf() +1 -1)*10) ) {
                //On test sur quelle carte on est tombé et si elle est retournée
                for (int j=0; j<(columns[i]->getRootCard()->getLengthToLeaf()+1-1);j++) {
                    if (y>(columns[i]->getY()+j*10) && y<(columns[i]->getY()+(j+1)*10)) {
                        //C'est la carte j qui est cliquée
                        if (columns[i]->getCardI(j)->getFace()) return false;
=======
            if (columns[i]->getCards().size()==0) return false;
            else if (y>columns[i]->getY() && y<(columns[i]->getY()+columns[i]->getH()+(columns[i]->getCards().size()-1)*10) ) {
                //On test sur quelle carte on est tombé et si elle est retournée
                for (int j=0; j<(columns[i]->getCards().size()-1);j++) {
                    if (y>(columns[i]->getY()+j*10) && y<(columns[i]->getY()+(j+1)*10)) {
                        //C'est la carte j qui est cliquée
                        if (columns[i]->getCards()[j]->getFace()) return false;
>>>>>>> 5e1366037b6b2a5e7fc2a137c9997bbb0739a21c
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
<<<<<<< HEAD
                card = columns[i]->getRootCard()->getLengthToLeaf()+1-1;
=======
                card = columns[i]->getCards().size()-1;
>>>>>>> 5e1366037b6b2a5e7fc2a137c9997bbb0739a21c
                shiftX = x-columns[i]->getX();
                shiftY = y-columns[i]->getY()-card*10;
                return true;
            }
            return false;
        }
    }
    return false;
}
<<<<<<< HEAD

=======
>>>>>>> 5e1366037b6b2a5e7fc2a137c9997bbb0739a21c
