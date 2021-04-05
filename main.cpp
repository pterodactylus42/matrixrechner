#include "matrixrechner.h"
#include <QApplication>
#include "ui_matrixrechner.h"

int main(int argc, char *argv[])
{
    // base class that handles the event loop:
    QApplication a(argc, argv);
    //  color is used to render text ...
    a.setStyleSheet("QTextBrowser { background-color: black; color: green}");
    // instantiate and show the calculator:
     MatrixRechner w;
     w.show();

    return a.exec();

    // todo: where to put the destructor ?

}
