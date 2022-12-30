#include "tetris_view.h"
#include "tetris.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Tetris* tetris = new Tetris;
    Tetris_View tv(tetris);
    tv.show();

    return a.exec();
}
