#include "mainwindow.h"
#include <QApplication>
#include <QIcon>

using namespace std;



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowIcon(QIcon("D:/QtProject/example/letterIcon.ico"));
    QApplication::setWindowIcon(QIcon("D:/QtProject/example/letterIcon.png"));
    w.setFixedSize(760,525);
    w.show();
    return a.exec();
}
