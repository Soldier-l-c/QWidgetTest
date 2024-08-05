#include "pch.h"
#include "TimeCounterWidget.h"

TimeCounterWidget::TimeCounterWidget(QWidget* parent) :QWidget(parent)
{
	InitUI();
	UpdateTime(0);
}

void TimeCounterWidget::UpdateTime(int32_t seconds)
{
	if (last_value_ == seconds)return;
	last_value_ = seconds;

	if (seconds < 0 || time_num_labels_.size() < 6)return;

	auto second_ones = seconds % 10;
	auto second_tens = (seconds % 60) / 10;
	seconds /= 60;

	auto minute_ones = (seconds) % 10;
	auto minute_tens = (seconds % 60) / 10;
	seconds /= 60;

	auto hour_ones = (seconds) % 10;
	auto hour_tens = (seconds) / 10;

	if (hour_tens > 10)hour_tens = 9;

	if (0 == hour_tens && 0 == hour_ones)
	{
		hour_point_widget_->hide();
		time_num_labels_[0]->hide();
		time_num_labels_[1]->hide();
	}
	else
	{
		hour_point_widget_->show();
		time_num_labels_[0]->show();
		time_num_labels_[1]->show();
	}

	time_num_labels_[0]->setText(QString::number(hour_tens));
	time_num_labels_[1]->setText(QString::number(hour_ones));

	time_num_labels_[2]->setText(QString::number(minute_tens));
	time_num_labels_[3]->setText(QString::number(minute_ones));

	time_num_labels_[4]->setText(QString::number(second_tens));
	time_num_labels_[5]->setText(QString::number(second_ones));
}

void TimeCounterWidget::changeEvent(QEvent* e)
{
	QWidget::changeEvent(e);
}

void TimeCounterWidget::InitUI()
{
	this->setWhatsThis("background_no_border");

	QVBoxLayout* vbox_layout = new QVBoxLayout();
	setLayout(vbox_layout);

	QHBoxLayout* hbox_layout = new QHBoxLayout();
	QWidget* time_widget = new QWidget;
	time_widget->setLayout(hbox_layout);
	time_widget->setWhatsThis("background_no_border");

	InitNumLabel();
	hour_point_widget_ = new PointWidget(nullptr);
	hbox_layout->addStretch();
	hbox_layout->addWidget(time_num_labels_[0]);
	hbox_layout->addSpacing(4);
	hbox_layout->addWidget(time_num_labels_[1]);
	hbox_layout->addSpacing(4);
	hbox_layout->addWidget(hour_point_widget_);
	hbox_layout->addSpacing(4);
	hbox_layout->addWidget(time_num_labels_[2]);
	hbox_layout->addSpacing(4);
	hbox_layout->addWidget(time_num_labels_[3]);
	hbox_layout->addWidget(new PointWidget(nullptr));
	hbox_layout->addSpacing(4);
	hbox_layout->addWidget(time_num_labels_[4]);
	hbox_layout->addSpacing(4);
	hbox_layout->addWidget(time_num_labels_[5]);
	hbox_layout->addStretch();
	hbox_layout->setContentsMargins(0, 0, 0, 0);

	vbox_layout->addSpacing(5);
	vbox_layout->addWidget(time_widget);
	hbox_layout->setContentsMargins(0, 0, 0, 0);
}

void TimeCounterWidget::InitNumLabel()
{
	for (int32_t i = 0; i < 6; ++i)
	{
		auto label = new QLabel;
		time_num_labels_.emplace_back(label);
		label->setWhatsThis("time_counter_num");
		label->setFixedSize(28, 42);
		label->setAlignment(Qt::AlignCenter);
	}
}

PointWidget::PointWidget(QWidget* parent)
{
	setWhatsThis("background_no_border");
	QVBoxLayout* point_vbox_layout = new QVBoxLayout();
	setLayout(point_vbox_layout);

	QWidget* sub_point_widget_1 = new QWidget;
	sub_point_widget_1->setWhatsThis("background_time_point");
	sub_point_widget_1->setFixedSize(6, 6);

	QWidget* sub_point_widget_2 = new QWidget;
	sub_point_widget_2->setWhatsThis("background_time_point");
	sub_point_widget_2->setFixedSize(6, 6);

	point_vbox_layout->addStretch();
	point_vbox_layout->addWidget(sub_point_widget_1);
	point_vbox_layout->addSpacing(4);
	point_vbox_layout->addWidget(sub_point_widget_2);
	point_vbox_layout->addStretch();
	point_vbox_layout->setContentsMargins(0, 0, 0, 0);
}
