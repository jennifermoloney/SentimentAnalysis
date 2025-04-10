//
// Created by Jennifer Moloney on 4/8/25.
//
#include <QApplication>
#include "UI.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
