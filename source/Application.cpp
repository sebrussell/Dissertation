#include "Application.h"

Application::Application()
{
	m_mainTable.lock()->AddColumn("SteamID", STRNG);
	m_mainTable.lock()->AddColumn("PlayerName", STRNG);	
	m_mainTable.lock()->AddColumn("Country", GET);
	
	m_countryTable.lock()->AddColumn("CountryName", STRNG);
	m_countryTable.lock()->AddColumn("Count", DUPLICATE_ADD);
	
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
	
	m_genreTable.lock()->AddColumn("GenreID", INTEGER);
	m_genreTable.lock()->AddColumn("GenreName", STRNG);	
	
	m_genreToGame.lock()->AddColumn("GameID", INTEGER);
	m_genreToGame.lock()->AddColumn("GenreID", INTEGER);
	
	m_categoryTable.lock()->AddColumn("CategoryID", INTEGER);
	m_categoryTable.lock()->AddColumn("CategoryName", STRNG);	
	
	m_categoryToGame.lock()->AddColumn("GameID", INTEGER);
	m_categoryToGame.lock()->AddColumn("CategoryID", INTEGER);
	
	m_gameToCheck.lock()->AddColumn("GameID", INTEGER);
	m_gameToCheck.lock()->AddColumn("Added", INTEGER);
	m_gameToCheck.lock()->AddColumn("Evaluating", INTEGER);
}

Application::~Application()
{
	
}

void Application::UpdateGameCheckerTable()
{
	url =  "http://api.steampowered.com/ISteamApps/GetAppList/v0001/";			
	jsonSpare = api.GetData(url);

	int size = jsonSpare["applist"]["apps"]["app"].size();
		
	int gameID;
	

	for(int h = 0; h < size; h++)
	{		
		gameID = jsonSpare["applist"]["apps"]["app"][h]["appid"].asInt();
	
		m_gameToCheck.lock()->SetIntColumn("GameID", gameID);
		call = statement.Call("GamesToCheck");	
				
				
		bRet = objMain.execStatement(call);
		if (!bRet)
		{					
			std::cout << "ERROR!" << std::endl;
		}
				
		std::cout << h << std::endl;	
	}		
			
}

void Application::AddGamesToTable()
{
	int size = 0;
	bool maxReached = false;
	std::vector<int> m_gameIDs;
	
	call = statement.GetSize("GamesToCheck");	
	call += statement.AddNumberCondition("Added", 0);
	bRet = objMain.getDataStatement(call);
	if (!bRet)
	{					
		std::cout << "ERROR!" << std::endl;
	}
	else
	{
		while ((objMain.row = mysql_fetch_row(objMain.m_result)) != NULL)
		{
			size = std::atoi(objMain.row[0]);
		}
		objMain.ClearData();
	}
	
	
	if(size > 0)
	{
		
		call = statement.GetData("GamesToCheck");	
		call += statement.AddNumberCondition("Added", 0);
		bRet = objMain.getDataStatement(call);
		if (!bRet)
		{					
			std::cout << "ERROR!" << std::endl;
		}
		else
		{
			while ((objMain.row = mysql_fetch_row(objMain.m_result)) != NULL && !maxReached)
			{
				m_gameIDs.push_back(std::atoi(objMain.row[0]));
				if(m_gameIDs.size() >= maxC)
				{
					maxReached = true;
				}				
			}
			objMain.ClearData();
		}			
	}	
	
	maxReached = false;
	
	//begin timer
	
	for(int i = 0; i < m_gameIDs.size(); i++)
	{
		if(UpdateGame(m_gameIDs.at(i))) //if true = success
		{
			//change to 1
		}
		//change back to not in progress
			
	}
	
	//stop timer
	//wait for 300 - delta time
	
}

bool Application::UpdateGame(int _id)
{
	gameIDString = std::to_string(_id);
	url =  "http://store.steampowered.com/api/appdetails?appids=" + gameIDString;			
	jsonData = api.GetData(url);
	std::cout << "Steam Game ID: " << gameIDString << std::endl;
	
	if(!api.gotData)
	{
		return false;
	}
	
	if(jsonData[gameIDString]["success"].asBool() == true)
	{
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
				
		//COLLECT CATEGORIES
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
				
		m_gameTable.lock()->SetIntColumn("GameID", _id);
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
			m_genreToGame.lock()->SetIntColumn("GameID", _id);	
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
			m_categoryToGame.lock()->SetIntColumn("GameID", _id);	
			call = statement.Call("GameToCategory");				
			bRet = objMain.execStatement(call);
			if (!bRet)
			{					
				std::cout << "ERROR!" << std::endl;
			}
		}		
		
	}
	else
	{
		return false;
	}
			
	
	return true;
}

