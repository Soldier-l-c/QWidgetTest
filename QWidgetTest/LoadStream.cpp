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
        buffer << file.rdbuf(); // ��ȡ�����ļ����ݵ�stringstream
        file.close();           // �ر��ļ���
    }
    else 
    {
        return info_;
    }
    info_ = std::move(buffer.str());

    return info_;
}

const std::string& WeiboHttpStream::Read()
{
    std::string err_msg;
    int32_t curl_code{ 0 }, http_code{ 0 };
    NsNetHelper::NetError net_err{ NsNetHelper::FAILED };
    NsNetHelper::HttpRequest("https://weibo.com/ajax/side/hotSearch", "", {}, info_, err_msg, curl_code, http_code, net_err);

    LOG(INFO) << "http_code: [" << http_code << "] curl_code : [" << curl_code << "] err_msg:[" << err_msg << "] net_err:[" << (int32_t)net_err << "]";

    return info_;
}
