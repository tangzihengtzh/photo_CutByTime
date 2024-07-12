#include "mainwindow.h"
#include "mylib.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    //ShowImage("E:/visualstudio project/photo_timecut/x64/Debug/test.jpg");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
