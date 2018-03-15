#include "Table.h"
#include "TextReader.h"

Table::Table()
{
	m_secretKey = TextReader::ReadPassword("..//passwords/EncryptKey.txt");
	//std::cout << "Encrypt Key Loaded" << std::endl;
}

Table::~Table()
{
	
}

std::string Table::AlterTableAddColumn(std::string _columnName, Type _type)
{
	AddColumn(_columnName, _type);
	
	std::string returnString = "ALTER TABLE " + m_tableName + " ADD " + _columnName + " ";
	
	switch(_type)
	{
		case STRNG:
			returnString += "VARCHAR(50)";
			break;
		case DBL:
			returnString += "DOUBLE";
			break;
		case INTEGER:
			returnString += "INT";
			break;	
		case FLT:
			returnString += "FLOAT";
			break;
		case ENCRYPT:
			returnString += "VARBINARY(50)";
			break;			
		default:
			break;
	}
	
	return returnString;
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
		case INTEGER:
			m_ints[_columnName] = 0;
			break;	
		case FLT:
			m_floats[_columnName] = 0;
			break;
		case DUPLICATE_ADD:
			m_duplicateAdds.push_back("ON DUPLICATE KEY UPDATE " + _columnName + " = " + _columnName + " + 1");
			break;	
		case ENCRYPT:
			m_encrypts[_columnName] = "";
			break;			
		default:
			break;
	}
}

void Table::SetStringColumn(std::string _columnName, std::string _value)
{
	m_strings[_columnName] = FormatString(_value);
}

void Table::SetEncryptColumn(std::string _columnName, std::string _value)
{
	m_encrypts[_columnName] = "(AES_ENCRYPT('" + _value + "', '" + m_secretKey + "'))";
}

void Table::SetDoubleColumn(std::string _columnName, double _value)
{
	m_doubles[_columnName] = _value;
}

void Table::SetIntColumn(std::string _columnName, int _value)
{
	m_ints[_columnName] = _value;
}

void Table::SetFloatColumn(std::string _columnName, float _value)
{
	m_floats[_columnName] = _value;
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

std::string Table::UpdateValues(std::string _columnToSet, std::string _columnToChange, Type _type, int _number, bool _duplicate)
{
	std::string returnString;
	if(_number == 0)
	{
		returnString = "UPDATE " + _columnToSet + " SET ";
	}	
	else if(_number == 1)
	{
		returnString = " WHERE ";
	}
	else
	{
		returnString = " OR ";
	}
	
	returnString += _columnToChange + " = ";
	
	if(_duplicate == false)
	{
		switch (_type)
		{
				case STRNG:
					returnString += "'" + m_strings.find(_columnToChange)->second + "'";
					break;
				case INTEGER:
					returnString += std::to_string(m_ints.find(_columnToChange)->second);
					break;	
				case FLT:
					returnString += std::to_string(m_floats.find(_columnToChange)->second);
					break;	
				case ENCRYPT:
					returnString += m_encrypts.find(_columnToChange)->second;
					break;
		}
	}
	else
	{
		returnString += _columnToChange + " + 1";
	}
	
	
	
	return returnString;
}

std::string Table::SetValues(int iterator)
{
	
	//return (std::string("INSERT INTO" MainTable (PlayerID, SteamID, Username) VALUES ( '") + std::to_string(_test._number)) + "', '" + _test._id + "', '" + _test._name + "')";
	
	std::string returnString;
	
	if(iterator == 0)
	{
		returnString = (std::string("INSERT INTO ") + m_tableName + " (");
		
		
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
		
		
		if(m_encrypts.size() > 0)
		{
			if(m_strings.size() > 0)
			{
				returnString += ", ";
			}		
		}
		
		for (std::map<std::string, std::string>::iterator it=m_encrypts.begin(); it!=m_encrypts.end(); ++it)
		{
			if(std::next(it) == m_encrypts.end())
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
			if(m_encrypts.size() > 0 || m_strings.size() > 0)
			{
				returnString += ", ";
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
		
		if(m_ints.size() > 0)
		{
			if(m_doubles.size() > 0 || m_strings.size() > 0 || m_encrypts.size() > 0)
			{
				returnString += ", ";
			}		
		}
		
		for (std::map<std::string, int>::iterator it=m_ints.begin(); it!=m_ints.end(); ++it)
		{
			if(std::next(it) == m_ints.end())
			{
				returnString += it->first;
			}
			else
			{
				returnString += it->first + ", ";			
			}
		}	
		
		
		
		if(m_floats.size() > 0 )
		{
			if((m_doubles.size() > 0 || m_strings.size() > 0 || m_ints.size() > 0 || m_encrypts.size() > 0))
			{
				returnString += ", ";
			}	
		}	
		for (std::map<std::string, float>::iterator it=m_floats.begin(); it!=m_floats.end(); ++it)
		{
			if(std::next(it) == m_floats.end())
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
		
		
	}
	
	if(iterator == 0)
	{
		returnString += ") VALUES (";
	}
	else
	{
		returnString += ",(";
	}
		
	
	if(m_strings.size() > 0)
	{
		returnString += "'";
	}	
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
	
	if(m_encrypts.size() > 0)
	{
		if(m_strings.size() > 0)
		{
			returnString += ", ";	
		}		
	}
	
	for (std::map<std::string, std::string>::iterator it=m_encrypts.begin(); it!=m_encrypts.end(); ++it)
	{
		if(std::next(it) == m_encrypts.end())
		{
			returnString += it->second + "";
		}
		else
		{
			returnString += it->second + ", ";
		}
	}
	
	
	
	if(m_ints.size() > 0)
	{
		if(m_encrypts.size() > 0 || m_strings.size() > 0)
		{
			returnString += ", '";	
		}		
		else
		{
			returnString += "'";
		}
	}
	for (std::map<std::string, int>::iterator it=m_ints.begin(); it!=m_ints.end(); ++it)
	{
		if(std::next(it) == m_ints.end())
		{
			returnString += std::to_string(it->second) + "'";
		}
		else
		{
			returnString += std::to_string(it->second) + "', '";
		}
	}	
	
	
	if(m_floats.size() > 0)
	{
		if(m_doubles.size() > 0 || m_strings.size() > 0 || m_ints.size() > 0)
		{
			returnString += ", '";
		}		
	}
	for (std::map<std::string, float>::iterator it=m_floats.begin(); it!=m_floats.end(); ++it)
	{
		if(std::next(it) == m_floats.end())
		{
			returnString += std::to_string(it->second) + "'";
		}
		else
		{
			returnString += std::to_string(it->second) + "', '";
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
