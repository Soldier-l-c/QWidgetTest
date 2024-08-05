#pragma once
#include <QtWidgets/QWidget>
#include <Qt/include/BaseWindow.h>
#include <qtimer.h>

#include "battery/battery.h"

class QWidgetTest : public BaseWindow<QWidget>
{
    Q_OBJECT

public:
    QWidgetTest(QWidget *parent = nullptr);
    ~QWidgetTest();

signals:
    void SigTimeOut();

public:
    void SlotTimeOut();
    
private:
    void InitUI();
    void InitTimmer();
    QWidget* InitTitleWidget();
    QWidget* InitContentWidget();

public:
    QTimer* timmer_{ nullptr };
    Battery* battery_{ nullptr };
};
