#pragma once

#include <QtWidgets/QWidget>
#include <Qt/include/BaseWindow.h>

class QWidgetTest : public BaseWindow<QWidget>
{
    Q_OBJECT

public:
    QWidgetTest(QWidget *parent = nullptr);
    ~QWidgetTest();
};
