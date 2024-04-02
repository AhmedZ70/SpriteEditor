#include "mainwindow.h"
#include <QApplication>

/**
 * @author Joseph Corbeil, Johnny Song, Ezekiel Jaramillo, Ahmed Zahran, Raj Reddy, Joel Ronca
 * @date April. 1, 2024
 * @name main cpp file for assignment8
 * This cpp file will create the MainWindow and show the window.
 *
 * File and software practice principles reviewed by Ahmed Zahran.
*/

int main(int argc, char *argv[])
{
    // Creates the QApplication
    QApplication a(argc, argv);
    MainWindow w;

    // Shows the MainWndow
    w.show();

    return a.exec();
}
