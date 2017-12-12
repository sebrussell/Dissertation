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

	const std::string servername = "db712559206.db.1and1.com";
	const std::string username = "dbo712559206";
	const std::string password = "Passwords123*";
	std::string dbname = "db712559206";
	
	Json::Value jsonData;
	
	std::string name, location, id;
	
	std::vector<Test> test;
	
	int amount = 20000;
	int count = 0;
	int checkAmount = 100;
	int apiCalls = 0;
	
	clock_t start, stop, startDatabase;
	
	
	start = clock();
	
	for(int i = 0; i < amount;)
	{
		//steamid = api.GetRandomID();
		url = "http://api.steampowered.com/ISteamUser/GetPlayerSummaries/v0002/?key=" + api_key + "&steamids=";
		
		apiCalls++;
		
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
	
	std::cout << "ADD TO DATABASE" << std::endl;

	
	startDatabase = clock();
	
	
	
	
	Statement statement;
	std::weak_ptr<Table> m_table = statement.CreateTable("MainTable");
	m_table.lock()->AddColumn("SteamID", STRNG);
	m_table.lock()->AddColumn("PlayerName", STRNG);	
	m_table.lock()->AddColumn("Country", GET);
	
	std::weak_ptr<Table> m_countryTable = statement.CreateTable("CountryTable");
	m_countryTable.lock()->AddColumn("CountryName", STRNG);
	m_countryTable.lock()->AddColumn("Count", DUPLICATE_ADD);
	
	
	
	GetValue getValue;
	getValue.m_columnNameToGet = "idCountryTable";
	getValue.m_tableName = "CountryTable";
	getValue.m_columnNameToCompare = "CountryName";
	getValue.m_value = "GB";
	
	
	m_table.lock()->SetStringColumn("SteamID", "7068");
	m_table.lock()->SetStringColumn("PlayerName", "tes");	
	m_table.lock()->SetGetValueColumn("Country", getValue);

	
	
	std::string call;
	bool bRet;

	try {
        SqlConnector objMain;
		for(int i = 0; i < test.size(); i++)
		{
			std::cout << i << std::endl;
			
			m_countryTable.lock()->SetStringColumn("CountryName", test.at(i)._location);
			call = statement.Call("CountryTable");	
			
			
			bRet = objMain.execStatement(call);
			if (!bRet) std::cout << "ERROR!" << std::endl;
			
			
			getValue.m_value =  test.at(i)._location;		
			
			
			m_table.lock()->SetStringColumn("SteamID", test.at(i)._id);
			m_table.lock()->SetStringColumn("PlayerName", test.at(i)._name);	
			m_table.lock()->SetGetValueColumn("Country", getValue);
			call = statement.Call("MainTable");
			

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
	
	
	
	
	
    return 0;
}
