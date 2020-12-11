#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    if (!QFile("todo.db").exists())
    {     
        w.createDB();
    }
    w.connectToDB();
    return a.exec();
}
