#include "MySQL.h"
#include "Statement.h"
#include "TextReader.h"

SqlConnector::SqlConnector()
{	
	MY_HOSTNAME = "54.37.19.153";
	//MY_HOSTNAME = "localhost";
    MY_DATABASE = "main";
    MY_USERNAME = "seb";
    MY_SOCKET   = NULL;
	
	
	std::string mySqlPassword = TextReader::ReadPassword("..//passwords/MySQL.txt");
	MY_PASSWORD = mySqlPassword.c_str();
	//std::cout << "MySQL Password Loaded" << std::endl;
	
	//SETUP MYSQL
	OpenConnection();
	
	

}

SqlConnector::~SqlConnector()
{	
	CloseConnection();
	mysql_library_end();
}

void SqlConnector::OpenConnection()
{
	m_connection = mysql_init(NULL);
	std::string mySqlPassword = TextReader::ReadPassword("..//passwords/MySQL.txt");
	MY_PASSWORD = mySqlPassword.c_str();
	if (!mysql_real_connect(m_connection, MY_HOSTNAME, MY_USERNAME, MY_PASSWORD, MY_DATABASE, MY_PORT_NO, MY_SOCKET, MY_OPT)) {
		std::cout << mysql_error(m_connection) << std::endl;
    }
}

void SqlConnector::CloseConnection()
{
	mysql_close(m_connection);
}

void SqlConnector::ResetConnection()
{
	std::cout << "Resetting MYSQL Connection" << std::endl;
	CloseConnection();
	OpenConnection();
}

bool SqlConnector::execStatement(std::string statement, bool outputError)
{

        if (mysql_query(m_connection, statement.c_str())) {
			if(outputError)
			{
				std::cout << mysql_error(m_connection) << std::endl;
				ResetConnection();
			}            
            return false;
        }        
		return true;
}

bool SqlConnector::getDataStatement(std::string statement)
{
		
		
        if (mysql_query(m_connection, statement.c_str())) {
            std::cout << mysql_error(m_connection) << std::endl;
			ResetConnection();
            return false;
        }

        // Get a result set
        m_result = mysql_use_result(m_connection);

        // Fetch a result set
        //std::cout << "* MySQL - SHOW TABLES in `" << MY_DATABASE << "`" << std::endl;
        //while ((row = mysql_fetch_row(m_result)) != NULL)
		//{
        //    std::cout << row[1] << std::endl;
		//}

        // Release memories
        

        // Close a MySQL connection
        
		return true;
}

void SqlConnector::ClearData()
{
	mysql_free_result(m_result);
}

void SqlConnector::PrepareString(std::string& _string)
{

}