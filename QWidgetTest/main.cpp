#include "pch.h"
#include "QWidgetTest.h"
#include <QtWidgets/QApplication>
void LoadStyleFile(const QString& strStyle)
{
    QFile qss(strStyle);
    auto o = qss.open(QFile::ReadOnly);
    if (o)
    {
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidgetTest w;
    w.show();

    LoadStyleFile(":/QWidgetTest/res/public_qss.qss");
  
    return a.exec();
}
