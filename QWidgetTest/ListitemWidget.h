#pragma once
#include <qwidget.h>
#include <QLabel>
#include "WeiBoHotParser.h"
class ListitemWidget : public QWidget
{
	Q_OBJECT
public:
	ListitemWidget(int32_t index, RealTimeInfoPtr hot_info_ptr, QWidget* parent = nullptr);

	void UpdateIcon();

private:
	void InitUI();

private:
	RealTimeInfoPtr hot_info_ptr_;
	int32_t index_{ 0 };
	QLabel* label_index_{ nullptr };
	QLabel* label_note_{ nullptr };
	QLabel* label_icon_{ nullptr };
};

