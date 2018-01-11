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
	std::vector<int> m_gameIDs;
	
	call = statement.GetSize("GamesToCheck");				
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
	
	//if(m_gameIDs.size() != 
}

