#include "dr_mario_view.h"
#include "dr_mario.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dr_Mario* model = new Dr_Mario;
    Dr_Mario_View drmv(model);
    drmv.show();

    return a.exec();
}
