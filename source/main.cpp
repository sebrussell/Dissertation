// main.cpp
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <time.h>
#include <vector>
#include "SteamApi.h"
#include "Statement.h"
#include "Table.h"
#include "MySQL.h"


int main()
{
	
	SteamApi api;
	
	std::string api_key = "256F7C304A4B0557D4E42DEF0AAB053A";
	std::string steamid = "76561198069645144";
    std::string url = "http://api.steampowered.com/ISteamUser/GetPlayerSummaries/v0002/?key=" + api_key + "&steamids=" + steamid;

	Json::Value jsonData;
	
	std::string name, location, id;
	
	std::vector<Test> test;
	
	int amount = 1;
	int count = 0;
	int checkAmount = 1;
	int apiCalls = 0;
	
	clock_t start, stop, startDatabase;
		
	std::string call;
	bool bRet;
	SqlConnector objMain;
	Statement statement;
	
	
	
	std::weak_ptr<Table> m_mainTable = statement.CreateTable("MainTable");
	m_mainTable.lock()->AddColumn("SteamID", STRNG);
	m_mainTable.lock()->AddColumn("PlayerName", STRNG);	
	m_mainTable.lock()->AddColumn("Country", GET);
	
	std::weak_ptr<Table> m_countryTable = statement.CreateTable("CountryTable");
	m_countryTable.lock()->AddColumn("CountryName", STRNG);
	m_countryTable.lock()->AddColumn("Count", DUPLICATE_ADD);
	
	
	
	GetValue getCountryValue;
	getCountryValue.m_columnNameToGet = "idCountryTable";
	getCountryValue.m_tableName = "CountryTable";
	getCountryValue.m_columnNameToCompare = "CountryName";

	
	
	start = clock();
	for(int i = 0; i < amount;)
	{
		//steamid = api.GetRandomID();
		
		//PLAYER SUMMARIES
		//url = "http://api.steampowered.com/ISteamUser/GetPlayerSummaries/v0002/?key=" + api_key + "&steamids=";
		
		//GAMES OWNED BY PLAYER
		url =  "http://api.steampowered.com/IPlayerService/GetOwnedGames/v0001/?key=" + api_key + "&format=json&include_played_free_games=1&include_appinfo=1&steamid=76561197960434622";
		
		apiCalls++;
		
		for(int n = 0; n < checkAmount; n++)
		{
			//url += api.GetRandomID() + ",";
		}
		
		jsonData = api.GetData(url);
		
		std::cout << jsonData << std::endl;
		
		
		i++;

		
		for(int z = 0; z < checkAmount; z++)
		{
			name = jsonData["response"]["players"][z]["personaname"].asString();
			location = jsonData["response"]["players"][z]["loccountrycode"].asString();
			id = jsonData["response"]["players"][z]["steamid"].asString();
			
			if(!name.empty() && !location.empty() & !id.empty())
			{
								
				
				//add the country value to the list
				m_countryTable.lock()->SetStringColumn("CountryName", location);
				call = statement.Call("CountryTable");					
				bRet = objMain.execStatement(call);
				if (!bRet)
				{					
					std::cout << "ERROR!" << std::endl;
				}
				
				
				//add the player to the main table
				getCountryValue.m_value = location;						
				m_mainTable.lock()->SetStringColumn("SteamID", test.at(i)._id);
				m_mainTable.lock()->SetStringColumn("PlayerName", test.at(i)._name);	
				m_mainTable.lock()->SetGetValueColumn("Country", getCountryValue);
				call = statement.Call("MainTable");				
				bRet = objMain.execStatement(call);
				if (!bRet)
				{					
					std::cout << "ERROR!" << std::endl;
				}
				
				
				
				i++;				
				std::cout << i << std::endl;
				if(i > amount)
				{
					break;
				}
			}	
			count++;
		}			
	
		
	}
	
	// DATABASE STUFF
	
	/*
	std::cout << "ADD TO DATABASE" << std::endl;

	
	startDatabase = clock();
	
	
	
	

	
	
	

	


	try {
        
		for(int i = 0; i < test.size(); i++)
		{
			std::cout << i << std::endl;
			
			
			

			bRet = objMain.execStatement(call);
			if (!bRet) std::cout << "ERROR!" << std::endl;

		}
        
    } catch (char *e) {
        std::cout << "[EXCEPTION] " << e << std::endl;
        return 1;
    }
	
	
	
	stop = clock();		
	std::cout << "Time Taken Total: " << ((float)(stop - start) / CLOCKS_PER_SEC) << std::endl;
	std::cout << "Time Taken Steam Query: " << ((float)(startDatabase - start) / CLOCKS_PER_SEC) << std::endl;
	std::cout << "Time Taken Dtabase Query: " << ((float)(stop - startDatabase) / CLOCKS_PER_SEC) << std::endl;
	std::cout << "Amount Checked: " << count << std::endl;
	std::cout << "Amount Added: " << amount << std::endl;
	std::cout << "API Calls: " << apiCalls << std::endl;
	std::cout << "Average API Call per User: " << apiCalls / amount << std::endl;
	std::cout << "Average time per user: " << ((float)(stop - start) / CLOCKS_PER_SEC) / amount << std::endl;
	std::cout << "Hit Percentage: " << (float)((float)amount / (float)count) << std::endl;
	std::cout << " " << std::endl;
	
	*/
	
	
	
    return 0;
}
