#include "mainwindow.h"
#include "options.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    FreeConsole();
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/Images/xml-file-format-symbol.png"));
    MainWindow w;
    w.show();
    return a.exec();
}
