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
	
	MY_HOSTNAME = "declared-hinges.000webhostapp.com";
    MY_DATABASE = "id4004992_test";
    MY_USERNAME = "id4004992_s38russell";
    MY_PASSWORD = "Test123";
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

        // Get a result set
        //m_result = mysql_use_result(m_connection);

        // Fetch a result set
        //std::cout << "* MySQL - SHOW TABLES in `" << MY_DATABASE << "`" << std::endl;
        //while ((row = mysql_fetch_row(m_result)) != NULL)
		//{
        //    std::cout << row[1] << std::endl;
		//}

        // Release memories
        //mysql_free_result(m_result);

        // Close a MySQL connection
        
		return true;
}

void SqlConnector::PrepareString(std::string& _string)
{

}