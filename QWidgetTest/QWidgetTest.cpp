#include "pch.h"
#include "QWidgetTest.h"
#include "ListWidget.h"

QWidgetTest::QWidgetTest(QWidget *parent)
    : BaseWindow<QWidget>(parent, Qt::WindowStaysOnTopHint)
{
    helper::ui::i18n::LoadTranslator(L"qwidget_test");

    InitUI();
    InitTimmer();
}

QWidgetTest::~QWidgetTest()
{}

void QWidgetTest::InitUI()
{
    auto main_widget = GetMainWidget(QSize(1000, 600));

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    main_widget->setLayout(layout);
    main_widget->setWhatsThis("background_no_border");
    layout->addWidget(InitTitleWidget());
    layout->addWidget(InitContentWidget());
}

void QWidgetTest::InitTimmer()
{
    connect(this, &QWidgetTest::SigTimeOut, this, &QWidgetTest::SlotTimeOut);

    timmer_ = new QTimer(this);
    timmer_->setInterval(std::chrono::milliseconds(100));
    timmer_->callOnTimeout([&]
        {
            SigTimeOut();
        });
    timmer_->start();
}

QWidget* QWidgetTest::InitTitleWidget()
{
    auto title_widget = CreateTitleBar(":/QWidgetTest/res/image/Ubuntu.ico", qtTrId("ids_title"),
        BaseUI::TitleFlag(BaseUI::DefaultTitleFlag ^ BaseUI::MaxButton));
    title_widget->setFixedSize(GetMainWidget()->width(), BaseUI::default_title_bar_hight);
    title_widget->setStyleSheet(("background-color:rgb(214,214,214)"));
    return title_widget;
}

QWidget* QWidgetTest::InitContentWidget()
{
    auto content_widget = new QWidget;
    content_widget->setFixedSize(GetMainWidget()->width(), GetMainWidget()->height() - BaseUI::default_title_bar_hight);
    content_widget->setWhatsThis("background_no_border");

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    content_widget->setLayout(layout);

    auto sub_widget = new QWidget;
    QHBoxLayout* sub_layout = new QHBoxLayout;
    sub_layout->setContentsMargins(0, 0, 0, 0);
    sub_widget->setLayout(sub_layout);
    sub_widget->setWhatsThis("background_no_border");

    battery_ = new  Battery(this);
    battery_->setFixedSize(100, 50);

    time_counter_ = new TimeCounterWidget(this);
    time_counter_->setFixedSize(270, 80);

    auto list_widget = new ListWidget(this);
    //list_widget->setFixedWidth(200);

    sub_layout->addWidget(list_widget);
    sub_layout->addWidget(battery_);
    sub_layout->addWidget(time_counter_);
    sub_layout->addStretch();
    layout->addWidget(sub_widget);

    return content_widget;
}

void QWidgetTest::SlotTimeOut()
{
    const auto one_day_sec = (24 * 60 * 60);
    auto cur_time = (helper::time::get_timestamp_ins() + 8 * 3600) % one_day_sec;
    battery_->setValue(int(100-((float)(cur_time) / (float)one_day_sec)*100));
    time_counter_->UpdateTime(cur_time);
}
