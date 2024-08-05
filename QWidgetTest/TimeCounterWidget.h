#pragma once
#include <QWidget>
#include <QLabel>
#include <QEvent>
class PointWidget :public QWidget
{
public:
	PointWidget(QWidget* parent);
};

class TimeCounterWidget : public QWidget
{
	Q_OBJECT
public:
	TimeCounterWidget(QWidget* parent);

	void UpdateTime(int32_t second);

	void changeEvent(QEvent* e);

private:
	void InitUI();
	void InitNumLabel();

public:
	std::vector<QLabel*> time_num_labels_;
	PointWidget* hour_point_widget_{ nullptr };
	QLabel* title_{ nullptr };
	int32_t last_value_{ -1 };
};