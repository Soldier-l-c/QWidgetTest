#pragma once
#include <QListWidget>
#include <QWidget>
#include "WeiboHotLoader.h"
class ListWidget :public QWidget
{
	Q_OBJECT
public:
	ListWidget(QWidget* parent = nullptr);

private:
	void InitUI();

signals:
	void SigReadFinsh();
	void SigIconDownloadFinsh();

public:
	void SlotReadFinsh();
	void SlotIconDownloadFinsh();
	void SlotItemClicked(QListWidgetItem* item);

private:
	QListWidget* list_widget_{ nullptr };
	WeiboHotLoader loader_;
};