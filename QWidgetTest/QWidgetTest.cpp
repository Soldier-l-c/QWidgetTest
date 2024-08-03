#include "QWidgetTest.h"
#include "battery/battery.h"

QWidgetTest::QWidgetTest(QWidget *parent)
    : BaseWindow<QWidget>(parent)
{
    setFixedSize(100, 50);

    Battery* b = new  Battery(this);
    b->setFixedSize(100, 50);

    b->setValue(10);
}

QWidgetTest::~QWidgetTest()
{}
