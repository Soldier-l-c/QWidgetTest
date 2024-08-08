#pragma once
struct LoadStream
{
	virtual const std::string& Read() = 0;
};
using LoadStreamPtr = std::shared_ptr<LoadStream>;

class WeiboFileStream :public LoadStream
{
public:
	WeiboFileStream() = default;
	WeiboFileStream(const std::wstring& file_path);
	virtual const std::string& Read();

private:
	std::wstring file_path_;
	std::string info_;
};

class WeiboHttpStream :public LoadStream
{
public:
	WeiboHttpStream() = default;
	virtual const std::string& Read();

private:
	std::string info_;
};