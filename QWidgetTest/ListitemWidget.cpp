#include "pch.h"
#include "ListitemWidget.h"
#include <QFont>

ListitemWidget::ListitemWidget(int32_t index, RealTimeInfoPtr hot_info_ptr, QWidget* parent) :
	QWidget(parent),
	hot_info_ptr_(hot_info_ptr),
	index_(index)
{
	setWhatsThis("background_no_border");
	InitUI();
}

void ListitemWidget::UpdateIcon()
{
	if (helper::path::path_exists(hot_info_ptr_->icon_local_path))
	{
		label_icon_->setPixmap(QIcon(QString::fromStdWString(hot_info_ptr_->icon_local_path)).pixmap(24, 24));
	}
	else
	{
		//label_icon_->setPixmap(QIcon(":/QWidgetTest/res/image/Ubuntu.ico").pixmap(24, 24));
	}
}

size_t TextWidth(const QString& str, int32_t font_size)
{
	QFont font;
	font.setPointSize(font_size); // 设置字体大小

	QFontMetrics metrics(font);
	return metrics.horizontalAdvance(str); // 获取字体宽度
}

void ListitemWidget::InitUI()
{
	QHBoxLayout* layout = new QHBoxLayout;
	layout->setContentsMargins(5, 0, 0, 5);
	setLayout(layout);

	setFixedHeight(24);

	label_index_ = new QLabel();
	label_note_ = new QLabel();
	label_falg_desc_ = new QLabel();
	label_hot_num_ = new QLabel();
	label_icon_ = new QLabel();

	auto add_size = ((int)hot_info_ptr_->flag_desc.empty()) * 50 + ((int)hot_info_ptr_->hot_num_str.empty()) * 50;

	label_index_->setFixedSize(24, 24);
	label_note_->setFixedHeight(24);
	label_note_->setFixedWidth(200 + add_size);
	label_falg_desc_->setFixedSize(hot_info_ptr_->flag_desc.empty() ? QSize(0, 0) : QSize(50, 24));
	label_hot_num_->setFixedSize(hot_info_ptr_->hot_num_str.empty()? QSize(0, 0) : QSize(50, 24));
	label_icon_->setFixedSize(24, 24);

	label_index_->setWhatsThis("default_label");
	label_note_->setWhatsThis("default_label");
	label_falg_desc_->setWhatsThis("default_label");
	label_hot_num_->setWhatsThis("default_label");

	UpdateIcon();
	helper::SetTest(label_index_, QString::number(index_) + ".");
	helper::SetTest(label_note_, hot_info_ptr_->note.c_str());
	helper::SetTest(label_falg_desc_, hot_info_ptr_->flag_desc.c_str());
	helper::SetTest(label_hot_num_, hot_info_ptr_->hot_num_str.c_str()+qtTrId("ids_wan"));

	layout->addWidget(label_index_);
	layout->addSpacing(5);
	layout->addWidget(label_note_);
	layout->addSpacing(5);
	layout->addWidget(label_falg_desc_);
	layout->addSpacing(5);
	layout->addWidget(label_hot_num_);
	layout->addStretch();
	layout->addWidget(label_icon_);
}
