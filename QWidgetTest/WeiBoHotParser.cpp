#include "pch.h"
#include "WeiBoHotParser.h"

void WeiBoRealTimeInfo::Parse(const rapidjson::Value& oj_hot_item)
{
	is_ad = helper::Rapidjson::GetInt32("is_ad", oj_hot_item);
	hot_num = helper::Rapidjson::GetInt64("num", oj_hot_item);
	rank = helper::Rapidjson::GetInt32("rank", oj_hot_item);
	note = helper::Rapidjson::GetString("note", oj_hot_item);
	url = "https://s.weibo.com/weibo?q=%23"+ note +"%23";
	icon = helper::Rapidjson::GetString("icon", oj_hot_item);
	flag_desc = helper::Rapidjson::GetString("flag_desc", oj_hot_item);

	if (!is_ad)
	{
		auto pos = icon.rfind('/');
		std::wstring icon_name;
		if (pos != std::string::npos)
		{
			icon_name = helper::String::utf8_to_utf16(icon.substr(pos + 1).c_str());
		}

		icon_local_path = helper::path::get_cur_full_path_combine((L"icons/" + icon_name).c_str());
	}
	
	if (hot_num > 0)
	{
		auto n = (hot_num * 10) / 10000;
		hot_num_str = std::to_string((n / 10)) + "." + std::to_string(n % 10);
	}

}

void WeiBoHotGovInfo::Parse(const rapidjson::Value& oj_gov_item)
{
	WeiBoRealTimeInfo::Parse(oj_gov_item);

	note = helper::Rapidjson::GetString("note", oj_gov_item);

	if (note.length() > 0 && note[0] == '#' && note[note.length()-1] == '#')
	{
		note = note.substr(1, note.length() - 2);
	}

	url = "https://s.weibo.com/weibo?q=%23" + note + "%23";
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
		real_time_list.insert(real_time_list.begin(), gov_info);
		++realtime_count;
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
		realtime_info->Parse(*iter);
		if (realtime_info->is_ad)continue;

		real_time_list.push_back(realtime_info);
	}
}
