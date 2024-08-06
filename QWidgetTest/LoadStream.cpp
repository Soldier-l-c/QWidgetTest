#include "pch.h"
#include "LoadStream.h"

WeiboFileStream::WeiboFileStream(const std::wstring& file_path):file_path_(file_path)
{

}

const std::string& WeiboFileStream::Read()
{
	std::ifstream file(file_path_);
	if (!file.is_open())
	{
        LOG(ERROR) << "Read file failed. file:[" << helper::String::utf16_to_utf8(file_path_.c_str()) << "]";
		return info_;
	}
    std::stringstream buffer;

    if (file) 
    {
        buffer << file.rdbuf(); // 读取整个文件内容到stringstream
        file.close();           // 关闭文件流
    }
    else 
    {
        return info_;
    }
    info_ = std::move(buffer.str());

    return info_;
}
