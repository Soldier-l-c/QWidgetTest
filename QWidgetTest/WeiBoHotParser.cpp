#include "pch.h"
#include "WeiBoHotParser.h"

void WeiBoRealTimeInfo::Parse(const rapidjson::Value& oj_hot_item)
{
	is_ad = helper::Rapidjson::GetInt32("is_ad", oj_hot_item);
	hot_num = helper::Rapidjson::GetInt64("num", oj_hot_item);
	rank = helper::Rapidjson::GetInt32("rank", oj_hot_item);
	note = helper::Rapidjson::GetString("note", oj_hot_item);
	url = "https://s.weibo.com/weibo?q=%23"+ note +"%23";
}

void WeiBoHotGovInfo::Parse(const rapidjson::Value& oj_gov_item)
{
}

void WeiBoHotInfo::Parse(const std::string& data)
{
	rapidjson::Document doc;
	doc.Parse(data.c_str());
	if (doc.HasParseError() || !doc.IsObject())
	{
		LOG(ERROR) << "WeiBoHotInfo::Parse parse error";
		return;
	}

	ok = helper::Rapidjson::GetInt32("ok", doc, 0);
	if (0 == ok)return;

	if (!doc.HasMember("data") || !doc["data"].IsObject())
	{
		return;
	}

	const auto& data_obj = doc["data"].GetObj();
	if (data_obj.HasMember("realtime") && data_obj["realtime"].IsArray())
	{
		ParseRealTime(data_obj["realtime"]);
	}

	if (data_obj.HasMember("hotgov") && data_obj["hotgov"].IsObject())
	{
		gov_info = std::make_shared<WeiBoHotGovInfo>();
		gov_info->Parse(data_obj["hotgov"]);
	}
}

void WeiBoHotInfo::ParseRealTime(const rapidjson::Value& realtime)
{
	if (!realtime.IsArray())
		return;
	const auto& arrays = realtime.GetArray();
	for (auto iter = arrays.Begin(); iter != arrays.end(); ++iter)
	{
		if (!iter->IsObject())continue;
		++realtime_count;

		auto realtime_info = std::make_shared<WeiBoRealTimeInfo>();
		real_time_list.push_back(realtime_info);
		realtime_info->Parse(*iter);
	}
}
