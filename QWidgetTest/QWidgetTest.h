#pragma once

#include <QtWidgets/QWidget>
#include <Qt/include/BaseWindow.h>
#include "ui_QWidgetTest.h"
class QWidgetTest : public BaseWindow<QWidget>
{
    Q_OBJECT

public:
    QWidgetTest(QWidget *parent = nullptr);
    ~QWidgetTest();

public:
    Ui::QWidgetTestClass ui;
};
