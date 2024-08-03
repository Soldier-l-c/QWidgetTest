#include "QWidgetTest.h"
#include "battery/battery.h"
#include <QVBoxLayout>
QWidgetTest::QWidgetTest(QWidget *parent)
    : BaseWindow<QWidget>(parent)
{
    setFixedSize(400, 300);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(layout);

    Battery* b = new  Battery(this);
    b->setFixedSize(100, 50);
    b->setValue(10);

    layout->addWidget(CreateTitleBar(":public/title_logo.ico", QString::fromStdWString(L"²âÊÔ³ÌÐò")));
    layout->addStretch();
    layout->addWidget(b);
}

QWidgetTest::~QWidgetTest()
{}
