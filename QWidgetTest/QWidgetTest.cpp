#include "QWidgetTest.h"
#include "battery/battery.h"
#include <QVBoxLayout>

QWidgetTest::QWidgetTest(QWidget *parent)
    : BaseWindow<QWidget>(parent)
{
    ui.setupUi(this);

    setFixedSize(400, 300);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(layout);

    Battery* b = new  Battery(this);
    b->setFixedSize(100, 50);
    b->setValue(10);
    auto title_widget = CreateTitleBar(":/QWidgetTest/res/image/emoji_213.ico", QString::fromStdWString(L"²âÊÔ³ÌÐò"), BaseUI::TitleFlag(BaseUI::DefaultTitleFlag ^ BaseUI::MaxButton));
    title_widget->setStyleSheet(("background-color:rgb(0,92,255)"));
    layout->addWidget(title_widget);
    layout->addStretch();
    layout->addWidget(b);
}

QWidgetTest::~QWidgetTest()
{}
