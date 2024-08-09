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

void InitLogger()
{
    ObjectCreater creater;
    creater.Load(L"SoldierBase.dll");
    creater.CreateObject(g_logger);
    g_logger->Init(L"app.qttest");
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InitLogger();

    LOG(INFO) << "Start";

    helper::time::Timer timer;

    QWidgetTest w;

    LOG(INFO) << "QWidgetTest const time:[" << timer << "]";

    w.show();

    LOG(INFO) << "QWidgetTest const time:[" << timer << "]";

    LoadStyleFile(":/QWidgetTest/res/public_qss.qss");
  
    return a.exec();
}
