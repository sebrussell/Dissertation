#include <mysql/mysql.h>  
#include <iostream>
#include <string>
#include <algorithm>

class Statement;

class SqlConnector
{
    const char* MY_HOSTNAME;
    const char* MY_DATABASE;
    const char* MY_USERNAME;
    char* MY_PASSWORD;
    const char* MY_SOCKET;
    enum {
        MY_PORT_NO = 3306,
        MY_OPT     = 0
    };
    MYSQL     *m_connection;



public:
    SqlConnector();           // Constructor
	~SqlConnector();
    bool execStatement(std::string statement);  // Main Process
    bool getDataStatement(std::string statement);  // Main Process
	void ClearData();
	void PrepareString(std::string& _string);

	void GetPassword();
	MYSQL_RES *m_result;
    MYSQL_ROW row;
};