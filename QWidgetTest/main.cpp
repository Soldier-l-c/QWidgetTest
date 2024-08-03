#include "QWidgetTest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidgetTest w;
    w.show();
    return a.exec();
}
