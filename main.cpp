#include "MainWindow.h"
#include "chess/Board.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    // Create an object of type newWindow
    // This is where all the Qt magic happens!
    MainWindow w;
    w.initialise();
    // Display the window
    w.show();

    return a.exec();
}
