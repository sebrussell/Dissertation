// main.cpp
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <time.h>
#include <vector>
#include "SteamApi.h"
#include "MySQL.h"


int main()
{
	SteamApi api;
	
	std::string api_key = "256F7C304A4B0557D4E42DEF0AAB053A";
	std::string steamid = "76561198069645144";
    std::string url = "http://api.steampowered.com/ISteamUser/GetPlayerSummaries/v0002/?key=" + api_key + "&steamids=" + steamid;

	const std::string servername = "db712559206.db.1and1.com";
	const std::string username = "dbo712559206";
	const std::string password = "Passwords123*";
	std::string dbname = "db712559206";
	
	Json::Value jsonData;
	
	std::string name, location, id;
	
	std::vector<Test> test;
	
	int amount = 100;
	int count = 0;
	int checkAmount = 100;
	
	clock_t start, stop;
	
	
	start = clock();
	
	for(int i = 0; i < amount;)
	{
		//steamid = api.GetRandomID();
		url = "http://api.steampowered.com/ISteamUser/GetPlayerSummaries/v0002/?key=" + api_key + "&steamids=";
		
		for(int n = 0; n < checkAmount; n++)
		{
			url += api.GetRandomID() + ",";
		}
		
		jsonData = api.GetData(url);
		
		for(int z = 0; z < checkAmount; z++)
		{
			name = jsonData["response"]["players"][z]["personaname"].asString();
			location = jsonData["response"]["players"][z]["loccountrycode"].asString();
			id = jsonData["response"]["players"][z]["steamid"].asString();
			
			if(!name.empty() && !location.empty() & !id.empty())
			{
				test.push_back(Test(i, id, name, location));
				i++;
				if(i > amount)
				{
					break;
				}
			}	
			count++;
		}		
	}
	stop = clock();	
	
	for(int i = 0; i < test.size(); i++)
	{
		std::cout << test.at(i)._id << " " << test.at(i)._name << " " << test.at(i)._location << std::endl;
	}
	
	std::cout << "Regular Version 1: " << ((float)(stop - start) / CLOCKS_PER_SEC) << std::endl;
	std::cout << "Amount Checked: " << count << std::endl;
	std::cout << "Average time per user: " << ((float)(stop - start) / CLOCKS_PER_SEC) / amount << std::endl;
	std::cout << "Hit Percentage: " << (float)((float)amount / (float)count) << std::endl;
	std::cout << " " << std::endl;
	
	// DATABASE STUFF
	
	try {
        Proc objMain;
		for(int i = 0; i < test.size(); i++)
		{
			bool bRet = objMain.execMain(test.at(i));
			if (!bRet) std::cout << "ERROR!" << std::endl;
		}
        
    } catch (char *e) {
        std::cout << "[EXCEPTION] " << e << std::endl;
        return 1;
    }
	
    return 0;
}
