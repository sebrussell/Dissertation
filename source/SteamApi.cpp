#include "SteamApi.h"

SteamApi::SteamApi()
{
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	    // Don't bother trying IPv6, which would increase DNS resolution time.
    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

    // Don't wait forever, time out after 10 seconds.
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);

    // Follow HTTP redirects if necessary.
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	
	
	
	
	
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

    // Hook up data container (will be passed as the last parameter to the
    // callback handling function).  Can be any pointer type, since it will
    // internally be passed as a void pointer.
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());
	
	api_key = "256F7C304A4B0557D4E42DEF0AAB053A";
	
	id = "76561198069645144";
	
	srand (time(NULL));
	
}


SteamApi::~SteamApi()
{
	curl_global_cleanup();
}

Json::Value SteamApi::GetData(std::string _url)
{	
	curl = curl_easy_init();
	
	httpData = std::unique_ptr<std::string>(new std::string);
	httpCode = 0;
	
    curl_easy_setopt(curl, CURLOPT_URL, _url.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());
	curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
	//curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
	//curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

    // Run our HTTP GET command, capture the HTTP response code, and clean up.
		
    curl_easy_perform(curl);
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
	
	
    //curl_easy_cleanup(curl);
	Json::Value jsonData;
    Json::Reader jsonReader;
    if (httpCode == 200)
    {
        if (!jsonReader.parse(*httpData, jsonData))
        {
            std::cout << "Could not parse HTTP data as JSON" << std::endl;
            std::cout << "HTTP data was:\n" << *httpData.get() << std::endl;
        }
		else
		{
			
			//std::cout << jsonData.toStyledString() << std::endl;
		}
    }
    else
    {
        std::cout << "Couldn't GET from " << _url << " - exiting" << std::endl;
    }
	curl_easy_cleanup(curl);
	//curl_easy_reset(curl);	
	return jsonData;
}

std::string SteamApi::GetRandomID()
{	
	for(int i = 0; i < 8; i++)
	{		
		id.at(9 + i) = (rand() % 9 + 48);
	}

	return id;
}