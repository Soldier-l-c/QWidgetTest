#include "pch.h"
#include "ListWidget.h"
#include "WeiboHotLoader.h"

ListWidget::ListWidget(QWidget* parent) :QWidget(parent)
{
	InitUI();
}

void ListWidget::InitUI()
{
	list_widget_ = new QListWidget();
	QHBoxLayout* layout = new QHBoxLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(list_widget_);
	setLayout(layout);
	setWhatsThis("background_no_border");
	list_widget_->setWhatsThis("background_no_border");

	WeiboHotLoader loader;
	loader.Load(std::make_shared<WeiboFileStream>(helper::path::get_cur_full_path_combine(L"weibo_hot.json")));
	auto index{ 0 };
	for (const auto& iter : loader.GetInfo()->real_time_list)
	{
		auto list_item = new QListWidgetItem(QString::number(++index) +"." + iter->note.c_str(), list_widget_);
		list_widget_->addItem(list_item);
	}
}
