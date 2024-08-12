#pragma once
#include <QListWidget>
#include <QWidget>
#include "WeiboHotLoader.h"
class ListWidget :public QWidget
{
	Q_OBJECT
public:
	ListWidget(QWidget* parent = nullptr);

	bool Update();

private:
	void InitUI();

signals:
	void SigReadFinsh();
	void SigIconDownloadFinsh(int index);
	void SigInfoUpdateSuccess();

public:
	void SlotReadFinsh();
	void SlotIconDownloadFinsh(int index);
	void SlotItemClicked(QListWidgetItem* item);

private:
	void InitListWidget();
	void ReSetListWidget();

private:
	QListWidget* list_widget_{ nullptr };
	WeiboHotLoader loader_; 
	const int32_t update_interval_{ 60*10 };
	time_t last_update_time_{ 0 };
};