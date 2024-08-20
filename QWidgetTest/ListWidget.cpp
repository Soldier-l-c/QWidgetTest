#include "pch.h"
#include "ListWidget.h"
#include "ListitemWidget.h"

#include <QScroller>
ListWidget::ListWidget(QWidget* parent) :QWidget(parent)
{
	setMinimumWidth(400);
	InitUI();

	connect(this, &ListWidget::SigReadFinsh, this, &ListWidget::SlotReadFinsh);
	connect(this, &ListWidget::SigIconDownloadFinsh, this, &ListWidget::SlotIconDownloadFinsh);
	connect(list_widget_, &QListWidget::itemClicked, this, &ListWidget::SlotItemClicked);

	Update();
}

bool ListWidget::Update()
{
	auto curtime = helper::time::get_timestamp_ins();

	if (curtime - last_update_time_ < update_interval_)
	{
		return false;
	}

	last_update_time_ = curtime;

	thread_pool::ThreadPool::instance().CommitTask([this]
		{
			loader_.Load(std::make_shared<WeiboHttpStream>());
			SigReadFinsh();
		});

	return true;
}

void ListWidget::InitUI()
{
	InitListWidget();
	QHBoxLayout* layout = new QHBoxLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(list_widget_);
	setLayout(layout);
	setWhatsThis("background_no_border");
}

void ListWidget::SlotReadFinsh()
{
	if (!loader_.GetInfo()->ok)
		return;

	emit SigInfoUpdateSuccess();

	ReSetListWidget();

	thread_pool::ThreadPool::instance().CommitTask([this]
		{
			for (int index = 0; index<loader_.GetInfo()->real_time_list.size();++index)
			{
				const auto& iter = loader_.GetInfo()->real_time_list[index];
				if (iter->icon.empty())continue;
				
				auto exists = helper::path::path_exists(iter->icon_local_path);
				if (exists)continue;

				std::string err_msg;
				int32_t curl_code{ 0 }, http_code{ 0 };
				NsNetHelper::NetError net_err{ NsNetHelper::SUCCESSED };
				auto res = NsNetHelper::DownloadFile(iter->icon, iter->icon_local_path, err_msg, curl_code, http_code, net_err);

				if (res)
				{
					SigIconDownloadFinsh(index);
				}
			}
		});
}

void ListWidget::SlotIconDownloadFinsh(int index)
{
	if (0<=index && index<=loader_.GetInfo()->real_time_list.size())
	{
		(dynamic_cast<ListitemWidget*>(list_widget_->itemWidget(list_widget_->item(index))))->UpdateIcon();
	}
}

void ListWidget::SlotItemClicked(QListWidgetItem* item)
{
	(dynamic_cast<ListitemWidget*>(list_widget_->itemWidget(item)))->SlotClicked();
}

void ListWidget::InitListWidget()
{
	list_widget_ = new QListWidget();
	list_widget_->setFrameShape(QListWidget::NoFrame);						//去除边框
	list_widget_->setVerticalScrollMode(QListWidget::ScrollPerPixel);	//像素滚动
	list_widget_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);	//隐藏垂直滚动条
	list_widget_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);	//隐藏水平滚动条
	QScroller::grabGesture(list_widget_, QScroller::LeftMouseButtonGesture); //鼠标拖动
	list_widget_->setFocusPolicy(Qt::NoFocus);
	list_widget_->setWhatsThis("background_no_border");
}

void ListWidget::ReSetListWidget()
{
	if (!loader_.GetInfo()->ok)return;

	list_widget_->clear();

	auto index{ 0 };
	for (const auto& iter : loader_.GetInfo()->real_time_list)
	{
		auto list_item = new QListWidgetItem();
		auto item_widget = new ListitemWidget(++index, iter);
		list_item->setSizeHint(item_widget->size());

		list_widget_->addItem(list_item);
		list_widget_->setItemWidget(list_item, item_widget);
	}
}
