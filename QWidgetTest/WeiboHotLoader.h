#pragma once
#include "WeiBoHotParser.h"
#include "LoadStream.h"
class WeiboHotLoader
{
public:
	bool Load(const LoadStreamPtr& load);

	WeiBoHotInfoPtr GetInfo();

private:
	WeiBoHotInfoPtr hot_info_;
};