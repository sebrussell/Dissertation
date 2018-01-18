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
	gotData = true;

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
			gotData = false;
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

std::string SteamApi::ConvertToDate(std::string _date)
{
	std::string returnString = "0000-00-00";
	std::string month = "AAA";
	
	length = _date.length();
	
	if(length >= 11)
	{
		returnString.at(3) = _date.at(length - 1);
		returnString.at(2) = _date.at(length - 2);
		returnString.at(1) = _date.at(length - 3);
		returnString.at(0) = _date.at(length - 4);	

		month.at(2) = _date.at(length - 7);
		month.at(1) = _date.at(length - 8);
		month.at(0) = _date.at(length - 9);
		
		if(month == "Jan")
		{
			returnString.at(6) = '1';
		}
		if(month == "Feb")
		{
			returnString.at(6) = '2';
		}
		if(month == "Mar")
		{
			returnString.at(6) = '3';
		}
		if(month == "Apr")
		{
			returnString.at(6) = '4';
		}
		if(month == "May")
		{
			returnString.at(6) = '5';
		}
		if(month == "Jun")
		{
			returnString.at(6) = '6';
		}
		if(month == "Jul")
		{
			returnString.at(6) = '7';
		}
		if(month == "Aug")
		{
			returnString.at(6) = '8';
		}
		if(month == "Sep")
		{
			returnString.at(6) = '9';
		}
		if(month == "Oct")
		{
			returnString.at(5) = '1';
			returnString.at(6) = '0';
		}
		if(month == "Nov")
		{
			returnString.at(5) = '1';
			returnString.at(6) = '1';
		}
		if(month == "Dec")
		{
			returnString.at(5) = '1';
			returnString.at(6) = '2';
		}	

	}
	
	
	
	if(length == 11)
	{
		returnString.at(9) = _date.at(0);	
	}
	else if(length == 12)
	{
		returnString.at(8) = _date.at(0);
		returnString.at(9) = _date.at(1);
	}
	
	return returnString;
}

std::string SteamApi::UnixToDate(long int _date)
{
	time_t t = time(NULL);
	struct tm *tm = localtime(&_date);
	char date[20];
	strftime(date, sizeof(date), "%Y-%m-%d", tm);
	std::cout << date << std::endl;
}

std::string SteamApi::CleanRequirements(std::string _string)
{
	
	std::string returnString = "Unknown";
	
	
	
	std::size_t found = _string.find("Minimum:");
	if (found!=std::string::npos)
	{
		_string.erase(_string.begin(), _string.begin() + found + 8);
		
		found = _string.find("Recommended:");
		if (found!=std::string::npos)
		{
			_string.erase(_string.begin() + found, _string.end());
		}
		
		size_t n = std::count(_string.begin(), _string.end(), '<');			
		
		//std::cout << n << std::endl;
		
		for(size_t z = 0; z < n; z++)
		{
			found = _string.find("<");
			std::size_t found2 = _string.find(">");
			
			_string.erase(_string.begin() + found, _string.begin() + found2 + 1);
		}	

		/*
		n = std::count(_string.begin(), _string.end(), ',');
		
		if(n > 4)
		{
			found = _string.find(",");
			found = _string.find(",", found + 1, 1);
			found = _string.find(",", found + 1, 1);
			
			_string.erase(_string.begin() + found, _string.end());
		}
		*/
		
		returnString = _string;
	}	
	else if(_string.length() > 0)
	{
		size_t n = std::count(_string.begin(), _string.end(), '<');			
		
		//std::cout << n << std::endl;
		
		for(size_t z = 0; z < n; z++)
		{
			found = _string.find("<");
			std::size_t found2 = _string.find(">");
			
			_string.erase(_string.begin() + found, _string.begin() + found2 + 1);
		}	

		/*
		n = std::count(_string.begin(), _string.end(), ',');
		
		if(n > 4)
		{
			found = _string.find(",");
			found = _string.find(",", found + 1, 1);
			found = _string.find(",", found + 1, 1);
			
			_string.erase(_string.begin() + found, _string.end());
		}
		*/
		
		returnString = _string;
	}
	
	
	
	//std::cout << returnString << std::endl;
	//std::cout << "" << std::endl;
	
	return returnString;
	
}









