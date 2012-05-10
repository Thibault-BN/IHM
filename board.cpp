#include "board.h"

#define ECART_CARTE 25

Board::Board()
{
    deck = NULL;
    columns = NULL;
    stack = NULL;
    cardIsSelectedFromStack = false;
    cardIsSelectedFromColumn = false;
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
    if (cardIsSelectedFromStack || cardIsSelectedFromColumn) {
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
    deck->setIndex(-1);

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
    deck->setEcart(ecartV+card_width);
    Card* cardD = deck->getRootCard();
    while(cardD!= NULL) {
        cardD->setPos(ecartV,ecartH);
        cardD->setSize(card_width,card_height);
        cardD->setFace(true);
        cardD = cardD->getNextCard();
    }
    if (deck->getIndex() != -1){
        deck->getCardI(deck->getIndex())->setPos(2*ecartV+card_width,ecartH);
        deck->getCardI(deck->getIndex())->setFace(false);
    }

    for (int i = 0; i<7;i++) {
        columns[i]->setPos((i+1)*ecartV+i*card_width,2*ecartH+card_height);
        columns[i]->setSize(card_width,card_height);

        int columnSize = columns[i]->getSize();

        for (int j=0; j < columnSize; j++)
        {
            columns[i]->getCardI(j)->setPos((i+1)*ecartV+i*card_width,2*ecartH+card_height+j*25);
            columns[i]->getCardI(j)->setSize(card_width,card_height);
        }

    }
    for (int k=0;k<4;k++) {
        stack[k]->setPos((k+4)*ecartV+(k+3)*card_width,ecartH);
        stack[k]->setSize(card_width,card_height);
        Card* card = stack[k]->getRootCard();
        while(card!= NULL) {
            card->setPos((k+4)*ecartV+(k+3)*card_width,ecartH);
            card->setSize(card_width,card_height);
            card = card->getNextCard();
        }
    }
}

void Board::resizeEvent(QResizeEvent *) {
    updatePos();
    update();
}

void Board::mousePressEvent(QMouseEvent * e) {

    int numCol;
    int numCard;
    int numStack;
    if (clickOnDeck(e->x(),e->y())) {
        saveBoard();

        //Selon deal 1 ou deal 3?
        deck->deal(1);
        updatePos();
        update();
    }
    else if (clickOnColumn(e->x(),e->y(),numCol,numCard)){

        if(numCard!=52) {
            currentCard = columns[numCol]->getCardI(numCard);
            lastX = currentCard->getX();
            lastY = currentCard->getY();
            currCol = numCol;
            cardIsSelectedFromColumn = true;
        }
    }
    else if (clickOnStack(e->x(),e->y(),numStack)) {
        if (stack[numStack]->getRootCard() != NULL) {
            currentCard = stack[numStack]->getRootCard()->getLeaf();
            lastX = currentCard->getX();
            lastY = currentCard->getY();
            currStack = numStack;
            cardIsSelectedFromStack = true;
        }
    }
}

void Board::mouseDoubleClickEvent(QMouseEvent *e){
    int numCol;
    int numCard;

    if (clickOnColumn(e->x(),e->y(),numCol,numCard)) {
        if (numCard!=52) {
            Card* card = columns[numCol]->getCardI(numCard);
            if (card->getNextCard()==NULL) {
                for (int i=0;i<4;i++) {
                    int numCardInStack = 52;
                    if (stack[i]->getRootCard()!=NULL) numCardInStack = stack[i]->getRootCard()->getLeaf()->getNumber();
                    if (moveOnStackPossible(card->getNumber(),numCardInStack)) {
                        saveBoard();

                        //Move
                        if(card->getPreviousCard()!=NULL) {
                            card->getPreviousCard()->setNextCard(NULL);
                            card->getPreviousCard()->setFace(false);
                            card->setPreviousCard(NULL);

                        }
                        else {
                            columns[numCol]->setRootCard(NULL);
                        }
                        stack[i]->addCard(currentCard);
                        updatePos();
                        update();
                        break;
                    }
                }
            }
        }
    }
}

void Board::mouseReleaseEvent(QMouseEvent *e) {
    if(cardIsSelectedFromStack || cardIsSelectedFromColumn) {
        if (!releaseOnColumn(e->x(),e->y())) {
            releaseOnStack(e->x(),e->y());
        }
        cardIsSelectedFromStack=false;
        cardIsSelectedFromColumn = false;
        update();
    }
}

bool Board::releaseOnColumn(int x, int y) {
    int numCol;
    int numCard;
    if (clickOnColumn(x,y,numCol,numCard)) {
        int newCardNum = 52;
        if (numCard!=52) {
            newCardNum = columns[numCol]->getCardI(numCard)->getNumber();
        }
        if (movePossible(currentCard->getNumber(),newCardNum)) {
            saveBoard();

            //Alors on move la carte
            if(currentCard->getPreviousCard()!=NULL) {
                currentCard->getPreviousCard()->setNextCard(NULL);
                currentCard->getPreviousCard()->setFace(false);
                currentCard->setPreviousCard(NULL);

            }
            else {
                if (cardIsSelectedFromColumn) {
                    columns[currCol]->setRootCard(NULL);
                }
                if (cardIsSelectedFromStack) {
                    stack[currStack]->setRootCard(NULL);
                }
            }
            columns[numCol]->add(currentCard);
            updatePos();
            return true;
        }
        else {
            Card* card = currentCard;
            int j=0;
            while(card!=NULL) {
                card->setPos(lastX,lastY+j*ECART_CARTE);
                j++;
                card = card->getNextCard();
            }
        }

    }
    else {
        Card* card = currentCard;
        int j=0;
        while(card!=NULL) {
            card->setPos(lastX,lastY+j*ECART_CARTE);
            j++;
            card = card->getNextCard();
        }
    }
    return false;
}

void Board::releaseOnStack(int x, int y) {
    int numStack;
    //Si on bouge plus d'une carte, on ne peut déjà pas lacher sur un stack

    if (currentCard->getNextCard()==NULL && clickOnStack(x,y,numStack)) {
        int numCard;
        if(stack[numStack]->getRootCard()==NULL) {
            numCard=52;
        }
        else {
            numCard = stack[numStack]->getRootCard()->getLeaf()->getNumber();
        }

        if (moveOnStackPossible(currentCard->getNumber(),numCard)) {
            saveBoard();

            //Alors on bouge
            if(currentCard->getPreviousCard()!=NULL) {
                currentCard->getPreviousCard()->setNextCard(NULL);
                currentCard->getPreviousCard()->setFace(false);
                currentCard->setPreviousCard(NULL);

            }
            else {
                if (cardIsSelectedFromColumn) {
                    columns[currCol]->setRootCard(NULL);
                }
                if (cardIsSelectedFromStack) {
                    stack[currStack]->setRootCard(NULL);
                }
            }
            stack[numStack]->addCard(currentCard);
            updatePos();
        }
        else {
            currentCard->setPos(lastX,lastY);
        }

    }
    else {
        currentCard->setPos(lastX,lastY);
    }
}

void Board::mouseMoveEvent(QMouseEvent *e) {
    if (cardIsSelectedFromStack || cardIsSelectedFromColumn) {
        //On bouge la carte courante et les suivantes
        Card* card = currentCard;
        int j=0;
        while(card!=NULL) {
            card->setPos(e->x()-shiftX,e->y()-shiftY+j*ECART_CARTE);
            j++;
            card = card->getNextCard();
        }
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

            if (columns[i]->getRootCard()==NULL){
                if(y>columns[i]->getY() && y<(columns[i]->getY()+columns[i]->getH())) {
                    card = 52;
                    col = i;
                    return true;
                }
                else return false;
            }

            if (y>columns[i]->getY() && y<(columns[i]->getY()+columns[i]->getH()+(columns[i]->getRootCard()->getLengthToLeaf() +1 -1)*25) ) {
                //On test sur quelle carte on est tombé et si elle est retournée
                //S'il n'y a pas de carte, on renvoie 52 en num Card

                for (int j=0; j<(columns[i]->getRootCard()->getLengthToLeaf()+1-1);j++) {
                    if (y>(columns[i]->getY()+j*25) && y<(columns[i]->getY()+(j+1)*25)) {
                        //C'est la carte j qui est cliquée
                        if (columns[i]->getCardI(j)->getFace()) return false;
                        else {
                            col = i;
                            card = j;
                            shiftX = x-columns[i]->getX();
                            shiftY = y-columns[i]->getY()-j*25;
                            return true;
                        }
                    }
                }
                //C'est la carte du dessus qui est cliquée
                col = i;
                card = columns[i]->getRootCard()->getLengthToLeaf()+1-1;
                shiftX = x-columns[i]->getX();
                shiftY = y-columns[i]->getY()-card*25;
                return true;
            }
            return false;
        }
    }
    return false;
}

bool Board::clickOnStack(int x, int y, int &numStack){
    for (int i = 0; i<4; i++) {
        if ( x>stack[i]->getX() && x<(stack[i]->getX()+stack[i]->getW()) ) {
            if( y>stack[i]->getY() && y<(stack[i]->getY()+stack[i]->getH()) ) {
                numStack = i;
                shiftX = x-stack[i]->getX();
                shiftY = y-stack[i]->getY();
                return true;
            }
        }
    }
    return false;
}

bool Board::movePossible(int lastCard, int newCard) {
    switch(lastCard){

    case 0:
    case 39:
        if (newCard==14||newCard==27) return true;
        break;
    case 1:
    case 40:
        if (newCard==15||newCard==28) return true;
        break;
    case 2:
    case 41:
        if (newCard==16||newCard==29) return true;
        break;
    case 3:
    case 42:
        if (newCard==17||newCard==30) return true;
        break;
    case 4:
    case 43:
        if (newCard==18||newCard==31) return true;
        break;
    case 5:
    case 44:
        if (newCard==19||newCard==32) return true;
        break;
    case 6:
    case 45:
        if (newCard==20||newCard==33) return true;
        break;
    case 7:
    case 46:
        if (newCard==21||newCard==34) return true;
        break;
    case 8:
    case 47:
        if (newCard==22||newCard==35) return true;
        break;
    case 9:
    case 48:
        if (newCard==23||newCard==36) return true;
        break;
    case 10:
    case 49:
        if (newCard==24||newCard==37) return true;
        break;
    case 11:
    case 50:
        if (newCard==25||newCard==38) return true;
        break;

    case 13:
    case 26:
        if (newCard==1||newCard==40) return true;
        break;
    case 14:
    case 27:
        if (newCard==2||newCard==41) return true;
        break;
    case 15:
    case 28:
        if (newCard==3||newCard==42) return true;
        break;
    case 16:
    case 29:
        if (newCard==4||newCard==43) return true;
        break;
    case 17:
    case 30:
        if (newCard==5||newCard==44) return true;
        break;
    case 18:
    case 31:
        if (newCard==6||newCard==45) return true;
        break;
    case 19:
    case 32:
        if (newCard==7||newCard==46) return true;
        break;
    case 20:
    case 33:
        if (newCard==8||newCard==47) return true;
        break;
    case 21:
    case 34:
        if (newCard==9||newCard==48) return true;
        break;
    case 22:
    case 35:
        if (newCard==10||newCard==49) return true;
        break;
    case 23:
    case 36:
        if (newCard==11||newCard==50) return true;
        break;
    case 24:
    case 37:
        if (newCard==12||newCard==51) return true;
        break;
    case 12:
    case 25:
    case 38:
    case 51:
        if (newCard==52) return true;
        break;
    default:
        return false;
    }
    return false;
}

bool Board::moveOnStackPossible(int lastCard, int newCard) {
    if (lastCard==(newCard+1)) return true;
    if ((lastCard==0 || lastCard==13 || lastCard==26 || lastCard==39) && newCard==52) return true;
    return false;
}

void Board::saveBoard()
{
    SavedBoard * board = new SavedBoard();

    for (int i = 0; i < 4; i++)
    {
        board->saveStack(i,stack[i]->getRootCard());
    }

    for (int i = 0; i  < 7; i++)
    {
        board->saveColumn(i, columns[i]->getRootCard());
    }

    board->saveDeck(deck->getRootCard(),deck->getIndex());

    savedBoards.push_back(board);

    cout << "SavedBoars taille " << savedBoards.size() << endl;

    //Rajouter le temps

    emit boardSaved();
}

void Board::restorePreviousBoard()
{
    cout << "Restoring board ......" << endl;
    if (savedBoards.isEmpty() == true)
    {
    }
    else
    {
        SavedBoard* board = savedBoards.back();

        //Colonnes
        for (int iColumn = 0; iColumn < 7; iColumn++)
        {
            int nCards = board->getNCardsColumns()[iColumn];

            cout << "Restoring Column ...... "<< iColumn << "/" << nCards << endl;
            if (nCards > 0)
            {
                Card * root = board->getColumns()[iColumn][0];
                root->setPreviousCard(NULL);
                columns[iColumn]->setRootCard(root);

                Card * card = root;

                for (int i = 1; i < nCards; i++)
                {
                    cout << " " << card->getNumber();
                    card = board->getColumns()[iColumn][i];

                    card->setPreviousCard(board->getColumns()[iColumn][i-1]);
                    card->getPreviousCard()->setNextCard(card);

                    if (i-1 <= board->getILastFaceDownColumns()[iColumn])
                    {
                        card->getPreviousCard()->setFace(true);
                    }
                    else
                    {
                        card->getPreviousCard()->setFace(true);
                    }
                }
                card->setNextCard(NULL);
                cout << " " << card->getNumber() << endl;

            }
            else
            {
                columns[iColumn]->setRootCard(NULL);
            }
        }

        //Stacks
        for (int iStack = 0; iStack  < 4; iStack++)
        {
            int nCards = board->getNCardsStacks()[iStack];
            if (nCards > 0)
            {
                Card * root = board->getStacks()[iStack][0];
                root->setPreviousCard(NULL);
                stack[iStack]->setRootCard(root);

                Card * card = root;
                for (int i = 1; i < nCards; i++)
                {
                    card = board->getStacks()[iStack][i];
                    card->setPreviousCard(board->getStacks()[iStack][i-1]);
                    card->getPreviousCard()->setNextCard(card);
                    card->setFace(false);
                }
                card->setNextCard(NULL);
            }
            else
            {
                stack[iStack]->setRootCard(NULL);
            }
        }

        //Deck
        if(true)
        {
            int nCards = board->getNCardsDeck();
            if (nCards > 0)
            {
                Card * root = board->getDeck()[0];
                root->setPreviousCard(NULL);
                deck->setRootCard(root);

                Card * card = NULL;
                for (int i = 1; i < nCards; i++)
                {
                    card = board->getDeck()[i];
                    card->setPreviousCard(board->getDeck()[i-1]);
                    card->getPreviousCard()->setNextCard(card);
                    if (i == board->getICardUpDeck()) card->setFace(false);
                    else card->setFace(true);
                }
                card->setNextCard(NULL);
            }
            else
            {
                deck->setRootCard(NULL);
            }
        }

        cout << "Size savedBoards " << savedBoards.size();
        savedBoards.removeLast();
        cout << " " << savedBoards.size() << endl;

        updatePos();
        update();
    }

}
