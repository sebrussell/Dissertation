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

bool Application::GetIDTables()
{
	//LOAD GENRE INTO PROGRAM
	call = statement.GetData("Genre");	
	bRet = objMain.getDataStatement(call);
	if (!bRet)
	{					
		std::cout << "ERROR!" << std::endl;
		return false;
	}
	else
	{
		while ((objMain.row = mysql_fetch_row(objMain.m_result)) != NULL)
		{
			m_genresAdded[std::stoi(objMain.row[0])] = objMain.row[1];
		}
		objMain.ClearData();
	}	
	/*
	for (std::map<int, std::string>::iterator it=m_genresAdded.begin(); it!=m_genresAdded.end(); ++it)
	{
		std::cout << it->first << it->second << std::endl;
	}
	*/
	
	//LOAD CATEGORY INTO PROGRAM
	call = statement.GetData("Category");	
	bRet = objMain.getDataStatement(call);
	if (!bRet)
	{					
		std::cout << "ERROR!" << std::endl;
		return false;
	}
	else
	{
		while ((objMain.row = mysql_fetch_row(objMain.m_result)) != NULL)
		{
			m_categoriesAdded[std::stoi(objMain.row[0])] = objMain.row[1];
		}
		objMain.ClearData();
	}

	
	return true;
}

void Application::AddGamesToTable()
{
	int size = 0;
	bool maxReached = false;
	std::vector<int> m_gameIDs;
	
	//GETTING THE SIZE OF THE TABLE
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
	
	while(size > 0)
	{
		
	
		//IF THE SIZE IS GREATER THAN 0
		if(size > 0)
		{		
			//GET THE DATA FROM THE TABLE
			call = statement.GetData("GamesToCheck");	
			call += statement.AddNumberCondition("Added", 0);
			call += statement.AddNumberCondition("Evaluating", 0, 1);
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
		else
		{
			UpdateGameCheckerTable();
		}
		
		//CHANGE THE GAMES TO EVALUATING
		call = "";	
		if(m_gameIDs.size() > 2)
		{
			m_gameToCheck.lock()->SetIntColumn("GameID", m_gameIDs.at(0));				
			m_gameToCheck.lock()->SetIntColumn("Evaluating", 1);				
			call += m_gameToCheck.lock()->UpdateValues("GamesToCheck", "Evaluating", INTEGER);
			call += m_gameToCheck.lock()->UpdateValues("GamesToCheck", "GameID", INTEGER, 1);
			m_gameToCheck.lock()->SetIntColumn("GameID", m_gameIDs.at(1));
			call += m_gameToCheck.lock()->UpdateValues("GamesToCheck", "GameID", INTEGER, 2);
		}	
		for(int n = 2; n < m_gameIDs.size(); n++)
		{
			m_gameToCheck.lock()->SetIntColumn("GameID", m_gameIDs.at(n));
			call += m_gameToCheck.lock()->UpdateValues("GamesToCheck", "GameID", INTEGER, 3);		
		}	
		std::cout << call << std::endl;
		bRet = objMain.execStatement(call);				
		if (!bRet)
		{					
			std::cout << "ERROR!" << std::endl;
		}


		maxReached = false;	
		start = clock();
		
		
		//m_gameIDs.size()
		for(int i = 0; i < m_gameIDs.size(); i++)
		{
			if(UpdateGame(m_gameIDs.at(i)))
			{
				m_gameToCheck.lock()->SetIntColumn("GameID", m_gameIDs.at(i));				
				m_gameToCheck.lock()->SetIntColumn("Added", 1);	
				call = m_gameToCheck.lock()->UpdateValues("GamesToCheck", "Added", INTEGER);
				call += m_gameToCheck.lock()->UpdateValues("GamesToCheck", "GameID", INTEGER, 1);
				bRet = objMain.execStatement(call);				
				if (!bRet)
				{					
					std::cout << "ERROR!" << std::endl;
				}
			}
			m_gameToCheck.lock()->SetIntColumn("GameID", m_gameIDs.at(i));				
			m_gameToCheck.lock()->SetIntColumn("Evaluating", 0);	
			call = m_gameToCheck.lock()->UpdateValues("GamesToCheck", "Evaluating", INTEGER);
			call += m_gameToCheck.lock()->UpdateValues("GamesToCheck", "GameID", INTEGER, 1);
			bRet = objMain.execStatement(call);				
			if (!bRet)
			{					
				std::cout << "ERROR!" << std::endl;
			}		
		}
		
		m_gameIDs.clear();
		
		stop = clock();
		deltaTime = ((float)(clock() - start) / CLOCKS_PER_SEC);
		timeToWait = time - deltaTime;
		if(timeToWait > 0)
		{
			for(int t = 0; t < 10; t++)
			{
				sleep(timeToWait / 10);
				std::cout << (t + 1) * 10 << " Percent through wait." << std::endl;
			}
		}
	
	//loop to top
	}
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
			if(m_genresAdded.find(_genres[g].id) == m_genresAdded.end())
			{				
				m_genreTable.lock()->SetIntColumn("GenreID", _genres[g].id);
				m_genreTable.lock()->SetStringColumn("GenreName", _genres[g].name);	
				call = statement.Call("Genre");				
				bRet = objMain.execStatement(call);
				if (!bRet)
				{					
					std::cout << "ERROR!" << std::endl;
				}
				m_genresAdded[_genres[g].id] = _genres[g].name;
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
			if(m_categoriesAdded.find(_categories[g].id) == m_categoriesAdded.end())
			{	
				m_categoryTable.lock()->SetIntColumn("CategoryID", _categories[g].id);
				m_categoryTable.lock()->SetStringColumn("CategoryName", _categories[g].name);	
				call = statement.Call("Category");				
				bRet = objMain.execStatement(call);
				if (!bRet)
				{					
					std::cout << "ERROR!" << std::endl;
				}
				m_categoriesAdded[_categories[g].id] = _categories[g].name;
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

