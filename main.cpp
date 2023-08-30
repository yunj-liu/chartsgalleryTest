#include "mainwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication myapp(argc, argv);
    MainWidget w;
    w.show();
    return myapp.exec();
}
