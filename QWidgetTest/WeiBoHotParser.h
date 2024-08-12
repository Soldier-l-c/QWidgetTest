#pragma once
#include <helper/util_rapidjson.h>

struct WeiBoRealTimeInfo
{
	int32_t is_ad{ 0 };
	int64_t hot_num{ 0 };
	int32_t rank{ 0 };
	std::string note;
	std::string url;
	std::wstring icon_local_path;
	std::string icon;
	std::string flag_desc;
	std::string hot_num_str;
	virtual void Parse(const rapidjson::Value& oj_hot_item);
};

struct WeiBoHotGovInfo : public WeiBoRealTimeInfo
{
	void Parse(const rapidjson::Value& oj_gov_item);
};

using RealTimeInfoPtr = std::shared_ptr<WeiBoRealTimeInfo>;
using WeiBoHotGovInfoPtr = std::shared_ptr<WeiBoHotGovInfo>;
using RealTimeInfoList = std::vector<RealTimeInfoPtr>;

struct WeiBoHotInfo
{
	int32_t realtime_count{ 0 };
	int32_t ok{ 0 };
	void Parse(const std::string& data);

	void ParseRealTime(const rapidjson::Value& realtime);

	RealTimeInfoList real_time_list;
	WeiBoHotGovInfoPtr gov_info;
};
using WeiBoHotInfoPtr = std::shared_ptr<WeiBoHotInfo>;
