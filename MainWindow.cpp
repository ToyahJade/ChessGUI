#include "MainWindow.h"
#include "qt/GameUI.h"

// Constructor for the main window
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    this->setStyleSheet(
            "MainWindow {background-image:url(\"../themes/standard/table.jpg\");"
                    "background-position: center;}" );
    gameUI = new GameUI(this);
    // A standard Qt function assigning the UI to the window
    setCentralWidget(gameUI);

    //Setting some properties for the window
    setWindowTitle(tr("Chess"));
    this->setFixedSize(968, 690);
}

MainWindow::~MainWindow() {
    delete gameUI;
}

void MainWindow::initialise() {

    GameUI *ui = static_cast<GameUI*>(gameUI);
    ui->pressedNewGame();
}
