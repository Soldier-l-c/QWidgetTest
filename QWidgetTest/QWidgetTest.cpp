#include "pch.h"
#include "QWidgetTest.h"

QWidgetTest::QWidgetTest(QWidget *parent)
    : BaseWindow<QWidget>(parent, Qt::WindowStaysOnTopHint)
{
    helper::ui::i18n::LoadTranslator(L"qwidget_test");

    InitUI();
    InitTimmer();
}

QWidgetTest::~QWidgetTest()
{}

bool __stdcall QWidgetTest::TimerCallBack(uint32_t time_id, void* context, int32_t call_count, int32_t index)
{
    if (!context)return false;

    auto widget = static_cast<QWidgetTest*>(context);
    LOG(INFO) << "TimerCallBack";
    widget->SigTimeOut();

    return true;
}

void QWidgetTest::InitUI()
{
    auto main_widget = GetMainWidget(QSize(440, 800));

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
    connect(this, &QWidgetTest::SigTimeOut, this, &QWidgetTest::SlotTimeOut, Qt::DirectConnection);

    auto timer = NsNetHelper::CreateObject<ITimerPtr>();

    timer->AddTimer(0, TimerCallBack, this, 1000, -1);
}

QWidget* QWidgetTest::InitTitleWidget()
{
    auto title_widget = CreateTitleBar(":/QWidgetTest/res/image/weibo.png", qtTrId("ids_title"),
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
    layout->setContentsMargins(10, 10, 10, 10);
    content_widget->setLayout(layout);

    time_counter_ = new TimeCounterWidget(this);
    time_counter_->setFixedSize(content_widget->width()-20, 80);

    list_widget_ = new ListWidget(this);

    layout->addWidget(time_counter_);
    layout->addWidget(list_widget_);

    connect(list_widget_, &ListWidget::SigInfoUpdateSuccess, this, &QWidgetTest::UpdateTimeCounter);

    return content_widget;
}

void QWidgetTest::SlotTimeOut()
{
    list_widget_->Update();
}

void QWidgetTest::UpdateTimeCounter()
{
    const auto one_day_sec = (24 * 60 * 60);
    auto cur_time = (helper::time::get_timestamp_ins() + 8 * 3600) % one_day_sec;
    time_counter_->UpdateTime(cur_time);
}
