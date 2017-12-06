#include <curl/curl.h>
#include <json/json.h>
#include <memory>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>   

namespace
{
    std::size_t callback(
            const char* in,
            std::size_t size,
            std::size_t num,
            std::string* out)
    {
        const std::size_t totalBytes(size * num);
        out->append(in, totalBytes);
        return totalBytes;
    }
}

class SteamApi
{
	public:
		SteamApi();
		~SteamApi();
		Json::Value GetData(std::string _url);
		std::string GetRandomID();
	private:
		CURL* curl;
		std::unique_ptr<std::string> httpData;
		int httpCode;
		std::string api_key;
		std::string id;
};