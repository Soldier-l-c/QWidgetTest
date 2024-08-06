#include "pch.h"
#include "WeiboHotLoader.h"

bool WeiboHotLoader::Load(const LoadStreamPtr& load)
{
	VERF_PTR(load, false);
	hot_info_ =std::make_shared<WeiBoHotInfo>();
	hot_info_->Parse(load->Read());
	return true;
}

WeiBoHotInfoPtr WeiboHotLoader::GetInfo()
{
	return hot_info_;
}
