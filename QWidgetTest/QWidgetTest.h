#pragma once
#include "battery/battery.h"
#include "TimeCounterWidget.h"
#include "ListWidget.h"
#include <Qt/include/BaseWindow.h>

class QWidgetTest : public BaseWindow<QWidget>
{
    Q_OBJECT

public:
    QWidgetTest(QWidget* parent = nullptr);
    ~QWidgetTest();

signals:
    void SigTimeOut();

public:
    void SlotTimeOut();

public:
    void UpdateTimeCounter();

private:
    void InitUI();
    void InitTimmer();

    QWidget* InitTitleWidget();
    QWidget* InitContentWidget();

public:
    const int32_t shadow_radius_{ 10 };
    QTimer* timmer_{ nullptr };
    Battery* battery_{ nullptr };
    QWidget* background_{ nullptr };
    TimeCounterWidget* time_counter_{ 0 };
    ListWidget* list_widget_{ nullptr };
};
