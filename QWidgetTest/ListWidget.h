#pragma once
#include <QListWidget>
#include <QWidget>
class ListWidget :public QWidget
{
	Q_OBJECT
public:
	ListWidget(QWidget* parent = nullptr);

private:
	void InitUI();

private:
	QListWidget* list_widget_{ nullptr };
};