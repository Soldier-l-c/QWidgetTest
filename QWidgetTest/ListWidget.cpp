#include "pch.h"
#include "ListWidget.h"
#include "WeiboHotLoader.h"
#include "ListitemWidget.h"

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
	loader.Load(std::make_shared<WeiboHttpStream>());
	auto index{ 0 };
	for (const auto& iter : loader.GetInfo()->real_time_list)
	{
		auto list_item = new QListWidgetItem();
		list_widget_->addItem(list_item);
		list_widget_->setItemWidget(list_item, new ListitemWidget(++index, iter));
	}
}
