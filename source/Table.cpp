#include "Table.h"

Table::Table()
{
	
}

Table::~Table()
{
	
}

void Table::AddColumn(std::string _columnName, Type _type)
{
	switch(_type)
	{
		case STRNG:
			m_strings[_columnName] = "zz";
			break;
		case DBL:
			m_doubles[_columnName] = 0;
			break;
		default:
			break;
	}
}

void Table::SetStringColumn(std::string _columnName, std::string _value)
{
	m_strings[_columnName] = FormatString(_value);
}

void Table::SetDoubleColumn(std::string _columnName, double _value)
{
	m_doubles[_columnName] = _value;
}

std::string Table::FormatString(std::string _string)
{
	_string.erase(std::remove(_string.begin(), _string.end(), 39), _string.end());
	return _string;
}

std::string Table::SetValues()
{
	
	//return (std::string("INSERT INTO" MainTable (PlayerID, SteamID, Username) VALUES ( '") + std::to_string(_test._number)) + "', '" + _test._id + "', '" + _test._name + "')";
	
	std::string returnString = (std::string("INSERT INTO ") + m_tableName + "(");
	
	for (std::map<std::string, std::string>::iterator it=m_strings.begin(); it!=m_strings.end(); ++it)
	{
		if(std::next(it) == m_strings.end())
		{
			returnString += it->first;
		}
		else
		{
			returnString += it->first + ", ";
		}
	}
	
	for (std::map<std::string, double>::iterator it=m_doubles.begin(); it!=m_doubles.end(); ++it)
	{
		if(std::next(it) == m_doubles.end())
		{
			returnString += it->first;
		}
		else
		{
			returnString += it->first + ", ";
		}
	}
	
	
	
	returnString += ") VALUES ('";
	
	
	
	for (std::map<std::string, std::string>::iterator it=m_strings.begin(); it!=m_strings.end(); ++it)
	{
		if(std::next(it) == m_strings.end())
		{
			returnString += it->second + "'";
		}
		else
		{
			returnString += it->second + "', '";
		}
	}
	
	returnString += ")";
	
	//returnString += m_strings.end()->first + ") VALUES";
	
	//returnString += m_strings.at(m_strings.size() - 1) + ";
	
	return  returnString;
}
