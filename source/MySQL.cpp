#include "MySQL.h"

Proc::Proc()
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

bool Proc::execMain()
{
    try {
        // Format a MySQL object
        conn = mysql_init(NULL);

        // Establish a MySQL connection
        if (!mysql_real_connect(conn, MY_HOSTNAME, MY_USERNAME, MY_PASSWORD, MY_DATABASE, MY_PORT_NO, MY_SOCKET, MY_OPT)) {
            std::cout << mysql_error(conn) << std::endl;
            return false;
        }

        // Execute a sql statement
        if (mysql_query(conn, "SHOW TABLES")) {
            std::cout << mysql_error(conn) << std::endl;
            return false;
        }

        // Get a result set
        res = mysql_use_result(conn);

        // Fetch a result set
        std::cout << "* MySQL - SHOW TABLES in `" << MY_DATABASE << "`" << std::endl;
        while ((row = mysql_fetch_row(res)) != NULL)
            std::cout << row[0] << std::endl;

        // Release memories
        mysql_free_result(res);

        // Close a MySQL connection
        mysql_close(conn);
    } catch (char *e) {
        std::cout << "[EXCEPTION] " << e << std::endl;
        return false;
    }
    return true;
}