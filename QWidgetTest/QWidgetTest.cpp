#include "pch.h"
#include "QWidgetTest.h"

QWidgetTest::QWidgetTest(QWidget *parent)
    : BaseWindow<QWidget>(parent)
{
    helper::ui::i18n::LoadTranslator(L"qwidget_test");

    InitUI();
    InitTimmer();
}

QWidgetTest::~QWidgetTest()
{}

void QWidgetTest::InitUI()
{
    setFixedSize(800, 600);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(layout);

    layout->addWidget(InitTitleWidget());
    layout->addWidget(InitContentWidget());
}

void QWidgetTest::InitTimmer()
{
    connect(this, &QWidgetTest::SigTimeOut, this, &QWidgetTest::SlotTimeOut);

    timmer_ = new QTimer(this);
    timmer_->setInterval(std::chrono::seconds(2));
    timmer_->callOnTimeout([&]
        {
            SigTimeOut();
        });
    timmer_->start();
}

QWidget* QWidgetTest::InitTitleWidget()
{
    auto title_widget = CreateTitleBar(":/QWidgetTest/res/image/emoji_213.ico", qtTrId("ids_title"),
        BaseUI::TitleFlag(BaseUI::DefaultTitleFlag ^ BaseUI::MaxButton));
    title_widget->setStyleSheet(("background-color:rgb(214,214,214)"));
    return title_widget;
}

QWidget* QWidgetTest::InitContentWidget()
{
    auto content_widget = new QWidget;
    content_widget->setFixedSize(width(), height() - BaseUI::default_title_bar_hight);
    
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    content_widget->setLayout(layout);

    auto sub_widget = new QWidget;
    QHBoxLayout* sub_layout = new QHBoxLayout;
    sub_layout->setContentsMargins(0, 0, 0, 0);
    sub_widget->setLayout(sub_layout);

    battery_ = new  Battery(this);
    battery_->setFixedSize(100, 50);

    sub_layout->addWidget(battery_);
    layout->addWidget(sub_widget);

    return content_widget;
}

void QWidgetTest::SlotTimeOut()
{
    static int32_t c = 20;
    battery_->setValue(c);
    c = (c + 20) % 120;
}
