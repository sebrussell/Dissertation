#include "Application.h"

Application::Application()
{
	//TABLES
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
	m_gameToCheck.lock()->AddColumn("Count", INTEGER);
	
	//DEFAULT CHECK PLAYERS
	m_playersToAdd.push_back("76561198050068679");
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
	
	
	//LOAD COUNTRIES INTO PROGRAM
	call = statement.GetData("Countries");	
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
			m_countries[std::stoi(objMain.row[0])] = objMain.row[1];
		}
		objMain.ClearData();
	}
	
	
	//LOAD GAMES INTO PROGRAM
	call = statement.GetData("Game");	
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
			m_games[std::stoi(objMain.row[0])] = objMain.row[1];
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
	call += statement.AddNumberCondition("Evaluating", 0, 1);
	call += statement.AddNumberCondition("Count", 3, 1, "<");
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
	
	std::cout << "Game Amount: " << size << std::endl;
	
	while(size > 0)
	{
		
	
		//IF THE SIZE IS GREATER THAN 0
		if(size > 0)
		{		
			//GET THE DATA FROM THE TABLE
			call = statement.GetData("GamesToCheck");	
			call += statement.AddNumberCondition("Added", 0);
			call += statement.AddNumberCondition("Evaluating", 0, 1);
			call += statement.AddNumberCondition("Count", 3, 1, "<");
		
			bRet = objMain.getDataStatement(call);
			if (!bRet)
			{					
				std::cout << "ERROR!" << std::endl;
			}
			else
			{			
				while ((objMain.row = mysql_fetch_row(objMain.m_result)) != NULL && maxReached == false)
				{						
					m_gameIDs.push_back(std::atoi(objMain.row[0]));
					std::cout << m_gameIDs.size() << std::endl;
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
		
		
		std::cout << m_gameIDs.size() << std::endl;
		
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
		
		bRet = objMain.execStatement(call);				
		if (!bRet)
		{					
			std::cout << "ERROR!" << std::endl;
		}
		
		maxReached = false;	
		
		
		#ifdef __linux__ 
			if(clock_gettime(CLOCK_MONOTONIC, &startLinux))
			{ /* handle error */ }
		#elif _WIN32
			start = clock();
		#else
			start = clock();
		#endif
		
		start = clock();		
		//TRY AND ADD ALL THE GAMES IN THE VECTOR TO THE MAIN GAME TABLE
		//
		for(int i = 0; i < m_gameIDs.size(); i++)
		{
			//if update succeeds 
			if(UpdateGame(m_gameIDs.at(i)))
			{
				//change added to 1
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
			//change evaluating to 0
			m_gameToCheck.lock()->SetIntColumn("GameID", m_gameIDs.at(i));				
			m_gameToCheck.lock()->SetIntColumn("Evaluating", 0);	
			call = m_gameToCheck.lock()->UpdateValues("GamesToCheck", "Evaluating", INTEGER);
			call += m_gameToCheck.lock()->UpdateValues("GamesToCheck", "GameID", INTEGER, 1);
			
			bRet = objMain.execStatement(call);				
			if (!bRet)
			{					
				std::cout << "ERROR!" << std::endl;
			}	
			
			//increase count
			m_gameToCheck.lock()->SetIntColumn("GameID", m_gameIDs.at(i));	
			call = m_gameToCheck.lock()->UpdateValues("GamesToCheck", "Count", INTEGER, 0, true);
			call += m_gameToCheck.lock()->UpdateValues("GamesToCheck", "GameID", INTEGER, 1);	
			bRet = objMain.execStatement(call);				
			if (!bRet)
			{					
				std::cout << "ERROR!" << std::endl;
			}				
		}
		
		//CLEAR THE GAMES TO GET VECTOR
		m_gameIDs.clear();
		
		//PAUSE SO IT DOESNT BREAK STEAM API
		
		
		
		#ifdef __linux__ 
			if(clock_gettime(CLOCK_MONOTONIC, &stopLinux))
			{ /* handle error */ }
			deltaTime = TimeSpecToSeconds(&stopLinux) - TimeSpecToSeconds(&startLinux);
		#elif _WIN32
			stop = clock();
			deltaTime = ((float)(clock() - start) / CLOCKS_PER_SEC);
		#else
			stop = clock();
			deltaTime = ((float)(clock() - start) / CLOCKS_PER_SEC);
		#endif
		
		
		timeToWait = time - deltaTime;
		
		std::cout << "TIME TO WAIT: " << timeToWait << "----------------------------------------" << std::endl;
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

double Application::TimeSpecToSeconds(struct timespec* ts)
{
    return (double)ts->tv_sec + (double)ts->tv_nsec / 1000000000.0;
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

void Application::EvaluatePCRequirements()
{
	std::cout << "Adding Games String" << std::endl;
	std::vector<std::string> games;
	std::vector<std::string> words;
	call = statement.GetData("Game");	
	call += statement.AddStringCondition("GameType", "game");	
	bRet = objMain.getDataStatement(call);
	if (!bRet)
	{					
		std::cout << "ERROR!" << std::endl;
	}
	else
	{
		while ((objMain.row = mysql_fetch_row(objMain.m_result)) != NULL)
		{
			games.push_back(objMain.row[9]);
		}
		objMain.ClearData();
	}
	
	std::cout << "Converting to Upper and Adding Individual Word to Vector" << std::endl;
	std::locale loc;
	for(int i = 0; i < games.size(); i++)
	{
		for (int n = 0; n < games.at(i).length(); n++)
		{
			games.at(i)[n] = std::toupper(games.at(i)[n],loc);
		}
		
		std::istringstream iss(games.at(i));
		copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(words));
	}
	
	std::cout << "Counting Amount of Words" << std::endl;
	std::map<std::string, int> counter;
	for(int i = 0; i < words.size(); i++)
	{
		std::map<std::string, int>::iterator it = counter.find(words[i]); 
		if (it != counter.end())
		{
			it->second += 1;
		}
		else
		{
			counter.insert(std::make_pair(words[i], 1));
		}
	}
	
	
	std::map<std::string, int> topWords;
	bool breakIt = false;
	for(int i = 0; i < 100; i++)
	{
		topWords.insert(std::make_pair(std::to_string(i), 0));
	}
	
	for (std::map<std::string, int>::iterator it=counter.begin(); it!=counter.end(); ++it)
	{
		for (std::map<std::string, int>::iterator topIt=topWords.begin(); topIt!=topWords.end() && !breakIt; ++topIt)
		{
			if(topIt->second < it->second)
			{
				topWords.erase(topIt);
				topWords.insert(std::make_pair(it->first, it->second));
				topIt = topWords.end();
				breakIt = true;
			}
		}
		breakIt = false;
	}
	
	std::cout << topWords.size() << std::endl;
	
	for (std::map<std::string, int>::iterator topIt=topWords.begin(); topIt!=topWords.end(); ++topIt)
	{
		std::cout << topIt->first << " " << topIt->second << std::endl;
	}
}

void Application::UpdatePlayers()
{	
	#ifdef __linux__ 
		if(clock_gettime(CLOCK_MONOTONIC, &startLinux))
		{ /* handle error */ }
	#elif _WIN32
		start = clock();
	#else
		start = clock();
	#endif
	
	deltaTime = 0;
	
	int amount = 0;
	
	//check time hasn't reached 1 day and query = >= 100,000k
	while(deltaTime < 86400 && queryAmount < 100000)
	{
		//GET PLAYERS SUMMARY
		url = "http://api.steampowered.com/ISteamUser/GetPlayerSummaries/v0002/?key=" + api_key + "&steamids=";
		if(m_playersToAdd.size() < playerSteamApiCheckAmount)
		{
			amount = m_playersToAdd.size();
		}
		else
		{
			amount = playerSteamApiCheckAmount;
		}
		for(int i = 0; i < amount; i++)
		{
			url += m_playersToAdd.at(i) + ",";
		}		
		jsonSpare = api.GetData(url);
		queryAmount++;
		
		
		for(int i = 0; i < amount; i++)
		{
			
			steamid = jsonData["response"]["players"][i]["steamid"].asString();
			country = jsonData["response"]["players"][i]["loccountrycode"].asString();
			primaryClanID = jsonData["response"]["players"][i]["primaryclanid"].asString();
			
			timeCreated = api.UnixToDate(jsonData["response"]["players"][i]["timecreated"].asInt());
			//lastLogOff
			
		}

		//have a vector of players to look at
		//add 10 random players from different countries into the table
		//loop through the table, add players up to 100 amount into query
		//+1 to the query amount - cannot exceed 100,000k
		//for each player returned
		//check if its not private
		//add their data to the tables
		//check if game exists in table, if not try and add it
		//then update 
		//add their friends to the vector of players to look at
		//remove them from vector
		//loop
		
		
		#ifdef __linux__ 
		if(clock_gettime(CLOCK_MONOTONIC, &stopLinux))
			{ /* handle error */ }
			deltaTime += TimeSpecToSeconds(&stopLinux) - TimeSpecToSeconds(&startLinux);
		#elif _WIN32
			stop = clock();
			deltaTime += ((float)(clock() - start) / CLOCKS_PER_SEC);
		#else
			stop = clock();
			deltaTime += ((float)(clock() - start) / CLOCKS_PER_SEC);
		#endif
		
		
	}
	

	
	
	
	
}