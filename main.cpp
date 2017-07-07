#include "mainwindow.h"
#include "generator.h"
#include <QApplication>
#include <QButtonGroup>
#include <QAbstractButton>
#include <cstdlib>
#include "fastamf.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    w.show();






    return a.exec();
}

