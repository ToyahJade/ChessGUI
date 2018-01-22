#include <iostream>
#include "GameUI.h"
#include "Timer.h"
#include <QTextEdit>

// A constructor for the UI
GameUI::GameUI(MainWindow *parent) : QWidget(0) {
    // Creating a new ClickableSquare for each of the 8x8 locations
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // Each square is a "gamingField"
            _gamingField[i][j] = new ClickableSquares(i, j, this);
            // This is where all the Qt magic happens!
            // Every signal has to be connected to the correct slot.
            // In this case, the signal "clicked" from object _gamingField[i][j]
            // is being connected to the slot squareClicked in "this" i.e the GameUI class
            QObject::connect(_gamingField[i][j], SIGNAL(clicked(int, int)), this, SLOT(squareClicked(int, int)));
        }
    }
    // We need some pieces on the board,
    // else we'd have an infinitely long game!
    drawPieces();

    // Create an undo button
    undoButton = new QPushButton("Undo", this);
    // setGeometry takes: x position, y position, width, height
    undoButton->setGeometry(600, 630, 110, 40);
    // Connect the action of button being clicked to the function pressedNewGame
    // which is in "this" class
    QObject::connect(undoButton, SIGNAL(clicked()), this, SLOT(pressedUndo()));

    // Create a new game button
    newGameButton = new QPushButton("New Game", this);
    // setGeometry takes: x position, y position, width, height
    newGameButton->setGeometry(719, 630, 110, 40);
    // Connect the action of button being clicked to the function pressedNewGame
    // which is in "this" class
    QObject::connect(newGameButton, SIGNAL(clicked()), this, SLOT(pressedNewGame()));

    // Create a hint button
    christmasButton = new QPushButton("!! Christmas !!", this);
    // setGeometry takes: x position, y position, width, height
    christmasButton->setGeometry(840, 630, 110, 40);
    // Connect the action of button being clicked to the function pressedNewGame
    // which is in "this" class
    QObject::connect(christmasButton, SIGNAL(clicked()), this, SLOT(pressedChristmas()));

    // A log box of moves would be nice
    logBox = new QTextEdit(this);
    // We don't want the user being able to edit the log
    logBox->setReadOnly(true);
    // setGeometry takes: x position, y position, width, height
    logBox->setGeometry(600, 310, 348, 315);
    // We can also set the font size
    logBox->setFont (QFont ("", 11));
    // And let's have a welcome message!
    logBox->setText("Hello and welcome to my chess game!");

    whiteBox = new QLabel(this);
    whiteBox->setGeometry(600, 20, 348, 140);
    whiteBox->setAutoFillBackground(true);
    whiteBox->setStyleSheet("QLabel {background-color : white;}");

    blackBox = new QLabel(this);
    blackBox->setAutoFillBackground(true);
    blackBox->setGeometry(600, 160, 348, 140);
    blackBox->setStyleSheet("QLabel {background-color : pink;}");

    for (int i = 0; i < 2; ++i) {
        timerLCD[i] = new Timer(this, 10, 0);
        timerLCD[i]->setGeometry(624, 40 + (i * 140), 300, 100);
        timerLCD[i]->setStyleSheet("QLCDNumber {background-color : lightGrey;}");
    }
    timerLCD[0]->timer->start(1000);

    loadChristmas();

    for (int i = 0; i < 2; i++) {
        takenPieces[i] = new QLabel(this);

        QFont font = takenPieces[i]->font();
        font.setPointSize(20);
        takenPieces[i]->setFont(font);
    }
    takenPieces[WHITE]->setGeometry(20, 75 + 8*SQUARE_SIZE, 8*SQUARE_SIZE, 35);
    takenPieces[BLACK]->setGeometry(20, 20, 8*SQUARE_SIZE, 35);

    takenPieces[WHITE]->setStyleSheet("QLabel {background-color : white;}");
    takenPieces[BLACK]->setStyleSheet("QLabel {background-color : pink;}");

}

// This is the function that controls the game play.
// When a square is clicked, it emits a signal giving its x and y coordinates.
// These are passed into this function
void GameUI::squareClicked(int x, int y) {
    // First thing to check is if that piece is movable
    if (_game.isPieceSelectable(std::make_pair(x, y))) {
        _game.isPieceSelected = true;
        // Show in the log box that this is moveable
        // To do: change this to give coordinates and piece type
        logBox->append("This piece is moveable");

    // Otherwise, if a piece has previously been selected...
    } else if (_game.isPieceSelected) {
        // ...we check if it can be moved to the clicked area
        if (_game.isMoveValid(std::make_pair(x, y))) {
            logBox->append("Piece has been moved: ");
            logBox->append(QString::fromStdString(_game.getPiecePosition() + " -> " + _game.getMovePosition() + "\n"));

            timerLCD[_game.getPlayer()]->timer->stop();
            timerLCD[!_game.getPlayer()]->timer->start(1000);

            if (_game.getLabelCode(x, y) > 0) {
                takenPieces[_game.getPlayer()]->setText(takenPieces[_game.getPlayer()]->text() + " " +
                                                                QString::fromStdString(_game.getLabel(x, y)));
            }

            // We move the selected piece to the selected destination,
            // switch turns,
            // unselect everything
            // and draw the new board.
            _game.movePiece();
            _game.switchPlayers();
            _game.isPieceSelected = false;
            drawPieces();

            if (_game.isInCheck()) {
                logBox->append("CHECK!\n");
            }

            // Update the turn label
            if (_game.getPlayer() == WHITE) {
                logBox->append("White's turn");
            } else {
                logBox->append("Black's turn");
            }

        } else {
            // If we can't move to the second clicked square,
            // we get this message:
            logBox->append("Piece cannot move there!");
        }

    } else {
        // If the selected piece is not movable,
        // we get this message:
        logBox->append("Piece cannot be moved");
    }
}

// A function to show the pieces on the board
void GameUI::drawPieces() {
    QPixmap scaledPixmap;

    // We go through every square...
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // ...and give it the correct label (i.e. piece),
            // which is taken from the board stored inside of _game
            if (_isChristmas) {
                _gamingField[i][j]->setText("");
                _gamingField[i][j]->setPixmap(_christmasTheme[_game.getLabelCode(i, j)].scaled(SQUARE_SIZE-5, SQUARE_SIZE-5, Qt::KeepAspectRatio, Qt::SmoothTransformation));

            } else {
                _gamingField[i][j]->setText(QString::fromStdString(_game.getLabel(i, j)));
            }
        }
    }
}

// A function to restart the game on the click of a button
void GameUI::pressedNewGame() {
    timerLCD[0]->timer->stop();
    timerLCD[1]->timer->stop();

    timerLCD[0]->reset();
    timerLCD[1]->reset();

    _game.newGame();
    drawPieces();

    timerLCD[0]->timer->start(1000);
}

void GameUI::pressedUndo() {
    _game.undo();

    timerLCD[_game.getPlayer()]->timer->stop();
    timerLCD[!_game.getPlayer()]->timer->start(1000);

    _game.switchPlayers();
    drawPieces();
}

void GameUI::pressedChristmas() {
    // if not Christmas then make it so!
    _isChristmas = !_isChristmas;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if ((i + j) % 2 == 0) {
                if (_isChristmas) {
                    _gamingField[i][j]->setStyleSheet("QLabel {background-color : red !important;}");

                } else {
                    _gamingField[i][j]->setStyleSheet("QLabel {background-color : pink !important;}");
                }
            }
        }
    }

    if (_isChristmas) {
        blackBox->setStyleSheet("QLabel {background-color : red !important;}");
        takenPieces[BLACK]->setStyleSheet("QLabel {background-color : red !important;}");
        christmasButton->setText("Scrooge :(");

    } else {
        blackBox->setStyleSheet("QLabel {background-color : pink !important;}");
        takenPieces[BLACK]->setStyleSheet("QLabel {background-color : pink !important;}");
        christmasButton->setText("!! Christmas !!");
    }

    drawPieces();
}

void GameUI::loadChristmas() {
    // king
    _christmasTheme[10] = QPixmap("../themes/christmas/santa_green.png");
    _christmasTheme[20] = QPixmap("../themes/christmas/santa_red.png");

    // queen
    _christmasTheme[11] = QPixmap("../themes/christmas/mrsSanta_green.png");
    _christmasTheme[21] = QPixmap("../themes/christmas/mrsSanta_red.png");

    // rook
    _christmasTheme[12] = QPixmap("../themes/christmas/tree_green.png");
    _christmasTheme[22] = QPixmap("../themes/christmas/tree_red.png");

    // bishop
    _christmasTheme[13] = QPixmap("../themes/christmas/snowman_green.png");
    _christmasTheme[23] = QPixmap("../themes/christmas/snowman_red.png");

    // knight
    _christmasTheme[14] = QPixmap("../themes/christmas/reindeer_green.png");
    _christmasTheme[24] = QPixmap("../themes/christmas/reindeer_red.png");

    // pawn
    _christmasTheme[15] = QPixmap("../themes/christmas/present_green.png");
    _christmasTheme[25] = QPixmap("../themes/christmas/present_red.png");

    // empty
    _christmasTheme[0] = QPixmap("../themes/christmas/blank.png");
}

GameUI::~GameUI() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            delete _gamingField[i][j];
        }
    }

    for (int i = 0; i < 2; ++i) {
        delete timerLCD[i];
        delete takenPieces[i];
    }

    delete newGameButton;
    delete undoButton;
    delete christmasButton;

    delete logBox;
}

