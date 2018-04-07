#include "anagraficaregioni.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AnagraficaRegioni w;

    w.show();

    return a.exec();
}




