#include "Application.h"

Application::Application()
{
	//TABLES
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
	m_mainTable.lock()->AddColumn("GameType", STRNG);
	m_mainTable.lock()->AddColumn("ProcessorRequirements", FLT);
	m_mainTable.lock()->AddColumn("GPURequirements", FLT);
	m_mainTable.lock()->AddColumn("RamRequirements", FLT);
	m_mainTable.lock()->AddColumn("GPURamRequirements", FLT);
	
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
	
	m_alphabet.push_back("Q");
	m_alphabet.push_back("W");
	m_alphabet.push_back("E");
	m_alphabet.push_back("R");
	m_alphabet.push_back("T");
	m_alphabet.push_back("Y");
	m_alphabet.push_back("U");
	m_alphabet.push_back("I");
	m_alphabet.push_back("O");
	m_alphabet.push_back("P");
	m_alphabet.push_back("A");
	m_alphabet.push_back("S");
	m_alphabet.push_back("D");
	m_alphabet.push_back("F");
	m_alphabet.push_back("G");
	m_alphabet.push_back("H");
	m_alphabet.push_back("J");
	m_alphabet.push_back("K");
	m_alphabet.push_back("L");
	m_alphabet.push_back("Z");
	m_alphabet.push_back("X");
	m_alphabet.push_back("C");
	m_alphabet.push_back("V");
	m_alphabet.push_back("B");
	m_alphabet.push_back("N");
	m_alphabet.push_back("M");
	m_alphabet.push_back("M");
	
	m_otherRemoves.push_back("+");
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
		m_gameTable.lock()->SetStringColumn("GameType", type);				
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
	std::locale loc;
	std::size_t found;
	
	std::vector<std::string> m_stringsFound;
	m_stringsToFind.push_back("GB");
	m_stringsToFind.push_back("GHZ");
	m_stringsToFind.push_back("MB");
	//m_stringsToFind.push_back("QUAD");
	m_stringsToFind.push_back("RAM");
	//m_stringsToFind.push_back("VRAM");
	m_stringsToFind.push_back("MHZ");
	
	m_ramToFind.push_back("RAM");
	m_processorToFind.push_back("GHZ");
	m_processorToFind.push_back("MHZ");
	m_sizeToFind.push_back("GB");
	m_sizeToFind.push_back("MB");
	m_sizeToFind.push_back("GHZ");
	m_sizeToFind.push_back("MHZ");
	
	std::cout << "Adding Games String" << std::endl;
	std::vector<std::string> games;
	std::vector<std::string> gamesID;
	std::vector<std::string> sentences;
	
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
			gamesID.push_back(objMain.row[0]);
		}
		objMain.ClearData();
	}
	
	

	
	StringValues type;
	if(gamesID.size() == games.size())
	{
		//BREAK UP INTO : 	
		std::string token;
		char delimiter = ':';
		for(int i = 0; i < games.size(); i++)
		{
			//make capital
			for (int n = 0; n < games.at(i).length(); n++)
			{
				games.at(i)[n] = std::toupper(games.at(i)[n],loc);
			}
			//break up into :
			std::istringstream tokenStream(games.at(i));
			while (std::getline(tokenStream, token, delimiter))
			{
				sentences.push_back(token);
			}
			
			std::cout << "GAME ID: " << gamesID.at(i) << std::endl;
			int processorCount = 0;
			int ramCount = 0;	
			std::vector<StringValues> values;
			for(int s = 0; s < sentences.size(); s++)
			{
				m_stringsFound = SplitWordIntoKeyString(sentences.at(s));
				//for(int i = 0; i < m_stringsFound.size(); i++)
				//{
				//	std::cout << m_stringsFound.at(i) << " ";
				//}
				type = CalculateScore(m_stringsFound);
				if(type.value > -1 && type.type != -1)
				{
					values.push_back(type);

					if(type.type == 0)
					{
						ramCount++;
					}
					if(type.type == 1)
					{
						processorCount++;
					}
				}				
			}	
			
			float RAM = 0;
			float GraphicsRAM = 0;
			float Processor = 0;
			float GraphicsProcessor = 0;

			
			for(int v = 0; v < values.size(); v++)
			{
				//RAM
				if(values.at(v).type == 0)
				{
					if(RAM == 0)
					{
						//if in GB
						if(values.at(v).size == 0)
						{
							RAM = values.at(v).value * 1024;
						}
						else
						{
							RAM = values.at(v).value;
						}
					}
					else
					{
						if(values.at(v).size == 0)
						{
							GraphicsRAM = values.at(v).value * 1024;
						}
						else
						{
							GraphicsRAM = values.at(v).value;
						}
					}
				}
				//PROCESSOR
				if(values.at(v).type == 1)
				{
					if(Processor == 0)
					{
						if(values.at(v).size == 2)
						{
							Processor = values.at(v).value * 1000;
						}
						else
						{
							Processor = values.at(v).value;
						}
					}
					else
					{
						if(values.at(v).size == 2)
						{
							GraphicsProcessor = values.at(v).value * 1000;
						}
						else
						{
							GraphicsProcessor = values.at(v).value;
						}
					}
				}
			}
			
			m_mainTable.lock()->SetIntColumn("GameID", std::stoi(gamesID.at(i)));
			m_mainTable.lock()->SetFloatColumn("ProcessorRequirements", Processor);
			call = m_mainTable.lock()->UpdateValues("Game", "ProcessorRequirements", FLT);
			call += m_mainTable.lock()->UpdateValues("Game", "GameID", INTEGER, 1);			
			bRet = objMain.execStatement(call);				
			if (!bRet)
			{					
				std::cout << "ERROR!" << std::endl;
			}
			

			m_mainTable.lock()->SetFloatColumn("GPURequirements", GraphicsProcessor);
			call = m_mainTable.lock()->UpdateValues("Game", "GPURequirements", FLT);
			call += m_mainTable.lock()->UpdateValues("Game", "GameID", INTEGER, 1);			
			bRet = objMain.execStatement(call);				
			if (!bRet)
			{					
				std::cout << "ERROR!" << std::endl;
			}
			
			m_mainTable.lock()->SetFloatColumn("RamRequirements", RAM);
			call = m_mainTable.lock()->UpdateValues("Game", "RamRequirements", FLT);
			call += m_mainTable.lock()->UpdateValues("Game", "GameID", INTEGER, 1);			
			bRet = objMain.execStatement(call);				
			if (!bRet)
			{					
				std::cout << "ERROR!" << std::endl;
			}
			
			
			m_mainTable.lock()->SetFloatColumn("GPURamRequirements", GraphicsRAM);
			call = m_mainTable.lock()->UpdateValues("Game", "GPURamRequirements", FLT);
			call += m_mainTable.lock()->UpdateValues("Game", "GameID", INTEGER, 1);			
			bRet = objMain.execStatement(call);				
			if (!bRet)
			{					
				std::cout << "ERROR!" << std::endl;
			}
			
			
			values.clear();
			sentences.clear();
			
			//analyse the words
			//give score for game
			//reset words vector
		} 
	}
	else
	{
		std::cout << "Games ID is not equal to Game Sentence Size" << std::endl;
	}	

}

std::vector<std::string> Application::SplitWordIntoKeyString(std::string _string)
{
	std::vector<std::string> returnVector;
	std::vector<int> marked;
	std::size_t found;
	bool deleteIt = true;

	
	//split into individual words
	std::locale loc;
	std::istringstream iss(_string);
	copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(returnVector));
	
	for(int i = 0; i < returnVector.size(); i++)
	{
		marked.push_back(0);
	}

	//for every word
	for(int i = 0; i < returnVector.size(); i++)
	{		
		for(int n = 0; n < m_stringsToFind.size(); n++)
		{
			//if it is a word we want to look at
			found = returnVector.at(i).find(m_stringsToFind.at(n));
			if (found!=std::string::npos)
			{
				//mark the word
				marked.at(i) = 1;
				n = m_stringsToFind.size();
			}				
		}	
	}
	
	

	//for all the words
	for(int i = 0; i < returnVector.size(); i++)
	{
		//and not equal to the first one to stop errors
		if(i > 0)
		{
			//check if the one in front of it is marked
			if(marked.at(i - 1) == 1)
			{
				if(IsUseful(returnVector.at(i)))
				{
					//make it equal to 2 so it wont carry on down the string e.g. 01111111 it would be 021200000	
					marked.at(i) = 2;
				}							
			}
		}
		//check if not last item
		if(i < returnVector.size() - 1)
		{
			//otherwise, check if item behind it is marked
			if(marked.at(i + 1) == 1)
			{
				if(IsUseful(returnVector.at(i)))
				{
					//make it equal to 2 so it wont carry on down the string e.g. 01111111 it would be 021200000	
					marked.at(i) = 2;
				}
			}
		}
	}

	for(int i = 0; i < returnVector.size(); i++)
	{			//if nothing either side is marked then delete
		
		if(marked.at(i) == 0)
		{
			returnVector.erase (returnVector.begin()+i);
			marked.erase (marked.begin()+i);
			i--;
		}	
	}	
	
	return returnVector;
}

StringValues Application::CalculateScore(std::vector<std::string> _strings)
{
	StringValues returnType;
	float score = 0;	
	int markerType = -1;
	int markerNumber = -1;
	int markerSize = -1;
	
	if(_strings.size() > 0)
	{		
		//for every string
		for(int i = 0; i < _strings.size(); i++)
		{
			//for every possible ram word
			for(int n = 0; n < m_ramToFind.size(); n++)
			{
				//if the string == the ram word then is is a ram sentence
				if (_strings.at(i).find(m_ramToFind.at(n)) != std::string::npos)
				{
					score = 1;
					markerType = 0;
				}					
			}
			//for every possible processor word
			for(int n = 0; n < m_processorToFind.size(); n++)
			{
				//if the string == the processor word then is is a processor sentence
				if (_strings.at(i).find(m_processorToFind.at(n)) != std::string::npos)
				{
					score = 1;
					markerType = 1;
				}
			}
			for(int n = 0; n < m_sizeToFind.size(); n++)
			{
				//if the string == the size word then is is a size word
				if (_strings.at(i).find(m_sizeToFind.at(n)) != std::string::npos)
				{
					score = 1;
					markerSize = n;
				}
			}
			if(markerNumber == -1)
			{
				if(IsUseful(_strings.at(i)))
				{
					markerNumber = i;
				}
			}			
		}
	}
	
	if(markerNumber != -1)
	{
		returnType.value = ConvertToNumber(_strings.at(markerNumber));
	}
	else
	{
		returnType.value = -1;
	}
	

	returnType.type = markerType;
	returnType.size = markerSize;
	

	return returnType;
}

float Application::ConvertToNumber(std::string _number)
{
	float returnFloat = 0;
	int marker = -1;
	std::size_t found;
  
	for(int i = 0; i < m_alphabet.size(); i++)
	{
		found = _number.find(m_alphabet.at(i));
		if (found!=std::string::npos)
		{			
			_number.erase(_number.begin() + found);			
		}
	}
	for(int i = 0; i < m_otherRemoves.size(); i++)
	{
		found = _number.find(m_otherRemoves.at(i));
		if (found!=std::string::npos)
		{			
			_number.erase(_number.begin() + found);			
		}
	}
	
	for(int i = 0; i < _number.size(); i++)
	{
		if(_number.at(i) == '.' || _number.at(i) == ',')
		{
			marker = i;
		}
	}
	
	int digit = 0;
	int number = 0;
	//if it has a decimal point

	for(int i = 0; i < _number.size(); i++)
	{
		if(i != marker)
		{
			if(marker != -1)
			{
				if(i < marker)
				{
					digit = marker - i;
				}
				else
				{
					digit = marker - i + 1;
				}
			}
			else
			{
				digit = _number.size() - i;	
			}
					
			number = GetNumber(_number, i);			
			if(number > -1)
			{
				returnFloat += pow(10, digit - 1) * number;
			}
		}			
	}	
	
	return returnFloat;
	
	//erase any letters
	
}

int Application::GetNumber(std::string _number, int location)
{
	if(_number.at(location) == '0')
	{
		return 0;
	}
	if(_number.at(location) == '1')
	{
		return 1;
	}
	if(_number.at(location) == '2')
	{
		return 2;
	}
	if(_number.at(location) == '3')
	{
		return 3;
	}
	if(_number.at(location) == '4')
	{
		return 4;
	}
	if(_number.at(location) == '5')
	{
		return 5;
	}
	if(_number.at(location) == '6')
	{
		return 6;
	}
	if(_number.at(location) == '7')
	{
		return 7;
	}
	if(_number.at(location) == '8')
	{
		return 8;
	}
	if(_number.at(location) == '9')
	{
		return 9;
	}
	return -1;
}

bool Application::IsUseful(std::string _string)
{
	bool containsLetter = false;
	//checks if the value contains a number - this is to remove words like OPENGL or CARD which dont help 
	if (_string.find('0') != std::string::npos ||
        _string.find('1') != std::string::npos ||
        _string.find('2') != std::string::npos ||
        _string.find('3') != std::string::npos ||
        _string.find('4') != std::string::npos ||
        _string.find('5') != std::string::npos ||
        _string.find('6') != std::string::npos ||
        _string.find('7') != std::string::npos ||
        _string.find('8') != std::string::npos ||
        _string.find('.') != std::string::npos ||
        _string.find('9') != std::string::npos)
    {        
		for(int i = 0; i < m_alphabet.size(); i++)
		{
			if (_string.find(m_alphabet.at(i)) != std::string::npos)
			{
				containsLetter = true;
			}
		}
		//if it contains a letter it means its not a pure number
		if(containsLetter)
		{
			//check if it contains a key word
			for(int i = 0; i < m_stringsToFind.size(); i++)
			{
				if (_string.find(m_stringsToFind.at(i)) != std::string::npos)
				{
					return true;
				}
			}
		}
		else
		{
			return true;
		}
    }
	
	return false;
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