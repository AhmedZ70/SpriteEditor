#include "mainwindow.h"
#include "spriteModel.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // SpriteModel * spriteEditor;
    MainWindow w;
    w.show();
    return a.exec();
}
