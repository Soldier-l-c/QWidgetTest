#include "pch.h"
#include "ListWidget.h"

#include "ListitemWidget.h"

ListWidget::ListWidget(QWidget* parent) :QWidget(parent)
{
	connect(this, &ListWidget::SigReadFinsh, this, &ListWidget::SlotReadFinsh);
	connect(this, &ListWidget::SigIconDownloadFinsh, this, &ListWidget::SlotIconDownloadFinsh);

	thread_pool::ThreadPool::instance().CommitTask([this] 
		{
			loader_.Load(std::make_shared<WeiboHttpStream>());
			SigReadFinsh();
		});
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

	auto index{ 0 };
	for (const auto& iter : loader_.GetInfo()->real_time_list)
	{
		auto list_item = new QListWidgetItem();
		list_widget_->addItem(list_item);
		list_widget_->setItemWidget(list_item, new ListitemWidget(++index, iter));
	}
}

void ListWidget::SlotReadFinsh()
{
	InitUI();

	thread_pool::ThreadPool::instance().CommitTask([this]
		{
			bool downlaoded{ false };
			for (const auto& iter : loader_.GetInfo()->real_time_list)
			{
				if (iter->is_ad || iter->icon.empty() || helper::path::path_exists(iter->icon_local_path))continue;

				std::string err_msg;
				int32_t curl_code{ 0 }, http_code{ 0 };
				NsNetHelper::NetError net_err{ NsNetHelper::SUCCESSED };
				downlaoded |= NsNetHelper::DownloadFile(iter->icon, iter->icon_local_path, err_msg, curl_code, http_code, net_err);
			}

			if (downlaoded)
			{
				SigIconDownloadFinsh();
			}
		});
}

void ListWidget::SlotIconDownloadFinsh()
{
	for (auto i = 0; i < loader_.GetInfo()->real_time_list.size(); ++i)
	{
		(dynamic_cast<ListitemWidget*>(list_widget_->itemWidget(list_widget_->item(i))))->UpdateIcon();
	}
}
