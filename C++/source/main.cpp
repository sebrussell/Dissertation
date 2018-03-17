// main.cpp

#include "Application.h"



int main()
{
	Application app;
	
	std::string input;
	
	std::cout << "Choose which application to run" << std::endl;
	std::cout << "Manage API = 1" << std::endl;
	std::cout << "Update Player Tables = 2" << std::endl;
	//std::cout << "Evaluate PC requirements = 3" << std::endl;
	//std::cout << "Set PC requirements = 4" << std::endl;
	std::cout << "Association Rule = 5" << std::endl;
	std::cout << "Update Player Count = 8" << std::endl;
	std::cin >> input;
	
	app.GetIDTables();
	
	if(input == "1")
	{
		app.APIResetter();
	}
	else if(input == "2")
	{
		app.UpdatePlayers();
	}
	else if(input == "3")
	{
		//app.EvaluatePCRequirements();
	}
	else if(input == "4")
	{
		//app.SetPCRequirements();
	}
	else if(input == "5")
	{
		std::vector<int> games;
		games.push_back(440);
		games.push_back(70);
		games.push_back(212070);
		games.push_back(100);
		games.push_back(1900);
		games.push_back(8260);
		games.push_back(9060);
		games.push_back(334410);
		
		games.push_back(334710);
		games.push_back(332570);
		games.push_back(331920);
		games.push_back(296930);
		games.push_back(223100);
		games.push_back(63600);
		games.push_back(37270);
		
		games.push_back(34640);
		games.push_back(339290);
		games.push_back(339110);
		games.push_back(303470);
		games.push_back(303710);
		games.push_back(303830);
		games.push_back(71120);

		
		app.AssociationRule(games);
	}
	else if(input == "6")
	{
		//app.UpdateGame(5793);
	}
	else if(input == "7")
	{
		app.CountryCodes();
	}
	else if(input == "8")
	{
		app.GetCurrentPlayers();
	}
	
	
	
	
	//app.UpdateGameCheckerTable();
	
	
	
	//call times

	
	
	
	
	//default values


	

	
	/*
	
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
		


		
		
		
		url =  "http://api.steampowered.com/ISteamApps/GetAppList/v0001/";			
		jsonSpare = api.GetData(url);
		
		
		//std::cout << jsonSpare["applist"]["apps"]["app"].size() << std::endl;
		int size = jsonSpare["applist"]["apps"]["app"].size();
		
		
		//52061
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
				
			
				
	
			/*
			if(c == 0)
			{
				start = clock();
			}
	
			c++;
	
			gameID = jsonSpare["applist"]["apps"]["app"][h]["appid"].asInt();			
			gameIDString = std::to_string(gameID);

			
			url =  "http://store.steampowered.com/api/appdetails?appids=" + gameIDString;
			
			jsonData = api.GetData(url);
			
			
		
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
				
				
				//HOW TO GET DATA FROM A TABLE - COULD BE IMRPVOED ATM JUST RETURNS EVERYTHING
				call = statement.GetData("Genre");				
				bRet = objMain.getDataStatement(call);
				if (!bRet)
				{					
						std::cout << "ERROR!" << std::endl;
				}
				
				while ((objMain.row = mysql_fetch_row(objMain.m_result)) != NULL)
				{
				    std::cout << objMain.row[0] << " " << objMain.row[1] << std::endl;
				}
				objMain.ClearData();

			
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
			*/
			
			
		//}
		
		
		
		
		
		

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
		//i++;
	//}
	
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
