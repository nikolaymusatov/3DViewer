#include "view.h"

#include <QApplication>

using namespace s21;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    View w;
    w.show();
    return a.exec();
}
