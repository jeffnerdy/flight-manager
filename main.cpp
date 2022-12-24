#include "mainwindow.h"
#include "classes.h"

#include <QApplication>

//user declaration
extern Passenger* user;

//plane declaration
extern Plane plane_1;
extern Plane plane_2;
extern Plane plane_3;
extern Plane plane_4;
extern Plane plane_5;
extern Plane plane_6;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
