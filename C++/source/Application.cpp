#include "Application.h"
#include "TextReader.h"

Application::Application()
{
	//TABLES
	m_countryTable.lock()->AddColumn("CountryName", STRNG);
	m_countryTable.lock()->AddColumn("Count", DUPLICATE_ADD);
	
	m_gameTable.lock()->AddColumn("GameID", INTEGER);
	m_gameTable.lock()->AddColumn("GameName", STRNG);
	m_gameTable.lock()->AddColumn("Price", FLT);
	m_gameTable.lock()->AddColumn("AgeLimit", STRNG);
	m_gameTable.lock()->AddColumn("MetaCritic", INTEGER);
	m_gameTable.lock()->AddColumn("Windows", INTEGER);
	m_gameTable.lock()->AddColumn("Mac", INTEGER);
	m_gameTable.lock()->AddColumn("Linux", INTEGER);
	m_gameTable.lock()->AddColumn("ReleaseDate", STRNG);
	m_gameTable.lock()->AddColumn("Requirements", STRNG);
	m_gameTable.lock()->AddColumn("GameType", STRNG);
	m_gameTable.lock()->AddColumn("ProcessorRequirements", FLT);
	m_gameTable.lock()->AddColumn("GPURequirements", FLT);
	m_gameTable.lock()->AddColumn("RamRequirements", FLT);
	m_gameTable.lock()->AddColumn("GPURamRequirements", FLT);
	m_gameTable.lock()->AddColumn("FinalRequirements", FLT);
	m_gameTable.lock()->AddColumn("AvailableOnStore", INTEGER);
	m_gameTable.lock()->AddColumn("Website", STRNG);
	m_gameTable.lock()->AddColumn("HeaderImage", STRNG);
	
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
	
	m_apiCounter.lock()->AddColumn("Value", INTEGER);
	
	m_gameCountryCount.lock()->AddColumn("GameID", INTEGER);
	m_gameCountryCount.lock()->AddColumn("CountryID", INTEGER);
	m_gameCountryCount.lock()->AddColumn("Count", DUPLICATE_ADD);
	
	m_playersMain.lock()->AddColumn("SteamID", ENCRYPT);
	m_playersMain.lock()->AddColumn("PrimaryClan", STRNG);
	m_playersMain.lock()->AddColumn("DateCreated", STRNG);
	m_playersMain.lock()->AddColumn("AveragePCRequirements", FLT);
	m_playersMain.lock()->AddColumn("AverageMetacritic", FLT);
	m_playersMain.lock()->AddColumn("AveragePrice", FLT);
	m_playersMain.lock()->AddColumn("MostPlayedGame", STRNG);
	m_playersMain.lock()->AddColumn("MostPlayed2Weeks", STRNG);
	m_playersMain.lock()->AddColumn("MostPopularGenre", INTEGER);
	m_playersMain.lock()->AddColumn("MostPopularCategory", INTEGER);
	m_playersMain.lock()->AddColumn("Country", INTEGER);
	
	m_countriesTable.lock()->AddColumn("CountryID", INTEGER);
	m_countriesTable.lock()->AddColumn("SteamID", STRNG);
	m_countriesTable.lock()->AddColumn("Name", STRNG);
	m_countriesTable.lock()->AddColumn("3LetterCode", STRNG);
	
	
	m_playersFriends.lock()->AddColumn("SteamID1", ENCRYPT);
	m_playersFriends.lock()->AddColumn("SteamID2", ENCRYPT);
	m_playersFriends.lock()->AddColumn("FriendSince", STRNG);
	m_playersFriends.lock()->AddColumn("FriendRating", FLT);

	
	m_gamesOwned.lock()->AddColumn("GameID", STRNG);	
	m_gamesOwned.lock()->AddColumn("PlayerID", ENCRYPT);
	m_gamesOwned.lock()->AddColumn("MinutesPlayedTotal", INTEGER);	
	m_gamesOwned.lock()->AddColumn("MinutesPlayed2Weeks", INTEGER);	
	
	m_publishersTable.lock()->AddColumn("PublisherID", INTEGER);
	m_publishersTable.lock()->AddColumn("PublisherName", STRNG);
	
	m_developersTable.lock()->AddColumn("DeveloperID", INTEGER);
	m_developersTable.lock()->AddColumn("DeveloperName", STRNG);
	
	m_gameToDeveloperTable.lock()->AddColumn("DeveloperID", INTEGER);
	m_gameToDeveloperTable.lock()->AddColumn("GameID", INTEGER);
	
	m_gameToPublisherTable.lock()->AddColumn("PublisherID", INTEGER);
	m_gameToPublisherTable.lock()->AddColumn("GameID", INTEGER);
	
	m_playersToCheck.lock()->AddColumn("SteamID", ENCRYPT);
	m_playersToCheck.lock()->AddColumn("Added", INTEGER);
	m_playersToCheck.lock()->AddColumn("Evaluating", INTEGER);
	m_playersToCheck.lock()->AddColumn("Count", INTEGER);
	
	m_gamePlayerCount.lock()->AddColumn("GameID", INTEGER);
	m_gamePlayerCount.lock()->AddColumn("PlayerAmount", INTEGER);
	
	m_gameRules.lock()->AddColumn("GameID1", INTEGER);
	m_gameRules.lock()->AddColumn("GameID2", INTEGER);
	m_gameRules.lock()->AddColumn("Count", DUPLICATE_ADD);
		
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
	
	m_numbers.push_back('0');
	m_numbers.push_back('1');
	m_numbers.push_back('2');
	m_numbers.push_back('3');
	m_numbers.push_back('4');
	m_numbers.push_back('5');
	m_numbers.push_back('6');
	m_numbers.push_back('7');
	m_numbers.push_back('8');
	m_numbers.push_back('9');
	m_numbers.push_back('.');
	m_numbers.push_back(',');
}

Application::~Application()
{
	
}

void Application::APIResetter()
{
	bool usedEth1 = false;
	bool usedEth2 = false;
	bool usedEth3 = false;
	
	int queryAmount = 0;
	bool dayOver = false;
	TimeStruct time;
	
	int counter = 0; //used to regulate the calling with different ips more often
	
	counter = std::stoi(TextReader::ReadPassword("callamount.txt"));
	
	
	
	while(true)
	{
		if(!dayOver)		
		{
			std::string networkToUse = TextReader::ReadPassword("..//passwords/Network.txt");
			if(networkToUse == "net2")
			{
				api_key = TextReader::ReadPassword("..//passwords/API2.txt");
			}
			if(networkToUse == "net3")
			{
				api_key = TextReader::ReadPassword("..//passwords/API3.txt");
			}
			if(networkToUse == "net1")
			{
				api_key = TextReader::ReadPassword("..//passwords/API1.txt");
			}
			
			time = GetTime();
			if(time.hour == 14 && time.minute == 0)
			{
				counter = 0;
			}
			
			sleep(15);
			call = statement.GetSize("APICallCounter");
			bRet = objMain.getDataStatement(call);
			if (!bRet)
			{					
				std::cout << "ERROR!" << std::endl;
			}
			else
			{
				while ((objMain.row = mysql_fetch_row(objMain.m_result)) != NULL)
				{
					queryAmount = std::stoi(objMain.row[0]);
				}	
				objMain.ClearData();
			}
			
			url =  "http://api.ipify.org/?format=json";			
			jsonData = api.GetData(url);
			std::cout << jsonData["ip"] << " " << queryAmount << " API Key Starts with:" << api_key[0] << api_key[1] << " API Iteration: " << counter << std::endl;	
			
			if(queryAmount > 2500)
			{
				call = "TRUNCATE `main`.`APICallCounter`";
				bRet = objMain.execStatement(call);
				if (!bRet)
				{					
					std::cout << "ERROR!" << std::endl;
				}
				
				if(!usedEth1)
				{
					usedEth1 = true;
					std::ofstream ofs;
					ofs.open("..//passwords/Network.txt", std::ofstream::out | std::ofstream::trunc);
					ofs << "net2";
					ofs.close();
					
					api_key = TextReader::ReadPassword("..//passwords/API2.txt");
				}
				else
				{
					if(!usedEth2)
					{
						usedEth2 = true;
						std::ofstream ofs;
						ofs.open("..//passwords/Network.txt", std::ofstream::out | std::ofstream::trunc);
						ofs << "net3";
						ofs.close();
						
						api_key = TextReader::ReadPassword("..//passwords/API3.txt");
					}
					else
					{
						if(!usedEth3)
						{														
							std::ofstream ofs;
							ofs.open("..//passwords/Network.txt", std::ofstream::out | std::ofstream::trunc);
							ofs << "net1";
							ofs.close();
							api_key = TextReader::ReadPassword("..//passwords/API1.txt");	
							counter++;
							usedEth1 = false;
							usedEth2 = false;
							usedEth3 = false;	
							objMain.CloseConnection();
							objMain.OpenConnection();
						}
					}
				}
				if(counter > 40)
				{
					dayOver = true;
					
					m_apiCounter.lock()->SetIntColumn("Value", 1);	
					for(int z = 0; z < 100000; z++)
					{		
						if(z == 0)
						{
							call = m_apiCounter.lock()->SetValues();
						}
						else
						{
							call += m_apiCounter.lock()->SetValues(1);
						}
						
					}
					//std::cout << call << std::endl;
					bRet = objMain.execStatement(call);				
					if (!bRet)
					{					
						std::cout << "ERROR!" << std::endl;
					}
				}
			}
		}
		else
		{
			std::cout << "Day over if statement" << std::endl;
			objMain.CloseConnection();
			sleep(55);
			time = GetTime();		
			if(time.hour == 14 && time.minute == 0)
			{
				objMain.OpenConnection();
				//RESET API CALL AMOUNT every 24hr
				call = "TRUNCATE `main`.`APICallCounter`";
				bRet = objMain.execStatement(call);
				if (!bRet)
				{					
					std::cout << "ERROR!" << std::endl;
				}
				dayOver = false;
				counter = 0;
				usedEth1 = false;
				usedEth2 = false;
				usedEth3 = false;
			}
		}
		
		
		
		
		
	}
}

TimeStruct Application::GetTime()
{
	time_t theTime = time(NULL);
	struct tm *aTime = localtime(&theTime);

	TimeStruct temp;
	temp.hour = aTime->tm_hour;
	temp.minute = aTime->tm_min;

	return temp;
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
			m_countries[objMain.row[1]] = std::stoi(objMain.row[0]);
		}
		objMain.ClearData();
	}
	
	//LOAD PUBLISHERS INTO PROGRAM
	call = statement.GetData("Publishers");	
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
			m_publishers[objMain.row[1]] = std::stoi(objMain.row[0]);
		}
		objMain.ClearData();
	}
	
	//LOAD DEVELOPERS INTO PROGRAM
	call = statement.GetData("Developers");	
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
			m_developers[objMain.row[1]] = std::stoi(objMain.row[0]);
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
			GamesDownload temp;
			temp.price = std::stof(objMain.row[2]);
			temp.finalRequirements = std::stof(objMain.row[16]);
			temp.metaCritic = std::stoi(objMain.row[5]);
			temp.releaseDate = objMain.row[9];
			m_games[std::stoi(objMain.row[0])] = temp;
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
	
	int time = 300;
	
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
			/*
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
			*/
			
			if(CheckSteamIDs(m_gameIDs.at(i)))
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
	url =  "http://store.steampowered.com/api/appdetails?appids=" + gameIDString + "&cc=gb";			
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

		
		bool availableOnStore = true;	
		//GET THE PRICE - EVERYTHING IS IN GBP
		if(jsonData[gameIDString]["data"]["is_free"].asInt())
		{
			price = 0;
		}
		else
		{
			//need to check if it exists otherwise app is no longer on the store
			if(jsonData[gameIDString]["data"].isMember("price_overview"))
			{
				price = jsonData[gameIDString]["data"]["price_overview"]["final"].asDouble() / 100;
			}
			else
			{
				availableOnStore = false;	
			}			
		}
				
		//ADD WEBSITE INFORMATION
		websiteAddress = jsonData[gameIDString]["data"]["website"].asString();
		//ADD HEADER INFORMATION
		headerImageAddress = jsonData[gameIDString]["data"]["header_image"].asString();
		
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
		
		//COLLECT DEVELOPERS
		if(jsonData[gameIDString]["data"]["developers"].size() > 0)
		{
			std::string developer;
			for(int g = 0; g < jsonData[gameIDString]["data"]["developers"].size(); g++)
			{
				developer = jsonData[gameIDString]["data"]["developers"][g].asString();
					
				if(developer.size() > 0)
				{
					std::locale loc;
					if(developer.at(developer.size() - 1) == ' ')
					{
						developer.erase (developer.begin() + developer.size() - 1);
					}
					for (std::string::size_type n = 0; n < developer.length(); n++)
					{
						developer[n] = std::toupper(developer[n],loc);
					}
				}
				
				if ( m_developers.find(developer) == m_developers.end() ) 
				{					
					m_developers[developer] = m_developers.size();

					m_developersTable.lock()->SetIntColumn("DeveloperID", m_developers[developer]);
					m_developersTable.lock()->SetStringColumn("DeveloperName", developer);	
					call = statement.Call("Developers");
					bRet = objMain.execStatement(call);
					if (!bRet)
					{					
						std::cout << "ERROR!" << std::endl;
					}
				} 
			
				//add game to developers table
				m_gameToDeveloperTable.lock()->SetIntColumn("GameID", _id);
				m_gameToDeveloperTable.lock()->SetIntColumn("DeveloperID", m_developers[developer]);	
				call = statement.Call("GameToDeveloper");				
				bRet = objMain.execStatement(call);
				if (!bRet)
				{					
					std::cout << "ERROR!" << std::endl;
				}
			}
		}
		
		

		//COLLECT PUBLISHERS
		if(jsonData[gameIDString]["data"]["publishers"].size() > 0)
		{
			std::string publisher;
			for(int g = 0; g < jsonData[gameIDString]["data"]["publishers"].size(); g++)
			{				
				publisher = jsonData[gameIDString]["data"]["publishers"][g].asString();
				
				if(publisher.size() > 0)
				{
					std::locale loc;
					
					if(publisher.at(publisher.size() - 1) == ' ')
					{
						publisher.erase (publisher.begin() + publisher.size() - 1);
					}
					
					for (std::string::size_type n = 0; n < publisher.length(); n++)
					{
						publisher[n] = std::toupper(publisher[n],loc);
					}

				}
				
				if ( m_publishers.find(publisher) == m_publishers.end() ) 
				{			
					m_publishers[publisher] = m_publishers.size();

					m_publishersTable.lock()->SetIntColumn("PublisherID", m_publishers[publisher]);
					m_publishersTable.lock()->SetStringColumn("PublisherName", publisher);	
					call = statement.Call("Publishers");	
					bRet = objMain.execStatement(call);
					if (!bRet)
					{					
						std::cout << "ERROR!" << std::endl;
					}
				} 
				
				//add game to publisher table
				m_gameToPublisherTable.lock()->SetIntColumn("GameID", _id);
				m_gameToPublisherTable.lock()->SetIntColumn("PublisherID", m_publishers[publisher]);	
				call = statement.Call("GameToPublisher");				
				bRet = objMain.execStatement(call);
				if (!bRet)
				{					
					std::cout << "ERROR!" << std::endl;
				}
			}
		}
		/*
		//ADD GAME INFORMATION
		m_gameTable.lock()->SetIntColumn("GameID", _id);
		m_gameTable.lock()->SetStringColumn("GameName", name);				
		
		m_gameTable.lock()->SetStringColumn("AgeLimit", ageRequirement);
		m_gameTable.lock()->SetIntColumn("MetaCritic", metaCritic);
		m_gameTable.lock()->SetIntColumn("Windows", windows);
		m_gameTable.lock()->SetIntColumn("Mac", mac);
		m_gameTable.lock()->SetIntColumn("Linux", linux);
		m_gameTable.lock()->SetStringColumn("ReleaseDate", date);
		m_gameTable.lock()->SetStringColumn("Requirements", requirements);
		m_gameTable.lock()->SetStringColumn("GameType", type);	
		
		m_gameTable.lock()->SetStringColumn("Website", websiteAddress);		
		m_gameTable.lock()->SetStringColumn("HeaderImage", headerImageAddress);
		
		
		if(availableOnStore)
		{
			m_gameTable.lock()->SetIntColumn("AvailableOnStore", 1);
			m_gameTable.lock()->SetFloatColumn("Price", price);
		}
		else
		{
			m_gameTable.lock()->SetIntColumn("AvailableOnStore", 0);
			m_gameTable.lock()->SetFloatColumn("Price", -1);
		}
		
		
		
		call = statement.Call("Game");	
		
		//std::cout << call << std::endl;
		
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
		*/
	}
	else
	{
		return false;
	}
			
	
	return true;
}

void Application::SetPCRequirements()
{
	struct gameValues
	{
		std::string gameID;
		double processor, ram, gpuProc, gpuRam;
	};
	std::vector<gameValues> m_gameValues;
	//12,12,13,14 columns
	call = statement.GetData("Game");	
	bRet = objMain.getDataStatement(call);
	if (!bRet)
	{					
		std::cout << "ERROR!" << std::endl;
	}
	else
	{
		while ((objMain.row = mysql_fetch_row(objMain.m_result)) != NULL)
		{
			gameValues temp;
			temp.gameID = objMain.row[0];
			temp.processor = std::stod(objMain.row[12]);
			temp.gpuProc = std::stod(objMain.row[13]);
			temp.ram = std::stod(objMain.row[14]);
			temp.gpuRam = std::stod(objMain.row[15]);
			m_gameValues.push_back(temp);
		}
		objMain.ClearData();
	}	
	
	std::cout << m_gameValues.size() << std::endl;
	
	for(int i = 0; i < m_gameValues.size(); i++)
	{

		float count = 0;
		float score = 0;
		
		if(m_gameValues.at(i).processor != 0)
		{
			count++;
			score += GetScore(m_gameValues.at(i).processor, 500, 9);
		}
		
		if(m_gameValues.at(i).ram != 0)
		{
			count++;
			score += GetScore(m_gameValues.at(i).ram, 1000, 9);
		}
		
		if(m_gameValues.at(i).gpuProc != 0)
		{
			count++;
			score += GetScore(m_gameValues.at(i).gpuProc, 500, 7);
		}
		
		if(m_gameValues.at(i).gpuRam != 0)
		{
			count++;
			score += GetScore(m_gameValues.at(i).gpuRam, 1000, 7);
		}
		
		if(count > 0)
		{
			score = score / count;
			
			
			m_mainTable.lock()->SetIntColumn("GameID", std::stoi(m_gameValues.at(i).gameID));
			m_mainTable.lock()->SetFloatColumn("FinalRequirements", score);
			call = m_mainTable.lock()->UpdateValues("Game", "FinalRequirements", FLT);
			call += m_mainTable.lock()->UpdateValues("Game", "GameID", INTEGER, 1);	

			//std::cout << m_gameValues.at(i).processor << " " << m_gameValues.at(i).ram << " " << m_gameValues.at(i).gpuProc << " " << m_gameValues.at(i).gpuRam << " " << count << std::endl;
			
			//std::cout << call << std::endl;
			
			if(m_gameValues.at(i).gameID == "6400")
			{
				std::cout << GetScore(m_gameValues.at(i).ram, 1000, 9) << std::endl;
				system("PAUSE");
				
			}
			
			
			bRet = objMain.execStatement(call);				
			if (!bRet)
			{					
				std::cout << "ERROR!" << std::endl;
			}
			
			
		}
		else
		{
			score = 0;
		}
		
		
		
		
		
	}
}

float Application::GetScore(double value, int step, int amount)
{
	float returnValue = (value / step) * (100 / amount);
	
	if(returnValue > 100)
	{
		returnValue = 100;
	}
	
	return returnValue;
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
	//call += statement.AddStringCondition("GameType", "game");	
	bRet = objMain.getDataStatement(call);
	if (!bRet)
	{					
		std::cout << "ERROR!" << std::endl;
	}
	else
	{
		while ((objMain.row = mysql_fetch_row(objMain.m_result)) != NULL)
		{
			games.push_back(objMain.row[10]);
			gamesID.push_back(objMain.row[0]);
		}
		objMain.ClearData();
	}
	
	

	
	StringValues type;
	if(gamesID.size() == games.size())
	{
		//BREAK UP INTO : 	
		std::string token;
		char delimiter = ',';
		for(int i = 0; i < games.size(); i++)
		{
			//make capital
			for (int n = 0; n < games.at(i).length(); n++)
			{
				games.at(i)[n] = std::toupper(games.at(i)[n],loc);
			}
			
			//break up into :
			std::size_t found = games.at(i).find(":");
			if(found!=std::string::npos)
			{
				delimiter = ':';
			}
			else
			{
				delimiter = ',';
			}
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
			
			/*
			if(gamesID.at(i) == "416130")
			{
				system("PAUSE");
			}
			*/
			
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
		/*
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
		*/
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
			//for every size word
			for(int n = 0; n < m_sizeToFind.size(); n++)
			{
				//if the string == the size word then is is a size word i.e. GB, MB
				if (_strings.at(i).find(m_sizeToFind.at(n)) != std::string::npos)
				{
					score = 1;
					markerSize = n;
				}
			}
			if(IsUseful(_strings.at(i)))
			{
				markerNumber = i;
			}
			
			//std::cout << _strings.at(i) << std::endl;
			
		}
	}
	
	//std::cout << "new setnecne" << std::endl;
	
	if(markerNumber != -1)
	{
		//std::cout << _strings.at(markerNumber) << std::endl;
		returnType.value = ConvertToNumber(_strings.at(markerNumber));
		//std::cout << returnType.value << std::endl;
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
	
	bool erase = true;
	for(int i = 0; i < _number.size();)
	{	
		erase = true;
		if(_number.at(i) == '.' || _number.at(i) == ',')
		{
			marker = i;
		}
		for(int n = 0; n < m_numbers.size(); n++)
		{
			if(_number.at(i) == m_numbers.at(n))
			{
				erase = false;
				n = m_numbers.size();
			}
		}
		if(erase)
		{
			_number.erase(_number.begin() + i);
		}	
		else
		{
			i++;
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
	//structs to store results from the json query
	struct Friends
	{
		std::string steamID, friendSince;
	};	
	struct GamesPlayed
	{
		std::string appID;
		int appNumber;
		int playtimeForever, playtime2Weeks;
	};
	
	int amount = 0;	
	bool run = true;
	
	int resetMYSQLConnectionCounter = 0;
	
	//check time hasn't reached 1 day and query = >= 100,000k
	while(run)
	{
		call = statement.GetSize("APICallCounter");
		bRet = objMain.getDataStatement(call);
		if (!bRet)
		{					
			std::cout << "ERROR!" << std::endl;
		}
		else
		{
			while ((objMain.row = mysql_fetch_row(objMain.m_result)) != NULL)
			{
				queryAmount = std::stoi(objMain.row[0]);
			}	
			objMain.ClearData();
		}
		
	
		while(queryAmount < 100000)
		{
			//for all in the vector
			//check if they haven't already been added
			//if they have then remove them
			
			call = statement.GetSize("APICallCounter");
			bRet = objMain.getDataStatement(call);
			if (!bRet)
			{					
				std::cout << "ERROR!" << std::endl;
			}
			else
			{
				while ((objMain.row = mysql_fetch_row(objMain.m_result)) != NULL)
				{
					queryAmount = std::stoi(objMain.row[0]);
				}	
				objMain.ClearData();
			}
			if(queryAmount > 99999)
			{
				break;			
			}
			else
			{
				queryAmount = 0;
			}
			
			std::string networkToUse = TextReader::ReadPassword("..//passwords/Network.txt");
			if(networkToUse == "net2")
			{
				api_key = TextReader::ReadPassword("..//passwords/API2.txt");
			}
			if(networkToUse == "net3")
			{
				api_key = TextReader::ReadPassword("..//passwords/API3.txt");
			}
			if(networkToUse == "net1")
			{
				api_key = TextReader::ReadPassword("..//passwords/API1.txt");
			}
			
			if(TextReader::ReadPassword("run.txt") == "0")
			{
				run = false;
				queryAmount = 100000;
				break;
			}
			
			resetMYSQLConnectionCounter++;			
			if(resetMYSQLConnectionCounter > 50)
			{
				objMain.CloseConnection();
				objMain.OpenConnection();
				resetMYSQLConnectionCounter = 0;
			}
			
			
			int count = 0;
			call = statement.GetData("PlayersToCheck", true, "SteamID");
			call += statement.AddNumberCondition("Added", 0);	
			call += statement.AddNumberCondition("Evaluating", 0, 1);	
			call += statement.AddNumberCondition("Count", 1, 2, "<");	
			call += statement.AddLimit("100");	
			bRet = objMain.getDataStatement(call);
			if (!bRet)
			{					
				std::cout << "ERROR!" << std::endl;
			}
			else
			{
				while ((objMain.row = mysql_fetch_row(objMain.m_result)) != NULL && count <= playerSteamApiCheckAmount)
				{
					count++;
					m_playersToAdd.push_back(objMain.row[0]);
				}	
				objMain.ClearData();
			}
			
			//GET PLAYERS SUMMARY
			url = "http://api.steampowered.com/ISteamUser/GetPlayerSummaries/v0002/?key=" + api_key + "&steamids=";
			//add all the steam users to check
			for(int i = 0; i < m_playersToAdd.size(); i++)
			{
				url += m_playersToAdd.at(i) + ",";
			}
			std::cout << resetMYSQLConnectionCounter << std::endl;
			std::cout << "Set Players To Evaluating" << std::endl;
			//SET THE PLAYERS YOU ARE CHECKING TO EVALUATING
			call = "";	
			if(m_playersToAdd.size() > 2)
			{
				m_playersToCheck.lock()->SetEncryptColumn("SteamID", m_playersToAdd.at(0));				
				m_playersToCheck.lock()->SetIntColumn("Evaluating", 1);		
				
				call += m_playersToCheck.lock()->UpdateValues("PlayersToCheck", "Evaluating", INTEGER);

				call += m_playersToCheck.lock()->UpdateValues("PlayersToCheck", "SteamID", ENCRYPT, 1);

				
				m_playersToCheck.lock()->SetEncryptColumn("SteamID", m_playersToAdd.at(1));
				call += m_playersToCheck.lock()->UpdateValues("PlayersToCheck", "SteamID", ENCRYPT, 2);
				
				
				for(int n = 2; n < m_playersToAdd.size(); n++)
				{
					m_playersToCheck.lock()->SetEncryptColumn("SteamID", m_playersToAdd.at(n));
					call += m_playersToCheck.lock()->UpdateValues("PlayersToCheck", "SteamID", ENCRYPT, 3);		
				}
				
				//std::cout << call << std::endl;
				
				bRet = objMain.execStatement(call);				
				if (!bRet)
				{					
					std::cout << "ERROR!" << std::endl;
				}
			}	

			
			
			std::cout << "Set Players To Data" << std::endl;
			//get their data
			jsonSpare = api.GetData(url);
			queryAmount++;
			
			//for every steam user
			for(int i = 0; i < m_playersToAdd.size(); i++)
			{
				//if the player has a public profile
				if(jsonSpare["response"]["players"][i]["communityvisibilitystate"].asInt() == 3)
				{
					//get basic data
					steamid = jsonSpare["response"]["players"][i]["steamid"].asString();
					primaryClanID = jsonSpare["response"]["players"][i]["primaryclanid"].asString();			
					timeCreated = api.UnixToDate(jsonSpare["response"]["players"][i]["timecreated"].asInt());
					locCountryCode = jsonSpare["response"]["players"][i]["loccountrycode"].asString();
					locStateCode = jsonSpare["response"]["players"][i]["locstatecode"].asString();			
					if(locStateCode == "")
					{
						locStateCode = "Unknown";
					}
					if(locCountryCode == "")
					{
						locCountryCode = "Unknown";
					}	

					std::cout << "SteamID: " << steamid << " Connection Counter: " << resetMYSQLConnectionCounter << std::endl;

					std::map<std::string, int>::iterator it = m_countries.find(locCountryCode);
					if(it != m_countries.end())
					{
						countryID = it->second;
					}
					else
					{
						m_countries[locCountryCode] = m_countries.size() + 1;
						m_countriesTable.lock()->SetIntColumn("CountryID", m_countries.size());
						m_countriesTable.lock()->SetStringColumn("SteamID", locCountryCode);					
						call = m_countriesTable.lock()->SetValues();					
						bRet = objMain.execStatement(call);				
						if (!bRet)
						{					
							std::cout << "ERROR!" << std::endl;
						}
						countryID = m_countries.size();
					}
					
					
					lastLogOff = api.UnixToDate(jsonSpare["response"]["players"][i]["lastlogoff"].asInt());
					
					std::vector<Friends> m_friends;
					std::vector<GamesPlayed> m_playerGames;
					int mostPlayed = 0;
					std::string mostPlayedID = "0";
					int mostPlayed2Weeks = 0;
					std::string mostPlayed2WeeksID = "0";
						
					std::cout << "Getting Players Games" << std::endl;			
					//get all their games			
					url = "http://api.steampowered.com/IPlayerService/GetOwnedGames/v0001/?key=" + api_key + "&steamid=" + steamid + "&include_played_free_games=1&include_appinfo=1&format=json";			
					jsonData = api.GetData(url);					
					queryAmount++;
					int size = jsonData["response"]["game_count"].asInt();	
					
					if(size > 0)
					{				
						
						//for every game, if it has a playtime get the playtime, get the 2 week playtime
						for(int f = 0; f < size; f++)
						{		
							GamesPlayed temp;
							temp.appID = jsonData["response"]["games"][f]["appid"].asString();
							temp.appNumber = jsonData["response"]["games"][f]["appid"].asInt();
							//check if playtime forever exists
							if(jsonData["response"]["games"][f].isMember("playtime_forever"))
							{
								temp.playtimeForever = jsonData["response"]["games"][f]["playtime_forever"].asInt();
								if(temp.playtimeForever < 0)
								{
									temp.playtimeForever = 0;
								}
								if(temp.playtimeForever > mostPlayed)
								{
									mostPlayed = temp.playtimeForever;
									mostPlayedID = temp.appID;
								}
							}
							else
							{
								temp.playtimeForever = 0;
							}
							//check if playtime 2 weeks exists
							if(jsonData["response"]["games"][f].isMember("playtime_2weeks"))
							{
								temp.playtime2Weeks = jsonData["response"]["games"][f]["playtime_2weeks"].asInt();
								if(temp.playtime2Weeks < 0)
								{
									temp.playtime2Weeks = 0;
								}
								if(temp.playtime2Weeks > mostPlayed2Weeks)
								{
									mostPlayed2Weeks = temp.playtime2Weeks;
									mostPlayed2WeeksID = temp.appID;
								}
							}
							else
							{
								temp.playtime2Weeks = 0;
							}
							m_playerGames.push_back(temp);
						}	

						double averagePCRequirements = 0;
						double averagePrice = 0;
						double averageMetaCritic = 0;
						double averageReleaseDate = 0;
						double requirementsCount = 0;
						double priceCount = 0;
						double criticCount = 0;
						double releaseCount = 0;
						double totalTimePlaying = 0;
						double twoWeekPlaytime = 0;
						
						for(int n = 0; n < m_playerGames.size(); n++)
						{	
							if(m_playerGames.at(n).playtimeForever > 0)
							{
								totalTimePlaying += m_playerGames.at(n).playtimeForever;
							}
							if(m_playerGames.at(n).playtime2Weeks > 0)
							{
								twoWeekPlaytime += m_playerGames.at(n).playtime2Weeks;
							}					
						}
						
						//std::cout << "Calculating GameTime" << std::endl;
					
						GamesDownload tempGame;
						std::map<int, int> popularCategories;
						std::map<int, int> popularGenres;
						//for all the games
						for(int n = 0; n < m_playerGames.size(); n++)
						{										
							if ( m_games.find(m_playerGames.at(n).appNumber) == m_games.end() ) {
								//if the game isnt in the games database - could be because the game is no longer on steam
								//std::cout << "Game " << m_playerGames.at(n).appID << " not found!" << std::endl;
								
								
							  
							  
							  
							} else {
								//store the game info
								tempGame = m_games.at(m_playerGames.at(n).appNumber);
							  
								//calculate the avaerage price they will pay
								
								if(tempGame.price > 0)
								{
									if(totalTimePlaying > 0)
									{
										priceCount += totalTimePlaying;
										averagePrice += tempGame.price * totalTimePlaying;
									}
									
									if(twoWeekPlaytime > 0)
									{
										priceCount += twoWeekPlaytime;
										averagePrice += tempGame.price * twoWeekPlaytime;
									}
								}
								
								
								
							  
								//calculate the metacritic
								if(tempGame.metaCritic > 0)
								{
									if(totalTimePlaying > 0)
									{
										criticCount += totalTimePlaying;
										averageMetaCritic += tempGame.metaCritic * totalTimePlaying;
									}
									if(twoWeekPlaytime > 0)
									{
										criticCount += twoWeekPlaytime;
										averageMetaCritic += tempGame.metaCritic * twoWeekPlaytime;
									}
								}
								//calculate the final requirements
								if(tempGame.finalRequirements > 0)
								{
									if(totalTimePlaying > 0)
									{
										requirementsCount += totalTimePlaying;
										averagePCRequirements += tempGame.finalRequirements * totalTimePlaying;
									}
									if(twoWeekPlaytime > 0)
									{
										requirementsCount += twoWeekPlaytime;
										averagePCRequirements += tempGame.finalRequirements * twoWeekPlaytime;
									}						  
								}
							  
							  
								if(totalTimePlaying > 0 || twoWeekPlaytime > 0)
								{
									call = statement.GetData("GameToGenre");
									call +=	statement.AddStringCondition("GameID", m_playerGames.at(n).appID);	
									bRet = objMain.getDataStatement(call);
									if (!bRet)
									{					
										std::cout << "ERROR!" << std::endl;
									}
									else
									{
										while ((objMain.row = mysql_fetch_row(objMain.m_result)) != NULL)
										{
											popularGenres[std::stoi(objMain.row[1])] += totalTimePlaying + twoWeekPlaytime;
										}
										objMain.ClearData();
									}
									
									call = statement.GetData("GameToCategory");
									call +=	statement.AddStringCondition("GameID", m_playerGames.at(n).appID);	
									bRet = objMain.getDataStatement(call);
									if (!bRet)
									{					
										std::cout << "ERROR!" << std::endl;
									}
									else
									{
										while ((objMain.row = mysql_fetch_row(objMain.m_result)) != NULL)
										{
											popularCategories[std::stoi(objMain.row[1])] += totalTimePlaying + twoWeekPlaytime;
										}
										objMain.ClearData();
									}
								}
								
													  
							}
						}			
						//work out the average of each value
						
						//std::cout << averagePCRequirements << " " << requirementsCount << std::endl;
						//std::cout << averageMetaCritic << " " << criticCount << std::endl;
						//std::cout << averagePrice << " " << priceCount << std::endl;
						
						averagePCRequirements = averagePCRequirements / requirementsCount;
						averageMetaCritic = averageMetaCritic / criticCount;
						averagePrice = averagePrice / priceCount;
						
						int mostPopularGenre = -1;
						int mostPopularCategory = -1;
						int score = 0;
						//get highest scoring genre
						for (std::map<int, int>::iterator it=popularGenres.begin(); it!=popularGenres.end(); ++it)
						{
							if(it->second > score)
							{
								score = it->second;
								mostPopularGenre = it->first;
							}
						}
						score = 0;
						for (std::map<int, int>::iterator it=popularCategories.begin(); it!=popularCategories.end(); ++it)
						{
							if(it->second > score)
							{
								score = it->second;
								mostPopularCategory = it->first;
							}
						}
						std::cout << "Getting Players Friends" << std::endl;
						//get all their friends					
						url = "http://api.steampowered.com/ISteamUser/GetFriendList/v0001/?key=" + api_key + "&steamid=" + steamid + "&relationship=all&format=json";
						jsonData = api.GetData(url);	
						queryAmount++;
						//for all their friends get the steam id and how long they have been friends
						for(int f = 0; f < jsonData["friendslist"]["friends"].size(); f++)
						{
							Friends temp;
							temp.steamID = jsonData["friendslist"]["friends"][f]["steamid"].asString();
							temp.friendSince = api.UnixToDate(jsonData["friendslist"]["friends"][f]["friend_since"].asInt());
							m_friends.push_back(temp);
						}
						
						//change added to 1
						m_playersToCheck.lock()->SetEncryptColumn("SteamID", steamid);				
						m_playersToCheck.lock()->SetIntColumn("Added", 1);	
						call = m_playersToCheck.lock()->UpdateValues("PlayersToCheck", "Added", INTEGER);
						call += m_playersToCheck.lock()->UpdateValues("PlayersToCheck", "SteamID", ENCRYPT, 1);
						bRet = objMain.execStatement(call);				
						if (!bRet)
						{					
							std::cout << "ERROR!" << std::endl;
						}	
						
						//add the basic information the database
						m_playersMain.lock()->SetEncryptColumn("SteamID", steamid);
						m_playersMain.lock()->SetStringColumn("PrimaryClan", primaryClanID);
						m_playersMain.lock()->SetStringColumn("DateCreated", timeCreated);
						m_playersMain.lock()->SetFloatColumn("AveragePCRequirements", averagePCRequirements);
						m_playersMain.lock()->SetFloatColumn("AverageMetacritic", averageMetaCritic);
						m_playersMain.lock()->SetFloatColumn("AveragePrice", averagePrice);
						m_playersMain.lock()->SetStringColumn("MostPlayedGame", mostPlayedID);
						m_playersMain.lock()->SetStringColumn("MostPlayed2Weeks", mostPlayed2WeeksID);
						m_playersMain.lock()->SetIntColumn("MostPopularGenre", mostPopularGenre);
						m_playersMain.lock()->SetIntColumn("MostPopularCategory", mostPopularCategory);
						m_playersMain.lock()->SetIntColumn("Country", countryID);

						call = m_playersMain.lock()->SetValues();
						
						std::cout << "Adding Player Info" << std::endl;

						bRet = objMain.execStatement(call);				
						if (!bRet)
						{					
							std::cout << "ERROR!" << std::endl;
						}
						
						std::cout << "Adding Games " << m_playerGames.size() << std::endl;
						//add games to the database
						for(int n = 0; n < m_playerGames.size(); n++)
						{
							m_gamesOwned.lock()->SetStringColumn("GameID", m_playerGames.at(n).appID);	
							m_gamesOwned.lock()->SetEncryptColumn("PlayerID", steamid);
							m_gamesOwned.lock()->SetIntColumn("MinutesPlayedTotal", m_playerGames.at(n).playtimeForever);	
							m_gamesOwned.lock()->SetIntColumn("MinutesPlayed2Weeks", m_playerGames.at(n).playtime2Weeks);
							
							if(n == 0)
							{
								call = m_gamesOwned.lock()->SetValues();
							}
							else
							{
								call += m_gamesOwned.lock()->SetValues(1);
							}	
						}						
						//std::cout << call << std::endl;
						bRet = objMain.execStatement(call);				
						if (!bRet)
						{					
							std::cout << "ERROR!" << std::endl;
						}
						
						std::cout << "Adding Friends" << std::endl;
						//add friends to the database
						for(int n = 0; n < m_friends.size(); n++)
						{
							m_playersFriends.lock()->SetEncryptColumn("SteamID1", steamid);
							m_playersFriends.lock()->SetEncryptColumn("SteamID2", m_friends.at(n).steamID);
							m_playersFriends.lock()->SetStringColumn("FriendSince", m_friends.at(n).friendSince);
							
							if(n == 0)
							{
								call = m_playersFriends.lock()->SetValues();
							}
							else
							{
								call += m_playersFriends.lock()->SetValues(1);
							}
						}
						//std::cout << call << std::endl;
						bRet = objMain.execStatement(call);				
						if (!bRet)
						{					
							std::cout << "ERROR!" << std::endl;
						}
					}				
					
				}	
				//change evaluating to 0
				m_playersToCheck.lock()->SetEncryptColumn("SteamID", m_playersToAdd.at(i));				
				m_playersToCheck.lock()->SetIntColumn("Evaluating", 0);	
				call = m_playersToCheck.lock()->UpdateValues("PlayersToCheck", "Evaluating", INTEGER);
				call += m_playersToCheck.lock()->UpdateValues("PlayersToCheck", "SteamID", ENCRYPT, 1);
				
				bRet = objMain.execStatement(call);				
				if (!bRet)
				{					
					std::cout << "ERROR!" << std::endl;
				}	
				
				//increase count
				m_playersToCheck.lock()->SetEncryptColumn("SteamID", m_playersToAdd.at(i));	
				call = m_playersToCheck.lock()->UpdateValues("PlayersToCheck", "Count", INTEGER, 0, true);
				call += m_playersToCheck.lock()->UpdateValues("PlayersToCheck", "SteamID", ENCRYPT, 1);	
				bRet = objMain.execStatement(call);				
				if (!bRet)
				{					
					std::cout << "ERROR!" << std::endl;
				}
			}
			
			//remove the players already checked		
			m_playersToAdd.clear();
			
			m_apiCounter.lock()->SetIntColumn("Value", 1);	
			for(int z = 0; z < queryAmount; z++)
			{		
				if(z == 0)
				{
					call = m_apiCounter.lock()->SetValues();
				}
				else
				{
					call += m_apiCounter.lock()->SetValues(1);
				}
				
			}
			//std::cout << call << std::endl;
			bRet = objMain.execStatement(call);				
			if (!bRet)
			{					
				std::cout << "ERROR!" << std::endl;
			}	
			
			std::cout << "Query Amount: " << queryAmount << std::endl;
		}
		if(run)
		{
			sleep(300);
		}	
		
	}
	
	
	
	
}

std::map<float, MinimumSupport> Application::AssociationRule(std::vector<int> games, float confidenceThreshold)
{
	
	std::map<std::string, std::vector<int>> playerData;
	std::map<int, int> supportValue;
	
	int threshold = playerData.size() * 0.4; //40%
	
	std::vector<int> gameIDsDownloaded;
	
	std::map<int, std::map<int, MinimumSupport>> supportSpecified;
	
	call = statement.GetData("Game", false);	
	call += statement.AddNumberCondition("AvailableOnStore", 1);
	call += statement.AddStringCondition("GameType", "game", 1);
	std::cout << call << std::endl;
	
	//call += statement.AddLimit("10000");
	bRet = objMain.getDataStatement(call);
	if (!bRet)
	{					
		std::cout << "ERROR!" << std::endl;
	}
	else
	{
		while ((objMain.row = mysql_fetch_row(objMain.m_result)) != NULL)
		{
			gameIDsDownloaded.push_back(std::stoi(objMain.row[0]));	
		}
		objMain.ClearData();
	}
	
	std::cout << "downloaded games " << gameIDsDownloaded.size() << std::endl;
	
	for(int i = 0; i < gameIDsDownloaded.size(); i++)
	{
		
		for(int j = 0; j < gameIDsDownloaded.size(); j++)
		{
			
			MinimumSupport temp;
			temp.gameID1 = gameIDsDownloaded.at(i);
			temp.gameID2 = gameIDsDownloaded.at(j);
			temp.confidence = 0;
			temp.count = 0;	
			supportSpecified[gameIDsDownloaded.at(i)][gameIDsDownloaded.at(j)] = temp;
		}
		std::cout << i << std::endl;
	}
	
	
	//for every game owned
	call = statement.GetData("GamesOwned", true, "PlayerID", false, "GameID");	
	call += " INNER JOIN Game ON Game.GameID=GamesOwned.GameID WHERE Game.AvailableOnStore=1";
	call += statement.AddLimit("10000");
	std::cout << call << std::endl;
	
	//call += statement.AddLimit("10000");
	bRet = objMain.getDataStatement(call);
	if (!bRet)
	{					
		std::cout << "ERROR!" << std::endl;
	}
	else
	{
		while ((objMain.row = mysql_fetch_row(objMain.m_result)) != NULL)
		{
			//add the game to a list of games owned by each player
			playerData[objMain.row[1]].push_back(std::stoi(objMain.row[0]));
		}
		objMain.ClearData();
	}
	
	std::cout << "Players Counted For " << playerData.size() << std::endl;
	
	auto start = std::chrono::high_resolution_clock::now();

	std::vector<MinimumSupport> support;
	
	std::map<int,int>::iterator supportIT;
	
	if(games.size() == 0)
	{
		//for every player
		for (std::map<std::string, std::vector<int>>::iterator it = playerData.begin(); it != playerData.end(); it++ )
		{			
			//for all their games
			for(int i = 0; i < it->second.size(); i++)
			{
				//add their game to a map of all the games
				supportIT = supportValue.find(it->second.at(i));
				if (supportIT != supportValue.end())
				{
					supportIT->second++;
				}	
				else
				{
					supportValue[it->second.at(i)] = 1;
				}
				
			}
		}
		
		std::cout << "Analysing Games" << std::endl;
		
		//go through the map of games and how many times they have been owned
		std::vector<int> gamesAboveMinimumSupport;	
		
		float multiplier = 0.6;
		threshold = playerData.size() * multiplier;
		
		//if they dont find at least 5 rules, then go back and reduce the threshold
		while(gamesAboveMinimumSupport.size() < 5)
		{
			for (std::map<int, int>::iterator it = supportValue.begin(); it != supportValue.end(); it++ )
			{
				//if it has been owned by more than 50% of the population
				if(it->second > threshold)
				{
					//add it to the above minimum threshold vector
					gamesAboveMinimumSupport.push_back(it->first);
				}		
			}	
			multiplier -= 0.1;
			threshold = playerData.size() * multiplier;
			if(gamesAboveMinimumSupport.size() < 5)
			{
				gamesAboveMinimumSupport.clear();
			}			
		}
		
		
		std::cout << "Comparing Game Rules" << std::endl;
		
		//for all the games create a rule struct to later compare them against each other
		for(int i = 0; i < gamesAboveMinimumSupport.size(); i++)
		{
			MinimumSupport temp;
			temp.count = 0;
			temp.confidence = 0;
			temp.gameID1 = gamesAboveMinimumSupport.at(i);
			//if game x and game y -- do that for every game
			for(int l = 0; l < gamesAboveMinimumSupport.size(); l++)
			{
				temp.gameID2 = gamesAboveMinimumSupport.at(l);
				if(temp.gameID1 != temp.gameID2)
				{
					support.push_back(temp);
				}
			}
		}
		//for all the rules game 1 ->2, 1->3, 2->1, 2->3 etc
		for(int i = 0; i < support.size(); i++)
		{
			//for every player
			for (std::map<std::string, std::vector<int>>::iterator it = playerData.begin(); it != playerData.end(); it++ )
			{
				if ( std::find(it->second.begin(), it->second.end(), support.at(i).gameID1) != it->second.end() )
				{				
					if ( std::find(it->second.begin(), it->second.end(), support.at(i).gameID2) != it->second.end() )
					{
						//if you can find both games in a players library increase the support count
						support.at(i).count += 1;				
					}
				}
			}
		}
	}
	else
	{
		std::map<int, MinimumSupport>::iterator ruleIT;
		//td::map<int, std::map<int, MinimumSupport>>::iterator gameIT;
		
		//for every player
		for (std::map<std::string, std::vector<int>>::iterator it = playerData.begin(); it != playerData.end(); it++ )
		{		
			//for all their games
			for(int i = 0; i < it->second.size(); i++)
			{
				for(int j = 0; j < it->second.size(); j++)
				{
					supportSpecified[games.at(i)][games.at(j)].count += 1;					
				}
			}
			
			
				
				
				
				
				
				
			/*	------ OLD VERSION ---------------------
			//for all the games being checked			
			for(int g = 0; g < games.size(); g++)
			{
				//if they own any of the games being checked
				if ( std::find(it->second.begin(), it->second.end(), games.at(g)) != it->second.end() )
				{	
					//they means every game the person owns can be counted towards a rule with the game being checked
					for(int i = 0; i < it->second.size(); i++)
					{
						//if the rule for those 2 games exists
						ruleIT = supportSpecified[games.at(g)].find(it->second.at(i));
						if (ruleIT != supportSpecified[games.at(g)].end())
						{
							//increase the count of that rule
							ruleIT->second.count += 1;
						}	
						else
						{
							//otherwise make a new rule
							MinimumSupport temp;
							temp.gameID1 = games.at(g);
							temp.gameID2 = it->second.at(i);
							temp.confidence = 0;
							temp.count = 1;
							supportSpecified[games.at(g)][it->second.at(i)] = temp;
						}
					}					
				}				
			}
			
			
			//for all their games increase the individual count
			for(int i = 0; i < it->second.size(); i++)
			{			
				supportIT = supportValue.find(it->second.at(i));
				if (supportIT != supportValue.end())
				{
					supportIT->second++;
				}	
				else
				{
					supportValue[it->second.at(i)] = 1;
				}
								
			}
			*/
				
		}
		
		std::cout << supportSpecified.size() << std::endl;
		
		for (std::map<int, std::map<int, MinimumSupport>>::iterator it = supportSpecified.begin(); it != supportSpecified.end(); it++ )
		{
			for (std::map<int, MinimumSupport>::iterator itSecond = it->second.begin(); itSecond != it->second.end(); itSecond++ )
			{
				support.push_back(itSecond->second);
			}
			//std::cout << it->second.gameID1 << " " << it->second.gameID2 << " " << it->second.count << std::endl;
			
		}		
	}
	
	std::map<int, std::map<float, MinimumSupport>> ruleScoring;
	float confidenceWeighting = 0.4;
	float liftWeighting = 0.4;
	float convictionWeighting = 0.4;
	float score = 0;
	
	std::cout << "Output Rules for " << std::endl;
	
	//system("PAUSE");
	if(games.size() > 0)
	{
		threshold = 0;
		confidenceThreshold = 0.1;
	}
	else
	{
		threshold = playerData.size() * 0.1;
	}
	
	float ruleSupport, supportX, supportY;
	
	//for every rule
	for(int i = 0; i < support.size(); i++)
	{
		//if the rule is also above the threshold
		if(support.at(i).count > threshold && support.at(i).gameID1 != support.at(i).gameID2)
		{
			
			
			supportX = supportSpecified[support.at(i).gameID1][support.at(i).gameID1].count;
			support.at(i).confidence = (float)((float)support.at(i).count / supportX);
			ruleSupport = support.at(i).count;
			
			supportY = supportSpecified[support.at(i).gameID2][support.at(i).gameID2].count;
			
			
			// OLD METHOD
			/*
			//find the confidence value (the amount of times it comes up) of the first game in the rule
			std::map<int,int>::iterator confidenceIT;
			confidenceIT = supportValue.find(support.at(i).gameID1);						
			if (confidenceIT != supportValue.end())
			{
				//the confidence value is the amount of times the rule comes up divided by the amount of times the first value in the rule appears
				support.at(i).confidence = (float)((float)support.at(i).count / (float)confidenceIT->second);
				ruleSupport = support.at(i).count;
				supportX = confidenceIT->second;
			}
			
			confidenceIT = supportValue.find(support.at(i).gameID2);
			if (confidenceIT != supportValue.end())
			{				
				supportY = confidenceIT->second;
				
			}
			*/
			
			ruleSupport = ruleSupport / playerData.size();
			supportX = supportX / playerData.size();
			supportY = supportY / playerData.size();
			support.at(i).lift = ruleSupport / (supportX * supportY);
			
			support.at(i).conviction = (1 - supportY) / (1 - support.at(i).confidence);
			
			// 
			if(support.at(i).confidence > confidenceThreshold && support.at(i).lift > 1 && support.at(i).conviction > 1)
			{
				//std::cout << supportY << " " << supportX << " " << ruleSupport << " " << (support.at(i).confidence) << std::endl;
				//std::cout << support.at(i).confidence * 100 << "% of users who buy " << support.at(i).gameID1 << " also buy " << support.at(i).gameID2 << " with a lift of: " << support.at(i).lift << " with a conviction of: " << support.at(i).conviction << std::endl;
				
				//calculate score using weighting
				score = 0;
				score += support.at(i).confidence * confidenceWeighting;
				score += support.at(i).lift * liftWeighting;
				score += support.at(i).conviction * convictionWeighting;

				ruleScoring[support.at(i).gameID1][score] = support.at(i);
				
			}
			
		}
	}	
	
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	
	std::map<float, MinimumSupport> results;
	
	for (std::map<int, std::map<float, MinimumSupport>>::iterator it = ruleScoring.begin(); it != ruleScoring.end(); it++ )
	{
		//std::cout << "Scoring for " << it->first << std::endl;
		int scoreCount = 0;
		
		for (std::map<float, MinimumSupport>::reverse_iterator ruleIT = it->second.rbegin(); ruleIT != it->second.rend(); ruleIT++ )
		{		
			scoreCount++;
			//std::cout << ruleIT->second.confidence * 100 << "% of users who buy " << ruleIT->second.gameID1 << " also buy " << ruleIT->second.gameID2 << " with a lift of: " << ruleIT->second.lift << " with a conviction of: " << ruleIT->second.conviction << " with a score of " << ruleIT->first << std::endl;
			results[ruleIT->first] = ruleIT->second;	
			if(scoreCount == 10)
			{
				break;
			}		
		}
		
	}
	
	std::cout << "Elapsed time: " << elapsed.count() << std::endl;
	std::cout << "Time per game: " << elapsed.count() / games.size() << std::endl;
	
	
	return results;
	
	
}

void Application::AddingPlayerCount()
{
	struct GameIDandCountry
	{
		int gameID, country;
	};
	
	std::map<std::string, std::vector<GameIDandCountry>> playerData;
	
	int amountOfGamesOwned = 0;
	
	std::string iteration;
	
	std::cout << "Enter which iteration this program is" << std::endl;
	std::cin >> iteration;
	
	
	
	
	std::string itNumber = iteration;
	std::string fileName = "/tmp/data" + iteration + ".csv";
	
	if( std::remove( fileName.c_str() ) != 0 )
	{
		std::cout << "Error deleting file" << std::endl;
	}
	
	if(iteration == "1")
	{
		iteration = "< 11";
	}	
	if(iteration == "2")
	{
		iteration = "> 10";
	}
	
	std::ofstream myfile;
    
	int offSetOfLastPlayer = 0;
	
	bool runProgram = true;
	
	int programCounter = 0;

	programCounter = std::stoi(TextReader::ReadPassword("programCounter.txt"));
	
	while(runProgram)
	{		
		if(TextReader::ReadPassword("run.txt") == "0")
		{
			runProgram = false;
			break;
		}


		call = "SELECT go.GameID, AES_DECRYPT(go.PlayerID, '" + m_mainTable.lock()->GetKey() + "'), pl.Country FROM main.GamesOwned go INNER JOIN main.Players pl on go.PlayerID = pl.SteamID LEFT JOIN Game gm on gm.GameID = go.GameID WHERE gm.AvailableOnStore = 1 and gm.GameType = 'game'"; // and pl.UpdatingGroup" + iteration;
		call += statement.AddLimit("25000");
		call += " OFFSET " + std::to_string((programCounter * 25000) - offSetOfLastPlayer);
		bRet = objMain.getDataStatement(call);
		if (!bRet)
		{					
			std::cout << "ERROR!" << std::endl;
		}
		else
		{
			while ((objMain.row = mysql_fetch_row(objMain.m_result)) != NULL)
			{
				//add the game to a list of games owned by each player
				GameIDandCountry temp;
				temp.gameID = std::stoi(objMain.row[0]);
				temp.country = std::stoi(objMain.row[2]);
				
				playerData[objMain.row[1]].push_back(temp);
			}
			objMain.ClearData();
		}
		
		programCounter++;
		
		if(!playerData.empty())
		{
			std::map<std::string, std::vector<GameIDandCountry>>::reverse_iterator rit;
			rit = playerData.rbegin();
			offSetOfLastPlayer = rit->second.size();
		}
		else
		{
			runProgram = false;
			break;
		}
		

		std::cout << "Offset of last player (inorder so all rules are accounted for): " << offSetOfLastPlayer << std::endl;
		
		std::cout << "Players Counted For " << playerData.size() << std::endl;	
		
		std::cout << "Program Counter " << programCounter << std::endl;		
		
		std::string secondCall = "";
		
		auto start = std::chrono::high_resolution_clock::now();
		
		myfile.open (fileName);
		
		int counter = 0;
		
		for (std::map<std::string, std::vector<GameIDandCountry>>::iterator it=playerData.begin(); it!=std::prev(playerData.end()); ++it)
		{		
			if(it->second.size() < 300)
			{
				counter++;
				//std::cout << counter << " " << it->first << std::endl;
				
				
				start = std::chrono::high_resolution_clock::now();
				
				call = "INSERT INTO GameCountryCount (GameID, CountryID) VALUES ";
				
				for(int i = 0; i < it->second.size(); i++)
				{				
					call += "(" + std::to_string(it->second.at(i).gameID) + ", " + std::to_string(it->second.at(i).country) + ")";
					
					if(i < it->second.size() - 1)
					{
						call += ",";
					}
					if(i == it->second.size() - 1)
					{
						call += " ON DUPLICATE KEY UPDATE Count = Count + 1";
						bRet = objMain.execStatement(call);
						if (!bRet)
						{					
							std::cout << "ERROR!" << std::endl;
						}			
					}
					
					
					
					
					for(int j = 0; j < it->second.size(); j++)
					{					
						if(j != i)
						{
							//secondCall += "(" + std::to_string(it->second.at(i).gameID) + ", " + std::to_string(it->second.at(j).gameID) + ", " + std::to_string(it->second.at(i).country) + "),";	
							myfile << std::to_string(it->second.at(i).gameID) + ", " + std::to_string(it->second.at(j).gameID) + ", " + std::to_string(it->second.at(i).country) << std::endl;
						}								
					}
				}
			}
			else
			{
				call = "Insert into main.PlayersNotAdded (SteamID) VALUES (AES_ENCRYPT('" + it->first + "','" + m_mainTable.lock()->GetKey() + "'));";
				//std::cout << call << std::endl;
				bRet = objMain.execStatement(call);
				if (!bRet)
				{					
					std::cout << "ERROR!" << std::endl;
				}
			}
					
		}
		
		myfile.close();
		
		bool completed = false;
		
		
		call = "set unique_checks = 0, foreign_key_checks = 0, sql_log_bin=0;";
		bRet = objMain.execStatement(call);
		if (!bRet)
		{					
			std::cout << "ERROR!" << std::endl;
		}
		
		
		while(completed == false)
		{
			
			call = "LOAD DATA INFILE '" + fileName + "' INTO TABLE HoldingTable" + itNumber + " FIELDS TERMINATED BY ',';"; // OPTIONALLY ENCLOSED BY '"' (GameID1, GameID2, CountryID);
			std::cout << call << std::endl;
			bRet = objMain.execStatement(call);
			if (!bRet)
			{					
				std::cout << "ERROR!" << std::endl;
			}
			else
			{
				completed = true;
			}
		}
		
		while(completed == false)
		{		
			call = "set unique_checks = 1, foreign_key_checks = 1, sql_log_bin=1;";
			bRet = objMain.execStatement(call);
			if (!bRet)
			{					
				std::cout << "ERROR!" << std::endl;
			}
			else
			{
				completed = true;
			}
		}
		
		completed = false;
		while(completed == false)
		{
			call = "INSERT INTO GameRules (GameID1, GameID2, CountryID) SELECT GameID1, GameID2, CountryID FROM main.HoldingTable1 ON DUPLICATE KEY UPDATE GameID1 = VALUES(GameID1), GameID2 = VALUES(GameID2), CountryID = VALUES(CountryID), Count = Count + 1;";
			std::cout << call << std::endl;
			bRet = objMain.execStatement(call);
			if (!bRet)
			{					
				std::cout << "ERROR!" << std::endl;
			}
			else
			{
				completed = true;
			}
		}
		
		completed = false;
		while(completed == false)
		{
			call = "TRUNCATE HoldingTable" + itNumber;
			bRet = objMain.execStatement(call);
			if (!bRet)
			{					
				std::cout << "ERROR!" << std::endl;
			}
			else
			{
				completed = true;
			}
		}		
		
		
		
		if( std::remove( fileName.c_str() ) != 0 )
		{
			std::cout << "Error deleting file" << std::endl;
		}
		
		
		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = finish - start;
		
		std::cout << "Time Taken: " << elapsed.count() << std::endl;
		std::cout << "Time Taken per Player: " << elapsed.count() / playerData.size() << std::endl;
		
		//delete file
		
		
		playerData.clear();
	}
	
	
	
	
}

void Application::SendString(std::string& _string)
{
	_string = "INSERT INTO GameRules (GameID1, GameID2, CountryID) VALUES " + _string;
	if(_string[_string.size() - 1] == ',')
	{
		_string.erase (_string.end() - 1, _string.end());
	}
	_string += " ON DUPLICATE KEY UPDATE Count = Count + 1;";
	
	bRet = objMain.execStatement(_string);
	if (!bRet)
	{		
		
		std::cout << _string << std::endl;
		std::cout << _string.size() << std::endl;
		std::cout << "ERROR!" << std::endl;
	}
	_string = "";
}

void Application::AddHighPlayerCount()
{
	bool processed = false;
	std::ofstream myfile;
	
	struct PlayerInfo
	{
		std::string SteamID, CountryID;
	};
	
	std::vector<PlayerInfo> m_players;
	
	std::string fileName = "/tmp/bigData.csv";
	
	while(processed == false)
	{
		std::string update = "0";
		
		call = "Select * from main.StartUpdating LIMIT 1";
		bRet = objMain.getDataStatement(call);
		if (!bRet)
		{					
			std::cout << "ERROR!" << std::endl;
		}
		else
		{
			while ((objMain.row = mysql_fetch_row(objMain.m_result)) != NULL)
			{
				update = objMain.row[0];
			}
			objMain.ClearData();
		}
		
		if(update == "1")
		{
			call = "Select AES_DECRYPT(na.SteamID,'" + m_mainTable.lock()->GetKey() + "'), pl.Country FROM main.PlayersNotAdded na JOIN main.Players pl on na.SteamID = pl.SteamID where Added = 0 LIMIT 10;";
			bRet = objMain.getDataStatement(call);
			if (!bRet)
			{					
				std::cout << "ERROR!" << std::endl;
			}
			else
			{
				while ((objMain.row = mysql_fetch_row(objMain.m_result)) != NULL)
				{
					PlayerInfo temp;
					temp.SteamID = objMain.row[0];
					temp.CountryID = objMain.row[1];
					m_players.push_back(temp);
				}
				objMain.ClearData();
			}
			
			if(m_players.size() == 0)
			{
				processed = true;
				break;
			}
			
			std::cout << m_players.size() << std::endl;
			
			std::vector<std::string> playerGames;
			
			for(int i = 0; i < m_players.size(); i++)
			{
				call = "Select * from main.StartUpdating LIMIT 1";
				bRet = objMain.getDataStatement(call);
				if (!bRet)
				{					
					std::cout << "ERROR!" << std::endl;
				}
				else
				{
					while ((objMain.row = mysql_fetch_row(objMain.m_result)) != NULL)
					{
						update = objMain.row[0];
					}
					objMain.ClearData();
				}
				if(update == "0")
				{
					i = m_players.size();
					break;
				}
				
				
				
				myfile.open (fileName);
				
				call = "Select go.GameID from main.GamesOwned go JOIN main.Game g on go.GameID = g.GameID where AvailableOnStore = 1 and go.PlayerID=AES_ENCRYPT(" + m_players.at(i).SteamID + ",'" + m_mainTable.lock()->GetKey() + "');";
				bRet = objMain.getDataStatement(call);
				if (!bRet)
				{					
					std::cout << "ERROR!" << std::endl;
				}
				else
				{
					while ((objMain.row = mysql_fetch_row(objMain.m_result)) != NULL)
					{
						playerGames.push_back(objMain.row[0]);
					}
					objMain.ClearData();
				}
				
				call = "INSERT INTO GameCountryCount (GameID, CountryID) VALUES ";
				
				for(int g = 0; g < playerGames.size(); g++)
				{			
		
					call += "(" + playerGames.at(g) + ", " + m_players.at(i).CountryID + ")";
					
					if(g < playerGames.size() - 1)
					{
						call += ",";
					}
					if(g == playerGames.size() - 1)
					{
						call += " ON DUPLICATE KEY UPDATE Count = Count + 1";
						bRet = objMain.execStatement(call);
						if (!bRet)
						{					
							std::cout << "ERROR!" << std::endl;
						}			
					}
					
					for(int j = 0; j < playerGames.size(); j++)
					{					
						if(j != i)
						{						
							myfile << playerGames.at(g) + ", " + playerGames.at(j) + ", " + m_players.at(i).CountryID << std::endl;
						}								
					}
				
				}
				
				myfile.close();
				
				call = "set unique_checks = 0, foreign_key_checks = 0, sql_log_bin=0;";
				bRet = objMain.execStatement(call);
				if (!bRet)
				{					
					std::cout << "ERROR!" << std::endl;
				}
				
				bool completed = false;
				while(completed == false)
				{
					
					call = "LOAD DATA INFILE '" + fileName + "' INTO TABLE HoldingTableBigPlayers FIELDS TERMINATED BY ',';"; // OPTIONALLY ENCLOSED BY '"' (GameID1, GameID2, CountryID);
					std::cout << call << std::endl;
					bRet = objMain.execStatement(call);
					if (!bRet)
					{					
						std::cout << "ERROR!" << std::endl;
					}
					else
					{
						completed = true;
					}
				}
				
				while(completed == false)
				{		
					call = "set unique_checks = 1, foreign_key_checks = 1, sql_log_bin=1;";
					bRet = objMain.execStatement(call);
					if (!bRet)
					{					
						std::cout << "ERROR!" << std::endl;
					}
					else
					{
						completed = true;
					}
				}
				
				completed = false;
				while(completed == false)
				{
					call = "INSERT INTO GameRules (GameID1, GameID2, CountryID) SELECT GameID1, GameID2, CountryID FROM main.HoldingTableBigPlayers ON DUPLICATE KEY UPDATE GameID1 = VALUES(GameID1), GameID2 = VALUES(GameID2), CountryID = VALUES(CountryID), Count = Count + 1;";
					std::cout << call << std::endl;
					bRet = objMain.execStatement(call);
					if (!bRet)
					{					
						std::cout << "ERROR!" << std::endl;
					}
					else
					{
						completed = true;
					}
				}
				
				completed = false;
				while(completed == false)
				{
					call = "TRUNCATE HoldingTableBigPlayers";
					bRet = objMain.execStatement(call);
					if (!bRet)
					{					
						std::cout << "ERROR!" << std::endl;
					}
					else
					{
						completed = true;
					}
				}		
				
				
				completed = false;
				while(completed == false)
				{
					call = "UPDATE main.PlayersNotAdded SET Added = 1 WHERE SteamID = AES_ENCRYPT(" + m_players.at(i).SteamID + ",'" + m_mainTable.lock()->GetKey() + "');";
					bRet = objMain.execStatement(call);
					if (!bRet)
					{					
						std::cout << "ERROR!" << std::endl;
					}
					else
					{
						completed = true;
					}
				}
				
				if( std::remove( fileName.c_str() ) != 0 )
				{
					std::cout << "Error deleting file" << std::endl;
				}
				
				
				playerGames.clear();
			}
			m_players.clear();
			
		}
		else
		{
			std::cout << "Sleeping" << std::endl;
			sleep(30);
		}		
	}
	
	
	
}

void Application::RecommendPlayersGames(std::string _id)
{
	std::vector<int> playersGames;	
	
	call = statement.GetData("GamesOwned", false, "GameID", false, "GameID");
	call += " INNER JOIN Game ON Game.GameID=GamesOwned.GameID WHERE Game.AvailableOnStore=1";
	call += statement.AddStringCondition("PlayerID", _id, 1, "=", false, "GamesOwned", true);
	
	
	std::cout << call << std::endl;
	bRet = objMain.getDataStatement(call);
	if (!bRet)
	{					
		std::cout << "ERROR!" << std::endl;
	}
	else
	{
		while ((objMain.row = mysql_fetch_row(objMain.m_result)) != NULL)
		{
			//add the game to a list of games owned by each player
			playersGames.push_back(std::stoi(objMain.row[0]));
		}
		objMain.ClearData();
	}
	
	std::map<float, MinimumSupport> results = AssociationRule(playersGames);
	int scoreCount = 0;
	for (std::map<float, MinimumSupport>::reverse_iterator ruleIT = results.rbegin(); ruleIT != results.rend(); ruleIT++ )
	{		
		scoreCount++;
		std::cout << ruleIT->second.confidence * 100 << "% of users who buy " << ruleIT->second.gameID1 << " also buy " << ruleIT->second.gameID2 << " with a lift of: " << ruleIT->second.lift << " with a conviction of: " << ruleIT->second.conviction << " with a score of " << ruleIT->first << std::endl;
		if(scoreCount == 10)
		{
			break;
		}		
	}
	
}






void Application::SizeTest()
{
	struct PlayerInfo
	{
		unsigned long long int minutesPlayed = 0;
		int gameid = 0;
	};
	
	struct RuleInfo
	{
		unsigned long long int count = 0;
		long double minutesPlayed = 0;
	};	
	
	
	

	
	std::vector<std::string> countries;
	
	
	call = "Select CountryID FROM main.Countries";
	bRet = objMain.getDataStatement(call);
	if (!bRet)
	{					
		std::cout << "ERROR!" << std::endl;
	}
	else
	{
		while ((objMain.row = mysql_fetch_row(objMain.m_result)) != NULL)
		{
			countries.push_back(objMain.row[0]);
		}
		objMain.ClearData();
	}
	std::string iteration;
	for(int c = 0; c < countries.size(); c++)
	{
		
		
		iteration = countries.at(c);
		
		std::cout << iteration << std::endl;
		
		std::string itNumber = iteration;
		std::string fileName = "/tmp/data" + iteration + ".csv";

			
		std::map<std::string, std::vector<PlayerInfo>> playerGames;
		
		call = "Select AES_DECRYPT(pl.SteamID,'" + m_mainTable.lock()->GetKey() + "'), go.GameID, go.MinutesPlayedTotal from main.GamesOwned go join main.Players pl on go.PlayerID = pl.SteamID join main.Game g on go.GameID = g.GameID where pl.Country = " + itNumber + " and g.AvailableOnStore = 1 and g.GameType = 'game' and go.MinutesPlayedTotal > 0;";
		bRet = objMain.getDataStatement(call);
		if (!bRet)
		{					
			std::cout << "ERROR!" << std::endl;
		}
		else
		{
			while ((objMain.row = mysql_fetch_row(objMain.m_result)) != NULL)
			{
				//add the game to a list of games owned by each player
				PlayerInfo temp;
				
				temp.minutesPlayed = std::stoi(objMain.row[2]);
				temp.gameid = std::stoi(objMain.row[1]);
				
				playerGames[objMain.row[0]].push_back(temp);
			}
			objMain.ClearData();
		}
		
		std::cout << playerGames.size() << std::endl;
		
		std::map<int, std::map<int, RuleInfo>> rules;
		std::map<int, RuleInfo> gameInfo;
		
			
		auto start = std::chrono::high_resolution_clock::now();
			
		int counter = 0;
		int abover300Count = 0;
		double rulePlayedMins = 0;
		for(std::map<std::string, std::vector<PlayerInfo>>::iterator it = playerGames.begin(); it != playerGames.end(); ++it)
		{
			
			if(it->second.size() < 500)
			{
				counter++;
				for(int x = 0; x < it->second.size(); x++)
				{
					for(int y = 0; y < it->second.size(); y++)
					{				
						if(x != y)
						{
							rules[it->second.at(x).gameid][it->second.at(y).gameid].count++;		
							rulePlayedMins = 0;
							rulePlayedMins += it->second.at(x).minutesPlayed;
							rulePlayedMins += it->second.at(y).minutesPlayed;
							rules[it->second.at(x).gameid][it->second.at(y).gameid].minutesPlayed += rulePlayedMins;						
						}	
						else
						{
							gameInfo[it->second.at(x).gameid].count++;
							gameInfo[it->second.at(x).gameid].minutesPlayed += it->second.at(x).minutesPlayed;
						}
					}
				}
				//std::cout << counter << std::endl;
			}
			else
			{
				call = "Insert into main.PlayersNotAdded (SteamID) VALUES (AES_ENCRYPT('" + it->first + "','" + m_mainTable.lock()->GetKey() + "'));";
				//std::cout << call << std::endl;
				bRet = objMain.execStatement(call);
				if (!bRet)
				{					
					std::cout << "ERROR!" << std::endl;
				}
			}		
		}
		
		long double ruleSupport = 0;
		long double confidence = 0;
		long double lift = 0;
		long double conviction = 0;
		long double minuteWeight = 0;
		long double score = 0;
		
		
		long double gameID1Count = 0;
		long double gameID2Count = 0;
		
		float confidenceWeighting = 3;
		float liftWeighting = 1;
		float convictionWeighting = 1;
		float minuteWeighting = 1;
		
			
		std::ofstream myfile;
		myfile.open(fileName);
		
		for(std::map<int, std::map<int, RuleInfo>>::iterator it = rules.begin(); it != rules.end(); ++it)
		{
			for(std::map<int, RuleInfo>::iterator itSecond = it->second.begin(); itSecond != it->second.end(); ++itSecond)
			{
				
			
				gameID1Count = gameInfo[it->first].count;
				gameID2Count = gameInfo[itSecond->first].count;
				
				ruleSupport = (double)itSecond->second.count / (double)playerGames.size();
			
				confidence = (itSecond->second.count / gameID1Count);	
				
				
				
				
				lift = ruleSupport / (((double)gameID1Count / (double)playerGames.size()) * ((double)gameID2Count / (double)playerGames.size()));
				
				conviction = (1 - (gameID2Count / playerGames.size())) / (1 - confidence);

				minuteWeight = (1 - ((gameInfo[it->first].minutesPlayed / (double)gameID1Count) / (itSecond->second.minutesPlayed / (double)itSecond->second.count)));
				
				if(isinf(confidence))
				{
					confidence = 10000;
				}
				if(isinf(lift))
				{
					lift = 10000;
				}
				if(isinf(conviction))
				{
					conviction = 10000;
				}


				if(conviction > 1 && lift > 1 && minuteWeight > 0 && confidence > 0.2)
				{
					score = (confidence * confidenceWeighting) + (lift * liftWeighting) + (conviction * convictionWeighting) + (minuteWeight * minuteWeighting) / 4.0f;

					myfile << std::to_string(it->first) + ", " + std::to_string(itSecond->first) + ", " + itNumber + ", " + std::to_string(itSecond->second.count) + ", " + std::to_string(itSecond->second.minutesPlayed) + ", " + std::to_string(score) + ", " + std::to_string(confidence) + ", " + std::to_string(lift) + ", " + std::to_string(conviction) + ", " + std::to_string(minuteWeight) << std::endl;
				}
				
			
			}
		}
		
		
		
		myfile.close();
		
		call = "set unique_checks = 0, foreign_key_checks = 0, sql_log_bin=0;";
		bRet = objMain.execStatement(call);
		if (!bRet)
		{					
			std::cout << "ERROR!" << std::endl;
		}
		
		bool completed = false;
		while(completed == false)
		{
			
			call = "LOAD DATA INFILE '" + fileName + "' INTO TABLE GameRules FIELDS TERMINATED BY ',';"; // OPTIONALLY ENCLOSED BY '"' (GameID1, GameID2, CountryID);
			std::cout << call << std::endl;
			bRet = objMain.execStatement(call);
			if (!bRet)
			{					
				std::cout << "ERROR!" << std::endl;
			}
			else
			{
				completed = true;
			}
		}
		
		if( std::remove( fileName.c_str() ) != 0 )
		{
			std::cout << "Error deleting file" << std::endl;
		}
		
		
		
		myfile.open(fileName);
		
		for(std::map<int, RuleInfo>::iterator it = gameInfo.begin(); it != gameInfo.end(); ++it)
		{
			myfile << std::to_string(it->first) + ", " + itNumber + ", " + std::to_string(it->second.count) + ", " + std::to_string(it->second.minutesPlayed) << std::endl;
		}
		
		myfile.close();
		
		completed = false;
		while(completed == false)
		{
			
			call = "LOAD DATA INFILE '" + fileName + "' INTO TABLE GameCountryCount FIELDS TERMINATED BY ',';"; // OPTIONALLY ENCLOSED BY '"' (GameID1, GameID2, CountryID);
			std::cout << call << std::endl;
			bRet = objMain.execStatement(call);
			if (!bRet)
			{					
				std::cout << "ERROR!" << std::endl;
			}
			else
			{
				completed = true;
			}
		}
		completed = false;
		while(completed == false)
		{		
			call = "set unique_checks = 1, foreign_key_checks = 1, sql_log_bin=1;";
			bRet = objMain.execStatement(call);
			if (!bRet)
			{					
				std::cout << "ERROR!" << std::endl;
			}
			else
			{
				completed = true;
			}
		}
		
		if( std::remove( fileName.c_str() ) != 0 )
		{
			std::cout << "Error deleting file" << std::endl;
		}
		
		//for all of game info
		//add to csv file
		//add to GameCountryCount
		
		
		
		
		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = finish - start;
		
		std::cout << elapsed.count() << std::endl;
		std::cout << "Time per player: " << elapsed.count() / counter << std::endl;
		std::cout << "Above 300 player amount: " << abover300Count << std::endl;
		
	}
}	
	

	

	
	


void Application::CalculatePercentagesForGames()
{	
	std::map<int, double> countryPercent;
	std::vector<int> availableGames;
	
	call = "SELECT Country,COUNT(*) as count FROM Players GROUP BY Country";
	bRet = objMain.getDataStatement(call);
	if (!bRet)
	{					
		std::cout << "ERROR!" << std::endl;
	}
	else
	{
		while ((objMain.row = mysql_fetch_row(objMain.m_result)) != NULL)
		{
			countryPercent[std::stoi(objMain.row[0])] = std::stoi(objMain.row[1]);
		}
		objMain.ClearData();
	}
	
	int totalPlayerAmount = 0;
	
	for (std::map<int, double>::iterator it = countryPercent.begin(); it != countryPercent.end(); it++)
	{
		totalPlayerAmount += it->second;
	}
	
	std::cout << "Total Players: " << totalPlayerAmount << std::endl;
	
	for (std::map<int, double>::iterator it = countryPercent.begin(); it != countryPercent.end(); it++)
	{		
		it->second = it->second / totalPlayerAmount * 100;
	}
	
	call = "SELECT GameID FROM main.Game where AvailableOnStore = 1 and GameType = 'game'";
	bRet = objMain.getDataStatement(call);
	if (!bRet)
	{					
		std::cout << "ERROR!" << std::endl;
	}
	else
	{
		while ((objMain.row = mysql_fetch_row(objMain.m_result)) != NULL)
		{			
			availableGames.push_back(std::stoi(objMain.row[0]));
		}
		objMain.ClearData();
	}
	
	std::cout << "Total Games: " << availableGames.size() << std::endl;

	int totalAmountOfPlayersForGame = 0;
	//availableGames.size()
	for(int i = 0; i < availableGames.size(); i++)
	{
		
		std::cout << availableGames.at(i) << std::endl;
		bool valid = true;
		
		call = "SELECT Sum(Count) FROM main.GameCountryCount WHERE GameID = " + std::to_string(availableGames.at(i)) + ";";
		
		bRet = objMain.getDataStatement(call);
		if (!bRet)
		{					
			std::cout << "ERROR!" << std::endl;
		}
		else
		{
			while ((objMain.row = mysql_fetch_row(objMain.m_result)) != NULL)
			{
				if(objMain.row[0] == NULL)
				{
					valid = false;
				}
				else
				{
					totalAmountOfPlayersForGame = std::stoi(objMain.row[0]);
				}				
			}
			objMain.ClearData();
		}
		
		if(valid)
		{
			std::string updateString = "INSERT INTO GameCountryCount (GameID,CountryID,Percentage,RelativePercentage) VALUES ";
			double percentage, relative;
			
			
			call = "SELECT * FROM main.GameCountryCount WHERE GameID = " + std::to_string(availableGames.at(i)) + ";";
			bRet = objMain.getDataStatement(call);
			if (!bRet)
			{					
				std::cout << "ERROR!" << std::endl;
			}
			else
			{
				while ((objMain.row = mysql_fetch_row(objMain.m_result)) != NULL)
				{
					percentage = ((double)std::stoi(objMain.row[2]) / totalAmountOfPlayersForGame) * 100;
					relative = percentage - countryPercent[std::stoi(objMain.row[1])];
					updateString += "(" + std::to_string(availableGames.at(i)) + "," + objMain.row[1] + "," + std::to_string(percentage) + "," + std::to_string(relative) + "),";
				}
				objMain.ClearData();
			}
			
			if(updateString[updateString.size() - 1] == ',')
			{
				updateString.erase (updateString.end() - 1, updateString.end());
			}
			updateString += " ON DUPLICATE KEY UPDATE GameID=VALUES(GameID),CountryID=VALUES(CountryID),Percentage=VALUES(Percentage),RelativePercentage=VALUES(RelativePercentage);";
			//std::cout << updateString << std::endl;
			bRet = objMain.execStatement(updateString);
			if (!bRet)
			{					
				std::cout << updateString << std::endl;
				std::cout << updateString.size() << std::endl;
				std::cout << "ERROR!" << std::endl;
			}
		}
	}
	
}

void Application::RuleScoringOnDatabase()
{
	//CalculatePercentagesForGames();
	
	struct RuleInfo
	{
		int gameID1, gameID2, count, country, score;
	};
	
	double ruleSupport = 0;
	double confidence = 0;
	double lift = 0;
	double conviction = 0;
	double score = 0;
	
	float confidenceWeighting = 0.4;
	float liftWeighting = 0.4;
	float convictionWeighting = 0.4;
	
	std::map<int, int> countryCount;
	std::vector<RuleInfo> rules;
	
	bool run = true;
	
	int ruleCount = 0;
	
	call = "SELECT Country,COUNT(*) as count FROM Players GROUP BY Country";
	bRet = objMain.getDataStatement(call);
	if (!bRet)
	{					
		std::cout << "ERROR!" << std::endl;
	}
	else
	{
		while ((objMain.row = mysql_fetch_row(objMain.m_result)) != NULL)
		{
			countryCount[std::stoi(objMain.row[0])] = std::stoi(objMain.row[1]);
		}
		objMain.ClearData();
	}
	
	
	while(run)
	{
		call = "select * from main.GameRules where Score is null LIMIT 100;";
		bRet = objMain.getDataStatement(call);
		if (!bRet)
		{					
			std::cout << "ERROR!" << std::endl;
		}
		else
		{
			while ((objMain.row = mysql_fetch_row(objMain.m_result)) != NULL)
			{
				RuleInfo temp;
				temp.gameID1 = std::stoi(objMain.row[0]);
				temp.gameID2 = std::stoi(objMain.row[1]);
				temp.country = std::stoi(objMain.row[2]);
				temp.count = std::stoi(objMain.row[3]);
				
				
				rules.push_back(temp);
			}
			objMain.ClearData();
		}
		
		if(rules.size() == 0)
		{
			run = false;
			break;
		}
		
		for(int i = 0; i < rules.size(); i++)
		{
			ruleCount++;
			
			ruleSupport = (double)rules.at(i).count / (double)countryCount[rules.at(i).country];
			
						
			int gameID1Count = 0;
			int gameID2Count = 0;
			
			call = "Select Count FROm main.GameCountryCount where GameID = " + std::to_string(rules.at(i).gameID1) + " and CountryID = " + std::to_string(rules.at(i).country) + ";";
			bRet = objMain.getDataStatement(call);
			if (!bRet)
			{					
				std::cout << "ERROR!" << std::endl;
			}
			else
			{
				while ((objMain.row = mysql_fetch_row(objMain.m_result)) != NULL)
				{
					gameID1Count = std::stoi(objMain.row[0]);
				}
				objMain.ClearData();
			}
			call = "Select Count FROm main.GameCountryCount where GameID = " + std::to_string(rules.at(i).gameID2) + " and CountryID = " + std::to_string(rules.at(i).country) + ";";
			bRet = objMain.getDataStatement(call);
			if (!bRet)
			{					
				std::cout << "ERROR!" << std::endl;
			}
			else
			{
				while ((objMain.row = mysql_fetch_row(objMain.m_result)) != NULL)
				{
					gameID2Count = std::stoi(objMain.row[0]);
				}
				objMain.ClearData();
			}
			
			confidence = (double)((double)rules.at(i).count / (double)gameID1Count);
			lift = (double)(ruleSupport / (double)(((double)gameID1Count / (double)countryCount[rules.at(i).country]) * ((double)gameID2Count / (double)countryCount[rules.at(i).country])));
			conviction = (double)((1 - ((double)gameID2Count / (double)countryCount[rules.at(i).country])) / (1 - confidence));
			score = (confidence * confidenceWeighting) + (lift * liftWeighting) + (conviction * convictionWeighting);
			
			if(isinf(score))
			{
				score = 10000;
			}
			
			//call = "update GameRules set Score = " + std::to_string(score) + " Confidence = " + std::to_string(confidence) + " Lift = " + std::to_string(lift) + " Conviction = " + std::to_string(conviction) + " where GameID1 = " + std::to_string(rules.at(i).gameID1) + " and GameID2 = " + std::to_string(rules.at(i).gameID2) + " and CountryID = " + std::to_string(rules.at(i).country) + ";";
			call = "update GameRules set Score = " + std::to_string(score) + " where GameID1 = " + std::to_string(rules.at(i).gameID1) + " and GameID2 = " + std::to_string(rules.at(i).gameID2) + " and CountryID = " + std::to_string(rules.at(i).country) + ";";
			
			//std::cout << call << std::endl;
			bool added = false;
			
			while(added == false)
			{
				bRet = objMain.execStatement(call);
				if (!bRet)
				{					
					std::cout << "ERROR!" << std::endl;
				}
				else
				{
					added = true;
				}
			}
			
			
			
			
			//std::cout << "gameid1" << rules.at(i).gameID1 << " gameid2" << rules.at(i).gameID2 << " rulecount" << rules.at(i).count << " gameid1count" << gameID1Count << " gameid2count" << gameID2Count << " confidence" << confidence << " lift" << lift << " conviction" << conviction << " score" << score << std::endl;
		}
		rules.clear();
		
		std::cout << ruleCount << std::endl;
	}
	
	
	
	
	
	
	
	//for every rule
	
}


bool Application::CheckSteamIDs(int _gameID)
{
	std::string stringGame = std::to_string(_gameID);
	url =  "http://store.steampowered.com/api/appdetails?appids=" + stringGame;			
	jsonData = api.GetData(url);
	std::cout << "Steam Game ID: " << _gameID << std::endl;
	
	if(!api.gotData)
	{
		return false;
	}		
	if(jsonData[stringGame]["success"].asBool() == true)
	{			
		m_gameTable.lock()->SetIntColumn("SteamAppID", jsonData[stringGame]["data"]["steam_appid"].asInt());
		m_gameTable.lock()->SetIntColumn("GameID", _gameID);
		
		//if it is not free
		if(!jsonData[stringGame]["data"]["is_free"].asInt())
		{
			//if it has a price
			if(jsonData[stringGame]["data"].isMember("price_overview"))
			{
				if(jsonData[stringGame]["data"]["steam_appid"].asInt() != _gameID)
				{
					m_gameTable.lock()->SetIntColumn("AvailableOnStore", 0);
				}		
				else
				{
					m_gameTable.lock()->SetIntColumn("AvailableOnStore", 1);
				}
			}
			//if it doesnt have a price
			else
			{
				m_gameTable.lock()->SetIntColumn("AvailableOnStore", 0);
			}			
		}
		
		
		
		call = m_gameTable.lock()->UpdateValues("Game", "SteamAppID", INTEGER);
		call += m_gameTable.lock()->UpdateValues("Game", "GameID", INTEGER, 1);
		bRet = objMain.execStatement(call);				
		if (!bRet)
		{					
			std::cout << "ERROR!" << std::endl;
			return false;
		}
		
		call = m_gameTable.lock()->UpdateValues("Game", "AvailableOnStore", INTEGER);
		call += m_gameTable.lock()->UpdateValues("Game", "GameID", INTEGER, 1);
		bRet = objMain.execStatement(call);				
		if (!bRet)
		{					
			std::cout << "ERROR!" << std::endl;
			return false;
		}
		
		return true;
	}

}

void Application::CountryCodes()
{	
	std::map<std::string, std::string> countryCodes = TextReader::GetCountryCodes("all.json");
	
	
	std::map<std::string, std::string>::iterator it;
	for ( it = countryCodes.begin(); it != countryCodes.end(); it++ )
	{
		std::cout << it->first << ':' << it->second << std::endl;
		
		
		m_countriesTable.lock()->SetStringColumn("SteamID", it->first);	
		m_countriesTable.lock()->SetStringColumn("3LetterCode", it->second);	
		call = m_countriesTable.lock()->UpdateValues("Countries", "3LetterCode", STRNG);		
		call += m_countriesTable.lock()->UpdateValues("Countries", "SteamID", STRNG, 1);
		
		
		std::cout << call << std::endl;	

		bRet = objMain.execStatement(call);				
		if (!bRet)
		{					
			std::cout << "ERROR!" << std::endl;
		}
		
	} 
	
}

void Application::GetCurrentPlayers()
{
	
	std::vector<std::string> gameIDs;
	//GETTING ALL THE GAMES AND STORING IN A VECTOR
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
			gameIDs.push_back(objMain.row[0]);
		}	
		objMain.ClearData();
	}
	
	
	
	int queryAmount = 0;	
	bool getCount = false;
	
	while(true)
	{
		sleep(50);
		TimeStruct time = GetTime();		
		if(time.hour == 17 && time.minute == 30)
		{
			getCount = true;
		}
		if(time.hour == 23 && time.minute == 30)
		{
			getCount = true;
		}
		if(time.hour == 5 && time.minute == 30)
		{
			getCount = true;
		}
		if(time.hour == 11 && time.minute == 30)
		{
			getCount = true;
		}
		
		url =  "http://api.ipify.org/?format=json";			
		jsonData = api.GetData(url);
		std::cout << jsonData["ip"] << std::endl;	
		
		if(getCount)
		{
			objMain.OpenConnection();
			std::cout << "Starting Loading" << std::endl;
			for(int i = 0; i < gameIDs.size(); i++)
			{
				//CHECKS HOW MANY QUERYS HAVE BEEN MADE
				call = statement.GetSize("APICallCounter");
				bRet = objMain.getDataStatement(call);
				if (!bRet)
				{					
					std::cout << "ERROR!" << std::endl;
				}
				else
				{
					while ((objMain.row = mysql_fetch_row(objMain.m_result)) != NULL)
					{
						queryAmount = std::stoi(objMain.row[0]);
					}	
					objMain.ClearData();
				}

				//IF 100K have BEEN MADE THEN BREAK
				if(queryAmount >= 100000)
				{
					getCount = false;
					break;
				}

				//OTHERWISE CALL
				url = "http://api.steampowered.com/ISteamUserStats/GetNumberOfCurrentPlayers/v1/?&format=json&appid=" + gameIDs.at(i);
				jsonSpare = api.GetData(url);
				
				//INCREASE THE QUERY AMOUNT
				call = m_apiCounter.lock()->SetValues();
				bRet = objMain.execStatement(call);				
				if (!bRet)
				{					
					std::cout << "ERROR!" << std::endl;
				}	
				
				//IF IT HAS SUCCESSFULLY GOT THE PLAYER COUNT
				if(jsonSpare["response"].isMember("player_count"))
				{
					std::cout << gameIDs.at(i) << std::endl;
					m_gamePlayerCount.lock()->SetIntColumn("GameID", std::stoi(gameIDs.at(i)));	
					m_gamePlayerCount.lock()->SetIntColumn("PlayerAmount", jsonSpare["response"]["player_count"].asInt());				
					call = m_gamePlayerCount.lock()->SetValues();
					bRet = objMain.execStatement(call);				
					if (!bRet)
					{					
						std::cout << "ERROR!" << std::endl;
					}
				}		
			}
			objMain.CloseConnection();
			getCount = false;
		}		
	}
	
	
	
	//FOR EVERY GAME
	
	
	
	
}