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
			m_strings[_columnName] = "";
			break;
		case DBL:
			m_doubles[_columnName] = 0;
			break;
		case DUPLICATE_ADD:
			m_duplicateAdds.push_back("ON DUPLICATE KEY UPDATE " + _columnName + " = " + _columnName + " + 1");
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

void Table::SetGetValueColumn(std::string _columnName, GetValue _value)
{
	m_getValuesDouble[_columnName] = _value;
}

std::string Table::FormatString(std::string _string)
{
	_string.erase(std::remove(_string.begin(), _string.end(), 39), _string.end());
	_string.erase(std::remove(_string.begin(), _string.end(), 40), _string.end());
	_string.erase(std::remove(_string.begin(), _string.end(), 41), _string.end());
	_string.erase(std::remove(_string.begin(), _string.end(), 62), _string.end());
	_string.erase(std::remove(_string.begin(), _string.end(), 60), _string.end());
	_string.erase(std::remove(_string.begin(), _string.end(), 34), _string.end());
	return _string;
}

std::string Table::SetValues()
{
	
	//return (std::string("INSERT INTO" MainTable (PlayerID, SteamID, Username) VALUES ( '") + std::to_string(_test._number)) + "', '" + _test._id + "', '" + _test._name + "')";
	
	std::string returnString = (std::string("INSERT INTO ") + m_tableName + " (");
	
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
	
	if(m_doubles.size() > 0)
	{
		returnString += ", ";
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
	
	if(m_getValuesDouble.size() > 0)
	{
		returnString += ", ";
	}
	
	for (std::map<std::string, GetValue>::iterator it=m_getValuesDouble.begin(); it!=m_getValuesDouble.end(); ++it)
	{
		if(std::next(it) == m_getValuesDouble.end())
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
	
	/*
	if(m_doubles.size() > 0)
	{
		returnString += ", ";
	}
	
	
	for (std::map<std::string, double>::iterator it=m_doubles.begin(); it!=m_doubles.end(); ++it)
	{
		if(std::next(it) == m_doubles.end())
		{
			returnString += it->second + "'";
		}
		else
		{
			returnString += it->second + ", ";
		}
	}
	*/
	
	if(m_getValuesDouble.size() > 0)
	{
		returnString += ", ";
	}
	
	
	for (std::map<std::string, GetValue>::iterator it=m_getValuesDouble.begin(); it!=m_getValuesDouble.end(); ++it)
	{
		returnString += "(SELECT " + it->second.m_columnNameToGet + " FROM " + it->second.m_tableName + " WHERE " + it->second.m_columnNameToCompare + "='" + it->second.m_value;
		
		
		if(std::next(it) == m_getValuesDouble.end())
		{
			returnString += "') ";
		}
		else
		{
			returnString += "'), ";
		}
	}
	
	returnString += ") ";
	
	for(int i = 0; i < m_duplicateAdds.size(); i++)
	{
		returnString += m_duplicateAdds.at(i);
	}
	
	//returnString += m_strings.end()->first + ") VALUES";
	
	//returnString += m_strings.at(m_strings.size() - 1) + ";
	
	return  returnString;
}
