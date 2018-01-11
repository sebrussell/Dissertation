#include "MySQL.h"
#include "Statement.h"

SqlConnector::SqlConnector()
{
	/*
    // Initialize constants
    MY_HOSTNAME = "db712559206.db.1and1.com";
    MY_DATABASE = "db712559206";
    MY_USERNAME = "dbo712559206";
    MY_PASSWORD = "";
    MY_SOCKET   = NULL;
	*/
	
	MY_HOSTNAME = "213.138.113.137";
	//MY_HOSTNAME = "localhost";
    MY_DATABASE = "main";
    MY_USERNAME = "seb";
    MY_PASSWORD = "seb";
    MY_SOCKET   = NULL;
	
	//SETUP MYSQL
	
	m_connection = mysql_init(NULL);

	if (!mysql_real_connect(m_connection, MY_HOSTNAME, MY_USERNAME, MY_PASSWORD, MY_DATABASE, MY_PORT_NO, MY_SOCKET, MY_OPT)) {
		std::cout << mysql_error(m_connection) << std::endl;
    }
}

SqlConnector::~SqlConnector()
{
	mysql_close(m_connection);
	mysql_library_end();
}

bool SqlConnector::execStatement(std::string statement)
{

        if (mysql_query(m_connection, statement.c_str())) {
            std::cout << mysql_error(m_connection) << std::endl;
            return false;
        }        
		return true;
}

bool SqlConnector::getDataStatement(std::string statement)
{
		
		
        if (mysql_query(m_connection, statement.c_str())) {
            std::cout << mysql_error(m_connection) << std::endl;
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