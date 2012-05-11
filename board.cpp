#include "board.h"

#define ECART_CARTE 25

int Board::dealType =3;

Board::Board()
{
    deck = NULL;
    columns = NULL;
    stack = NULL;

    cardIsSelectedFromStack = false;
    cardIsSelectedFromColumn = false;
    cardIsSelectedFromDeck = false;

    setMinimumSize(800,500);
    QPalette Pal(palette());
    QColor color(76,164,35,255);
    Pal.setColor(QPalette::Background, color);
    setAutoFillBackground(true);
    setPalette(Pal);

    fileName = "stats";
    readStatsFile();
}

void Board::paintEvent(QPaintEvent *e) {
    QWidget::paintEvent(e);
    QPainter painter (this);

    deck->draw(painter,dealType);
    for (int i = 0; i<7;i++) {
        columns[i]->draw(painter);
    }
    for (int k=0;k<4;k++){
        stack[k]->draw(painter);
    }
    if (cardIsSelectedFromStack || cardIsSelectedFromColumn || cardIsSelectedFromDeck) {
        //On redessine la dernière carte pour qu'elle soit au dessus
        currentCard->draw(painter);
    }
}

void Board::newGame()
{
    if (gameTime != 0)
    {
        totalPLayedTime += gameTime;
    }

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

    //Création des 4 stacks vides
    this->stack = new Stack*[4];
    for (int k=0;k<4;k++) {
        stack[k] = new Stack();
    }

    //On réparti aléatoirement les cartes
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

    updatePos();
    update();

    //Lancement du timer
    gameTime = 0;
    emit startTime();
    emit newTime(gameTime);
    emit savedBoardsEmpty();

    //Mise à jour des stats
    nPlayedGames++;
    if (dealType == 1) nDeal1Games++;
    else nDeal3Games++;

    saveStatsFile();
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

//Mise à jour des positions réelles pour l'affichage
void Board::updatePos(){

    //On calcule la taille et l'écart des cartes en fonction de la taille de l'écran
    int card_height = (this->height()-210)/3;
    int card_width = 0.67*card_height;
    int ecartV = (width()-(7*card_width))/8;
    int ecartH = 30;

    //On met à jour d'abord le deck et les cartes retournées
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
    if (dealType==1) {
        if (deck->getIndex() != -1){
            deck->getCardI(deck->getIndex())->setPos(2*ecartV+card_width,ecartH);
            deck->getCardI(deck->getIndex())->setFace(false);
            if (deck->getIndex() > 0) {
                deck->getCardI(deck->getIndex()-1)->setPos(2*ecartV+card_width,ecartH);
                deck->getCardI(deck->getIndex()-1)->setFace(false);
            }
        }
    }
    else if (dealType==3){
        if (deck->getIndex()<2) {
            for (int i=0;i<=deck->getIndex();i++) {
                deck->getCardI(i)->setPos(2*ecartV+card_width+i*15,ecartH);
                deck->getCardI(i)->setFace(false);
            }
        }
        else {
            for (int j=0; j<3; j++) {
                deck->getCardI(deck->getIndex()-2+j)->setPos(2*ecartV+card_width+j*15,ecartH);
                deck->getCardI(deck->getIndex()-2+j)->setFace(false);
            }
        }
    }

    //On met ensuite à jour les colonnes
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

    //Et enfin on met à jour les stacks
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
    //On recalcule la taille des cartes quand on resize l'écran
    updatePos();
    update();
}

void Board::mousePressEvent(QMouseEvent * e) {

    int numCol;
    int numCard;
    int numStack;

    //On regarde si on a cliqué sur une carte disponible
    //Si c'est le cas, elle devient la carte courante

    //Si on clique sur le deck face caché on deal
    if (clickOnDeck(e->x(),e->y())) {
        saveBoard();

        //Selon deal 1 ou deal 3?
        deck->deal(dealType);
        updatePos();
        update();
    }
    //Sinon on regarde sur le deck retourné
    else if (clickOnReverseDeck(e->x(),e->y())) {
        currentCard = deck->getCardI(deck->getIndex());
        lastX = currentCard->getX();
        lastY = currentCard->getY();
        cardIsSelectedFromDeck = true;
    }
    //Ensuite on regarde sur les cartes retournées des colonnes
    else if (clickOnColumn(e->x(),e->y(),numCol,numCard)){

        //numCard=52 correspond au cas où la colonne est vide
        if(numCard!=52) {
            currentCard = columns[numCol]->getCardI(numCard);
            lastX = currentCard->getX();
            lastY = currentCard->getY();
            currCol = numCol;
            cardIsSelectedFromColumn = true;
        }
    }
    //On peut aussi déplacer les cartes de la pile
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

/*
  Quand on double clique, on regarde si on est sur une carte
  et si celle-ci peut être déplacée sur la pile
  */
void Board::mouseDoubleClickEvent(QMouseEvent *e){
    int numCol;
    int numCard;

    //Si c'est une carte des colonnes
    if (clickOnColumn(e->x(),e->y(),numCol,numCard)) {
        if (numCard!=52) {

            Card* card = columns[numCol]->getCardI(numCard);

            //Il faut que ce soit une carte retournée et sans carte suivante
            if (card->getNextCard()==NULL) {
                //On regarde s'il y a un stack où on peut déplacer la carte
                for (int i=0;i<4;i++) {

                    int numCardInStack = 52;
                    if (stack[i]->getRootCard()!=NULL) numCardInStack = stack[i]->getRootCard()->getLeaf()->getNumber();

                    if (moveOnStackPossible(card->getNumber(),numCardInStack)) {
                        //On sauvegarde l'état vu que le déplacement va être effectué
                        saveBoard();

                        //Move et Maj des liens entre cartes
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

                        //On vérifie toujours si l'on a gagné en ajoutant une carte sur une pile
                        gagne();
                        break;
                    }
                }
            }
        }
    }
    //Si c'est une carte du deck
    else if (clickOnReverseDeck(e->x(),e->y())) {

        Card* card = deck->getCardI(deck->getIndex());

        //Parcours des piles
        for (int i=0;i<4;i++) {

            int numCardInStack = 52;
            if (stack[i]->getRootCard()!=NULL) numCardInStack = stack[i]->getRootCard()->getLeaf()->getNumber();

            if (moveOnStackPossible(card->getNumber(),numCardInStack)) {
                //On sauvegarde puisqu'on peut bouger
                saveBoard();

                //Move et Maj des liens entre cartes
                if (card->getPreviousCard()==NULL) {
                    deck->setRootCard(card->getNextCard());
                    if(card->getNextCard()!=NULL) card->getNextCard()->setPreviousCard(NULL);
                    card->setNextCard(NULL);
                }
                else if (card->getNextCard()==NULL){
                    card->getPreviousCard()->setNextCard(NULL);
                    card->setPreviousCard(NULL);
                }
                else {
                    card->getPreviousCard()->setNextCard(card->getNextCard());
                    card->getNextCard()->setPreviousCard(card->getPreviousCard());
                    card->setPreviousCard(NULL);
                    card->setNextCard(NULL);
                }
                deck->setIndex(deck->getIndex()-1);
                stack[i]->addCard(currentCard);

                updatePos();
                update();
                gagne();
                break;
            }
        }
    }
}

void Board::mouseReleaseEvent(QMouseEvent *e) {
    //Si on relache, on vérifie si on peut l'ajouter à l'endroit où l'on a laché
    if(cardIsSelectedFromStack || cardIsSelectedFromColumn || cardIsSelectedFromDeck) {
        if (!releaseOnColumn(e->x(),e->y())) {
            if (releaseOnStack(e->x(),e->y())) {
                gagne();
            }
        }
        cardIsSelectedFromStack=false;
        cardIsSelectedFromColumn = false;
        cardIsSelectedFromDeck = false;
        update();
    }
}

bool Board::releaseOnColumn(int x, int y) {
    int numCol;
    int numCard;

    //On regarde si on lache sur une carte disponible d'abord
    if (clickOnColumn(x,y,numCol,numCard)) {

        int newCardNum = 52;
        if (numCard!=52) {
            newCardNum = columns[numCol]->getCardI(numCard)->getNumber();
        }

        if (movePossible(currentCard->getNumber(),newCardNum)) {
            //On sauve avant le déplacement
            saveBoard();

            //Alors on move la carte et on rechaine selon la provenance de la carte
            if (cardIsSelectedFromDeck){
                if (currentCard->getPreviousCard()==NULL) {
                    deck->setRootCard(currentCard->getNextCard());
                    if(currentCard->getNextCard()!=NULL) currentCard->getNextCard()->setPreviousCard(NULL);
                    currentCard->setNextCard(NULL);
                }
                else if (currentCard->getNextCard()==NULL){
                    currentCard->getPreviousCard()->setNextCard(NULL);
                    currentCard->setPreviousCard(NULL);
                }
                else {
                    currentCard->getPreviousCard()->setNextCard(currentCard->getNextCard());
                    currentCard->getNextCard()->setPreviousCard(currentCard->getPreviousCard());
                    currentCard->setPreviousCard(NULL);
                    currentCard->setNextCard(NULL);
                }
                deck->setIndex(deck->getIndex()-1);
            }
            else if(currentCard->getPreviousCard()!=NULL) {
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

            //On ajoute réélement et on met à jour
            columns[numCol]->add(currentCard);
            updatePos();
            return true;
        }
        //Si on ne peut pas se déplacer on remet les anciennes positions pour la carte courant
        else {
            if (!cardIsSelectedFromDeck) {
                //Et on n'oublie pas les cartes suivantes si on peut en avoir
                Card* card = currentCard;
                int j=0;
                while(card!=NULL) {
                    card->setPos(lastX,lastY+j*ECART_CARTE);
                    j++;
                    card = card->getNextCard();
                }
            }
            else {
                currentCard->setPos(lastX,lastY);
            }
        }

    }
    //On n'a même pas cliqué sur une colonne donc on remet les anciennes position
    else {
        if (!cardIsSelectedFromDeck) {
            Card* card = currentCard;
            int j=0;
            while(card!=NULL) {
                card->setPos(lastX,lastY+j*ECART_CARTE);
                j++;
                card = card->getNextCard();
            }
        }
        else {
            currentCard->setPos(lastX,lastY);
        }
    }
    return false;
}

/*
  On regarde si la carte qui se déplace peut être laché à l'endroit de la souris
  */
bool Board::releaseOnStack(int x, int y)
{
    int numStack;

    //Si on bouge plus d'une carte, on ne peut déjà pas lacher sur un stack
    if ((currentCard->getNextCard()==NULL || cardIsSelectedFromDeck) && clickOnStack(x,y,numStack)) {

        int numCard;
        if(stack[numStack]->getRootCard()==NULL) {
            numCard=52;
        }
        else {
            numCard = stack[numStack]->getRootCard()->getLeaf()->getNumber();
        }

        if (moveOnStackPossible(currentCard->getNumber(),numCard)) {
            //On sauve
            saveBoard();

            //On bouge et on met à jour les liens entre cartes
            if (cardIsSelectedFromDeck){
                if (currentCard->getPreviousCard()==NULL) {
                    deck->setRootCard(currentCard->getNextCard());
                    if(currentCard->getNextCard()!=NULL) currentCard->getNextCard()->setPreviousCard(NULL);
                    currentCard->setNextCard(NULL);
                }
                else if (currentCard->getNextCard()==NULL){
                    currentCard->getPreviousCard()->setNextCard(NULL);
                    currentCard->setPreviousCard(NULL);
                }
                else {
                    currentCard->getPreviousCard()->setNextCard(currentCard->getNextCard());
                    currentCard->getNextCard()->setPreviousCard(currentCard->getPreviousCard());
                    currentCard->setPreviousCard(NULL);
                    currentCard->setNextCard(NULL);
                }
                deck->setIndex(deck->getIndex()-1);
            }
            else if(currentCard->getPreviousCard()!=NULL) {
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
            return true;
        }
        //On remet les anciennes positions
        else {
            currentCard->setPos(lastX,lastY);
        }

    }
    //La souris n'était même pas sur un stack
    //On remet les anciennes positions
    else {
        currentCard->setPos(lastX,lastY);
    }
    return false;
}

void Board::mouseMoveEvent(QMouseEvent *e) {
    //Quand on bouge la souris, on bouge aussi la carte courante
    //Si elle est sélectionnée
    //Càd que la souris est restée enfoncée dessus
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
    else if (cardIsSelectedFromDeck) {
        //On ne bouge que la carte selectionnée
        currentCard->setPos(e->x()-shiftX,e->y()-shiftY);
        update();
    }
}

bool Board::clickOnDeck(int x, int y) {
    //On teste si on est sur la partie face cachée du deck
    if (x>deck->getX() && x<(deck->getX()+deck->getW()) && y>deck->getY() && y<(deck->getY()+deck->getH()))
        return true;
    return false;
}

bool Board::clickOnReverseDeck(int x, int y){

    //On fait la même chose mais sur le deck retourné
    //La position de carte valable dépend du type de deal et de l'index du deck
    if(deck->getIndex()>=2 || dealType==1){
        if (x>(deck->getX()+deck->getEcart()+(dealType-1)*15) && x<(deck->getX()+deck->getEcart()+deck->getW()+(dealType-1)*15) && y>deck->getY() && y<(deck->getY()+deck->getH())){
            if (deck->getIndex() != -1) {
                shiftX = x-(deck->getX()+deck->getEcart()+(dealType-1)*15);
                shiftY = y-deck->getY();
                return true;
            }
        }
    }
    else {
        if (x>(deck->getX()+deck->getEcart()+(deck->getIndex()*15)) && x<(deck->getX()+deck->getEcart()+deck->getW()+deck->getIndex()*15) && y>deck->getY() && y<(deck->getY()+deck->getH())){
            if (deck->getIndex() != -1) {
                shiftX = x-(deck->getX()+deck->getEcart()+deck->getIndex()*15);
                shiftY = y-deck->getY();
                return true;
            }
        }
    }
    return false;
}

/*
  On renvoie true si on a cliqué sur une carte
  col et card contiendront alors le numéro de la colonne de la carte cliquée
  et le numéro de la carte dans cette colonne
  */
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

            if (y>columns[i]->getY() && y<(columns[i]->getY()+columns[i]->getH()+(columns[i]->getRootCard()->getLengthToLeaf() +1 -1)*ECART_CARTE) ) {

                //On test sur quelle carte on est tombé et si elle est retournée
                //S'il n'y a pas de carte, on renvoie 52 en num Card
                for (int j=0; j<(columns[i]->getRootCard()->getLengthToLeaf()+1-1);j++) {

                    if (y>(columns[i]->getY()+j*ECART_CARTE) && y<(columns[i]->getY()+(j+1)*ECART_CARTE)) {
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

/*
  On renvoie vrai si une pile se trouve sous la souris
  numStack sera alors le numéro de la pile concernée
  */
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

/*
  Renvoie vrai si lastCard peut se placer au dessus de newCard
  dans une colonne
  */
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

/*
  On renvoie vrai si lastCard peut se place au dessus de newCard
  dans une pile
  */
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
    if (savedBoards.isEmpty() == false)
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
                        card->getPreviousCard()->setFace(false);
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
            deck->setIndex(board->getICardUpDeck());

        }

        updatePos();
        update();

        delete savedBoards.back();
        savedBoards.removeLast();
    }

    if (savedBoards.isEmpty() == true) emit savedBoardsEmpty();

}

void Board::restartGame()
{
    while (savedBoards.size() > 1)
    {
        delete savedBoards.back();
        savedBoards.removeLast();
    }

    restorePreviousBoard();

    gameTime = 0;
    emit startTime();
    emit newTime(gameTime);
}

void Board::updateTime()
{
    gameTime++;

    emit newTime(gameTime);
}

/*
  On teste si on a gagné dès que l'on ajoute une carte à un stack
  */
void Board::gagne() {

    bool gagne = true;
    for (int i = 0; i<4; i++) {
        //La pile est remplie si elle contient 13 cartes
        gagne = gagne && (stack[i]->getSize() == 13);
    }
    if (gagne) {
        //On arrete le temps en cours
        emit stopTime();

        //Stats
        nWonGames++;
        if (dealType == 1) nWonDeal1Games++;
        else nWonDeal3Games++;
        totalPLayedTime += gameTime;
        saveStatsFile();

        //Boite de dialogue avec les stats
        QMessageBox msgBox;
        QString text;
        text.append(QString("Felicitations !! \n\n\n"));
        text.append(QString("Voici vos statistiques :\n\n"));
        msgBox.setText(text);
        msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
        msgBox.setInformativeText("Voulez-vous rejouer?");
        msgBox.setDefaultButton(QMessageBox::Yes);
        msgBox.setWindowTitle("Bravo vous avez gagne !");

        if (msgBox.exec() == QMessageBox::Yes) {
            newGame();
        }
    }
}

/*
  Cette fonction regarde avec le board actuel si on peut placer
  une carte sur la pile
  */
bool Board::autoCompleteB(){

    //On ne vérifie ici pas si une carte de deck peut monter
    int stackNb, card2;
    Card* card;

    for (int i = 0; i<7; i++) {
        if(columns[i]->getSize()!=0) {
            card = columns[i]->getCardI(columns[i]->getSize()-1);

            for (stackNb=0;stackNb<4;stackNb++) {
                if (stack[stackNb]->getSize() == 0) {
                    card2 = 52;
                }
                else {
                    card2 = stack[stackNb]->getRootCard()->getLeaf()->getNumber();
                }

                if (moveOnStackPossible(card->getNumber(),card2)) {
                    //Si on peut déplacer la carte alors on le fait et on sauve
                    if (card->getNextCard()!=NULL) return false;
                    saveBoard();

                    if(card->getPreviousCard()!=NULL) {
                        card->getPreviousCard()->setNextCard(NULL);
                        card->getPreviousCard()->setFace(false);
                        card->setPreviousCard(NULL);
                    }
                    else {
                        columns[i]->setRootCard(NULL);
                    }

                    stack[stackNb]->addCard(card);
                    return true;
                    break;
                }
            }
        }
    }
    return false;
}

/*
  Cette fois ci on regarde si on peut ajouter des cartes
  du board tant qu'il en reste
  S'il reste des cartes mais qu'on ne peut plus en déplacer
  alors on arrête
  */
void Board::autoComplete(){
    bool cont = true;
    while (cont) {
        if (autoCompleteB()) {
            updatePos();
            update();
            gagne();
        }
        else cont=false;
    }
}

void Board::readStatsFile(){
    ifstream fileIn(fileName.c_str(), ios_base::in); //Ouverture du fichier à lire

    if (fileIn)
    {
        string line;

        if (getline(fileIn, line))
        {
            cout << "fichier de stat" << endl;
            istringstream intStream(line);
            intStream >> this->nPlayedGames;
            intStream >> this->nDeal1Games;
            intStream >> this->nDeal3Games;
            intStream >> this->nWonGames;
            intStream >> this->nWonDeal1Games;
            intStream >> this->nWonDeal3Games;
            intStream >> this->totalPLayedTime;
        }
        else
        {
            cerr << "fichier de stats corrompu" <<endl;
        }

        fileIn.close();
    }
    else
    {
        cout << "Pas fileIN" << endl;
        nPlayedGames = 0;
        nDeal1Games = 0;
        nDeal3Games = 0;
        nWonGames = 0;
        nWonDeal1Games = 0;
        nWonDeal3Games = 0;
        totalPLayedTime = 0;
    }
}

void Board::saveStatsFile()
{
    ofstream fileOut(fileName.c_str(), ios_base::trunc);

    //Vérification de l'ofstream
    if (fileOut)
    {
        fileOut << nPlayedGames << " "
                << nDeal1Games << " "
                << nDeal3Games << " "
                << nWonGames << " "
                << nWonDeal1Games << " "
                << nWonDeal3Games << " "
                << totalPLayedTime << endl;
        fileOut.close();
    }
    else
    {
        cerr << "Problème d'écriture du fichier de statistiques" << endl;
    }
}


void Board::deal1(){
    dealType = 1;
    newGame();
}

void Board::deal3(){
    dealType = 3;
    newGame();
}
