#ifndef APPLICATION_H
#define APPLICATION_H

#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <time.h>
#include <vector>
#include <unistd.h>
#include <map>
#include <stdio.h> 
#ifdef __linux__ 
	#include <sys/time.h>   
	#include <sys/resource.h> 
#endif
#include <sstream>
#include <algorithm>
#include <iterator>
#include <locale>


#include "SteamApi.h"
#include "Statement.h"
#include "Table.h"
#include "MySQL.h"

struct Replace
{
	Replace(std::string _find, std::string _replace)
	{
		stringToFind = _find;
		stringToReplace = _replace;
	}
	std::string stringToFind, stringToReplace;
};

struct StringValues
{
	StringValues(){};
	StringValues(int _type, int _size, float _value)
	{
		type = _type;
		size = _size;
		value = _value;
	}
	int type, size; //type 0 = ram, 1 = processor
					//size 0 = MB, 1 = GB
	float value;
	
};

class Application
{
	public:
		Application();
		~Application();
		
		//adds all the games in STEAM to the COLLECTING TABLE
		void UpdateGameCheckerTable();
		
		//this adds the games from the COLLECTING TABLE to the GAME TABLE
		void AddGamesToTable();
		
		//THIS GETS ALL THE GENRES, CATEGORIES etc AND STORES THEM IN THE C++ PROGRAM
		bool GetIDTables();
		
		//JUST UPDATES 1 PARTICULAR GAME
		bool UpdateGame(int _id);
		
		//UPDATES PLAYERS
		void UpdatePlayers();
		
		//EVALUATES MOST COMMON WORDS IN PC REQUIREMENTS
		void EvaluatePCRequirements();
		std::vector<std::string> SplitWordIntoKeyString(std::string _string);
		bool IsUseful(std::string _string);
		float ConvertToNumber(std::string _number);
		StringValues CalculateScore(std::vector<std::string> _strings);
		

	
	private:
		int GetNumber(std::string _number, int location);
		
		static double TimeSpecToSeconds(struct timespec* ts);
	
		SteamApi api;	//calls the steam api
		Json::Value jsonData, jsonSpare; //used to store the returned json data
		
		std::string api_key = "256F7C304A4B0557D4E42DEF0AAB053A";	//needed to call the api
		
		std::string steamid;	
		std::string url;
		
		//variables to time it
		clock_t start, stop, startDatabase;
		double deltaTime;
			
		//variables for mysql
		std::string call;
		bool bRet;
		SqlConnector objMain;
		Statement statement;		
		
		
		std::weak_ptr<Table> m_mainTable = statement.CreateTable("MainTable");		
		std::weak_ptr<Table> m_countryTable = statement.CreateTable("CountryTable");		
		std::weak_ptr<Table> m_gameTable = statement.CreateTable("Game");		
		std::weak_ptr<Table> m_genreTable = statement.CreateTable("Genre");
		std::weak_ptr<Table> m_genreToGame = statement.CreateTable("GameToGenre");		
		std::weak_ptr<Table> m_categoryTable = statement.CreateTable("Category");
		std::weak_ptr<Table> m_categoryToGame = statement.CreateTable("GameToCategory");		
		std::weak_ptr<Table> m_gameToCheck = statement.CreateTable("GamesToCheck");
		

		
		
		//GetValue getCountryValue;
		//getCountryValue.m_columnNameToGet = "idCountryTable";
		//getCountryValue.m_tableName = "CountryTable";
		//getCountryValue.m_columnNameToCompare = "CountryName";
		
		

		std::string gameIDString;
		std::string name;
		std::string date;
		std::string type;
		double price;
		std::string ageRequirement, requirements;
		int metaCritic;
		
		int windows, mac, linux;
		
		int c = 0;
		int maxC = 250;
		int time = 300;
		double timeToWait;
		
		std::string country, primaryClanID, timeCreated, lastLogOff;
		
		std::map<int, std::string> m_genresAdded;
		std::map<int, std::string> m_categoriesAdded;
		std::map<int, std::string> m_countries;
		std::map<int, std::string> m_games;
		
		
		std::vector<std::string> m_playersToAdd;
		int queryAmount = 0;
		int playerSteamApiCheckAmount = 100;
		
		
		//linux timing
		struct timespec startLinux, stopLinux;
		
		
		std::vector<std::string> m_stringsToFind;
		std::vector<std::string> m_ramToFind;
		std::vector<std::string> m_processorToFind;
		std::vector<std::string> m_sizeToFind;
		std::vector<Replace> m_stringsToReplace;
		std::vector<std::string> m_alphabet;
		std::vector<std::string> m_otherRemoves;

};

#endif