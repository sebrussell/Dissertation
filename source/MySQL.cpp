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
	
	MY_HOSTNAME = "sql2.freemysqlhosting.net";
    MY_DATABASE = "sql2209342";
    MY_USERNAME = "sql2209342";
    MY_PASSWORD = "uM2%pI4%";
    MY_SOCKET   = NULL;

}

SqlConnector::~SqlConnector()
{
	mysql_library_end();
}

bool SqlConnector::execStatement(std::string statement)
{
	//std::string statement = (std::string("INSERT INTO MainTable (PlayerID, SteamID, Username) VALUES ( '") + std::to_string(_test._number)) + "', '" + _test._id + "', '" + _test._name + "')";
    //std::string statement = "SHOW COLUMNS FROM PlayerTable";
	
	try {
        // Format a MySQL object
        m_connection = mysql_init(NULL);

        // Establish a MySQL connection
        if (!mysql_real_connect(m_connection, MY_HOSTNAME, MY_USERNAME, MY_PASSWORD, MY_DATABASE, MY_PORT_NO, MY_SOCKET, MY_OPT)) {
            std::cout << mysql_error(m_connection) << std::endl;
            return false;
        }

        // Execute a sql statement
        if (mysql_query(m_connection, statement.c_str())) {
            std::cout << mysql_error(m_connection) << std::endl;
            return false;
        }

        // Get a result set
        m_result = mysql_use_result(m_connection);

        // Fetch a result set
        //std::cout << "* MySQL - SHOW TABLES in `" << MY_DATABASE << "`" << std::endl;
        while ((row = mysql_fetch_row(m_result)) != NULL)
		{
            std::cout << row[1] << std::endl;
		}

        // Release memories
        mysql_free_result(m_result);

        // Close a MySQL connection
        mysql_close(m_connection);
    } catch (char *e) {
        std::cout << "[EXCEPTION] " << e << std::endl;
        return false;
    }
    return true;
}

void SqlConnector::PrepareString(std::string& _string)
{

}