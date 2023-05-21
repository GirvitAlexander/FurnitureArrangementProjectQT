#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Room room;
    MainWindow w(&room);

    w.show();
    return a.exec();
}
