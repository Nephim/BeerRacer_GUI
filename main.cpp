#include "beer_racer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Beer_Racer w;
    w.show();
    return a.exec();
}
