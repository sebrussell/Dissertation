// main.cpp
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <time.h>
#include <vector>
#include <unistd.h>
#include "SteamApi.h"
#include "Statement.h"
#include "Table.h"
#include "MySQL.h"


int main()
{
	
	SteamApi api;	//calls the steam api
	Json::Value jsonData, jsonSpare; //used to store the returned json data
	
	
	//call times
	int amount = 1;
	int count = 0;
	int checkAmount = 1;
	int apiCalls = 0;
	
	std::string api_key = "256F7C304A4B0557D4E42DEF0AAB053A";	//needed to call the api
	
	
	//default values
	std::string steamid = "76561198069645144";	
    std::string url = "http://api.steampowered.com/ISteamUser/GetPlayerSummaries/v0002/?key=" + api_key + "&steamids=" + steamid;

	
	//variables to store returned data
	std::string name, location, id;
	
	//variables to time it
	clock_t start, stop, startDatabase;
	double deltaTime;
		
	//variables for mysql
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
	
	
	std::weak_ptr<Table> m_gameTable = statement.CreateTable("Game");
	m_mainTable.lock()->AddColumn("GameID", INTEGER);
	m_mainTable.lock()->AddColumn("GameName", STRNG);
	m_mainTable.lock()->AddColumn("Price", FLT);
	m_mainTable.lock()->AddColumn("AgeLimit", STRNG);
	m_mainTable.lock()->AddColumn("MetaCritic", INTEGER);
	m_mainTable.lock()->AddColumn("Windows", INTEGER);
	m_mainTable.lock()->AddColumn("Mac", INTEGER);
	m_mainTable.lock()->AddColumn("Linux", INTEGER);
	m_mainTable.lock()->AddColumn("ReleaseDate", STRNG);
	m_mainTable.lock()->AddColumn("Requirements", STRNG);
	m_mainTable.lock()->AddColumn("Type", STRNG);

	
	std::weak_ptr<Table> m_genreTable = statement.CreateTable("Genre");
	m_genreTable.lock()->AddColumn("GenreID", INTEGER);
	m_genreTable.lock()->AddColumn("GenreName", STRNG);	

	std::weak_ptr<Table> m_genreToGame = statement.CreateTable("GameToGenre");
	m_genreToGame.lock()->AddColumn("GameID", INTEGER);
	m_genreToGame.lock()->AddColumn("GenreID", INTEGER);	
	
	
	
	std::weak_ptr<Table> m_categoryTable = statement.CreateTable("Category");
	m_categoryTable.lock()->AddColumn("CategoryID", INTEGER);
	m_categoryTable.lock()->AddColumn("CategoryName", STRNG);	

	std::weak_ptr<Table> m_categoryToGame = statement.CreateTable("GameToCategory");
	m_categoryToGame.lock()->AddColumn("GameID", INTEGER);
	m_categoryToGame.lock()->AddColumn("CategoryID", INTEGER);

	
	
	GetValue getCountryValue;
	getCountryValue.m_columnNameToGet = "idCountryTable";
	getCountryValue.m_tableName = "CountryTable";
	getCountryValue.m_columnNameToCompare = "CountryName";

	
	std::vector<int> m_gameIDs;
	
	
	start = clock();
	for(int i = 0; i < amount;)
	{
		//steamid = api.GetRandomID();
		
		//PLAYER SUMMARIES
		//url = "http://api.steampowered.com/ISteamUser/GetPlayerSummaries/v0002/?key=" + api_key + "&steamids=";
		
		//GAMES OWNED BY PLAYER
		//url =  "http://api.steampowered.com/IPlayerService/GetOwnedGames/v0001/?key=" + api_key + "&format=json&include_played_free_games=1&include_appinfo=1&steamid=76561197960434622";
		
		//ALL GAMES
		//url = "http://api.steampowered.com/ISteamApps/GetAppList/v0001/";
		
		apiCalls++;
		
		for(int n = 0; n < checkAmount; n++)
		{
			//url += api.GetRandomID() + ",";
		}
		
		int gameID;
		std::string gameIDString;
		std::string name;
		std::string date;
		std::string type;
		double price;
		std::string ageRequirement;
		int metaCritic;
		
		int windows, mac, linux;
		
		int c = 0;
		int time = 300;
		
		std::string requirements;

		
		
		
		url =  "http://api.steampowered.com/ISteamApps/GetAppList/v0001/";			
		jsonSpare = api.GetData(url);
		
		
		
		//52061
		for(int h = 0; h < 52061; h++)
		{		
			if(c == 0)
			{
				start = clock();
			}
	
			c++;
	
			gameID = jsonSpare["applist"]["apps"]["app"][h]["appid"].asInt();			
			gameIDString = std::to_string(gameID);

			
			url =  "http://store.steampowered.com/api/appdetails?appids=" + gameIDString;
			
			jsonData = api.GetData(url);
			
			std::cout << "Steam Game ID: " <<gameIDString << std::endl;
		
			if(jsonData[gameIDString]["success"].asBool() == true)
			{
				
				
				//GET BASIC INFORMATION
				name = jsonData[gameIDString]["data"]["name"].asString();
				type = jsonData[gameIDString]["data"]["type"].asString();
				ageRequirement = jsonData[gameIDString]["data"]["required_age"].asString();
				metaCritic = jsonData[gameIDString]["data"]["metacritic"]["score"].asInt();

				
				//GET THE PRICE - EVERYTHING IS IN GBP
				if(jsonData[gameIDString]["data"]["is_free"].asInt())
				{
					price = 0;
				}
				else
				{
					price = jsonData[gameIDString]["data"]["price_overview"]["final"].asDouble() / 100;
				}
				

				//GET INFORMATION ON WHAT THE GAME IS COMPATIBLE WITH
				windows = jsonData[gameIDString]["data"]["platforms"]["windows"].asInt();
				mac = jsonData[gameIDString]["data"]["platforms"]["mac"].asInt();
				linux = jsonData[gameIDString]["data"]["platforms"]["linux"].asInt();
				

				//CONVERT DATE INTO MYSQL FORMAT
				date = api.ConvertToDate(jsonData[gameIDString]["data"]["release_date"]["date"].asString());

				
				//COLLECT PC REQUIREMENTS
				if(jsonData[gameIDString]["data"]["pc_requirements"].size() > 0)
				{
					requirements = api.CleanRequirements(jsonData[gameIDString]["data"]["pc_requirements"]["minimum"].asString());
				}
				else
				{
					requirements = "Unknown";
				}

				
				//COLLECT GENRES
				std::vector<Genre> _genres;				
				if(jsonData[gameIDString]["data"]["genres"].size() > 0)
				{
					for(int g = 0; g < jsonData[gameIDString]["data"]["genres"].size(); g++)
					{
						Genre temp;
						std::string tempString = jsonData[gameIDString]["data"]["genres"][g]["id"].asString();
						temp.id = std::stoi(tempString.c_str());
						temp.name = jsonData[gameIDString]["data"]["genres"][g]["description"].asString();
						_genres.push_back(temp);
					}
				}
				
				std::vector<Genre> _categories;
				if(jsonData[gameIDString]["data"]["categories"].size() > 0)
				{
					for(int g = 0; g < jsonData[gameIDString]["data"]["categories"].size(); g++)
					{
						Genre temp;
						std::string tempString = jsonData[gameIDString]["data"]["categories"][g]["id"].asString();
						temp.id = std::stoi(tempString.c_str());
						temp.name = jsonData[gameIDString]["data"]["categories"][g]["description"].asString();
						_categories.push_back(temp);
					}
				}
				
				//ADD GAME INFORMATION
				
				m_gameTable.lock()->SetIntColumn("GameID", gameID);
				m_gameTable.lock()->SetStringColumn("GameName", name);				
				m_gameTable.lock()->SetFloatColumn("Price", price);
				m_gameTable.lock()->SetStringColumn("AgeLimit", ageRequirement);
				m_gameTable.lock()->SetIntColumn("MetaCritic", metaCritic);
				m_gameTable.lock()->SetIntColumn("Windows", windows);
				m_gameTable.lock()->SetIntColumn("Mac", mac);
				m_gameTable.lock()->SetIntColumn("Linux", linux);
				m_gameTable.lock()->SetStringColumn("ReleaseDate", date);
				m_gameTable.lock()->SetStringColumn("Requirements", requirements);
				m_gameTable.lock()->SetStringColumn("Type", type);				
				call = statement.Call("Game");	
				bRet = objMain.execStatement(call);
				if (!bRet)
				{					
					std::cout << "ERROR!" << std::endl;
				}
				
				//ADD GENRE INFORMATION
				for(int g = 0; g < _genres.size(); g++)
				{
					m_genreTable.lock()->SetIntColumn("GenreID", _genres[g].id);
					m_genreTable.lock()->SetStringColumn("GenreName", _genres[g].name);	
					call = statement.Call("Genre");				
					bRet = objMain.execStatement(call);
					if (!bRet)
					{					
						std::cout << "ERROR!" << std::endl;
					}
					
					m_genreToGame.lock()->SetIntColumn("GenreID", _genres[g].id);
					m_genreToGame.lock()->SetIntColumn("GameID", gameID);	
					call = statement.Call("GameToGenre");				
					bRet = objMain.execStatement(call);
					if (!bRet)
					{					
						std::cout << "ERROR!" << std::endl;
					}
				}
				
				//ADD CATEGORY INFORMATION
				for(int g = 0; g < _categories.size(); g++)
				{
					m_categoryTable.lock()->SetIntColumn("CategoryID", _categories[g].id);
					m_categoryTable.lock()->SetStringColumn("CategoryName", _categories[g].name);	
					call = statement.Call("Category");				
					bRet = objMain.execStatement(call);
					if (!bRet)
					{					
						std::cout << "ERROR!" << std::endl;
					}
					
					m_categoryToGame.lock()->SetIntColumn("CategoryID", _categories[g].id);
					m_categoryToGame.lock()->SetIntColumn("GameID", gameID);	
					call = statement.Call("GameToCategory");				
					bRet = objMain.execStatement(call);
					if (!bRet)
					{					
						std::cout << "ERROR!" << std::endl;
					}
				}

			
			}
 			
			if(c > 249)
			{
				
				
				deltaTime = ((float)(clock() - start) / CLOCKS_PER_SEC);
				double timeToWait = time - deltaTime;
				std::cout << "TIME TO WAIT: " << timeToWait << "----------------------------------------" << std::endl;
				std::cout << c << std::endl;
				
				for(int t = 0; t < 10; t++)
				{
					sleep(timeToWait / 10);
					std::cout << (t + 1) * 10 << " Percent through wait." << std::endl;
				}
				
				
				c = 0;
				
				
			}		
		}
		
		
		
		
		
		i++;

		/*
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
		*/
		
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
