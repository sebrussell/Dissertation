#ifndef APPLICATION_H
#define APPLICATION_H

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

class Application
{
	public:
		Application();
		~Application();
		
		void UpdateGameCheckerTable();
		void AddGamesToTable();
		bool UpdateGame(int _id);

	private:
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
		std::string ageRequirement;
		int metaCritic;
		
		int windows, mac, linux;
		
		int c = 0;
		int maxC = 250;
		int time = 300;
		
		std::string requirements;

};

#endif