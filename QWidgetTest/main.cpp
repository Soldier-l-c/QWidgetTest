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
    g_logger = NsBaseHelper::CreateObject<decltype(g_logger)>();
    g_logger->Init(L"app.qttest");
    g_logger->SetProperty(logger::LoggerProperty::AsynLog, 1);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!NsBaseHelper::GlobalInit())
        return -1;

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
