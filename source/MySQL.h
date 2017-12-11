#include <mysql/mysql.h>  
#include <iostream>
#include <string>
#include <algorithm>

struct Test
{
	Test(int number, std::string id, std::string name, std::string location)
	{
		_number = number;
		_id = id;
		_name = name;
		_location = location;
	}
	int _number;
	std::string _id;
	std::string _name;
	std::string _location;
};

class Statement;

class SqlConnector
{
    const char* MY_HOSTNAME;
    const char* MY_DATABASE;
    const char* MY_USERNAME;
    const char* MY_PASSWORD;
    const char* MY_SOCKET;
    enum {
        MY_PORT_NO = 3306,
        MY_OPT     = 0
    };
    MYSQL     *m_connection;
    MYSQL_RES *m_result;
    MYSQL_ROW row;


public:
    SqlConnector();           // Constructor
	~SqlConnector();
    bool execStatement(std::string statement);  // Main Process
	void PrepareString(std::string& _string);

};