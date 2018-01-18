#include <curl/curl.h>
#include <json/json.h>
#include <memory>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>   
#include <algorithm>
#include <string>

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

struct Genre
{
	int id;
	std::string name;
};

class SteamApi
{
	public:
		SteamApi();
		~SteamApi();
		Json::Value GetData(std::string _url);
		std::string GetRandomID();
		std::string ConvertToDate(std::string _date);
		std::string UnixToDate(long int _date);
		std::string CleanRequirements(std::string _string);
		bool gotData = true;
	private:
		CURL* curl;
		std::unique_ptr<std::string> httpData;
		int httpCode;
		std::string api_key;
		std::string id;
		int length;
};