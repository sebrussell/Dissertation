#include "Statement.h"
#include "Table.h"

std::string Statement::Call(std::string _tableName)
{
	//return "INSERT INTO MainTable (PlayerID, SteamID, Username) VALUES ( '") + std::to_string(_test._number)) + "', '" + _test._id + "', '" + _test._name + "')";
	if(m_tables[_tableName])
	{
		return m_tables[_tableName]->SetValues();
	}
}

std::string Statement::GetData(std::string _tableName, bool decrypt, std::string _columnToDecrypt)
{
	if(m_tables[_tableName])
	{
		if(decrypt)
		{
			return "SELECT AES_DECRYPT(" + _columnToDecrypt + ",'" + m_tables[_tableName]->GetKey() + "') FROM " + _tableName;
		}
		else
		{
			return "SELECT * FROM " + _tableName;
		}		
	}
	else
	{
		return "";
	}	
}

std::string Statement::AddLimit(std::string _limitAmount)
{
	return " LIMIT " + _limitAmount;
}

std::string Statement::GetSize(std::string _tableName)
{
	if(m_tables[_tableName])
	{
		return "SELECT COUNT(*) FROM " + _tableName;
	}
	else
	{
		return "";
	}
}

std::string Statement::AddNumberCondition(std::string _columnName, int value, int count, std::string operation)
{
	if(count == 0)
	{
		return " WHERE " + _columnName + operation + std::to_string(value);
	}
	else
	{
		return " AND " + _columnName + operation + std::to_string(value);
	}
	
}

std::string Statement::AddStringCondition(std::string _columnName, std::string value, int count, std::string operation, bool decrypt, std::string _tableName, bool encrypt)
{
	if(decrypt)
	{
		value = "AES_DECRYPT(" + value + ",'" + m_tables[_tableName]->GetKey() + "')";
	}
	if(encrypt)
	{
		value = "AES_ENCRYPT(" + value + ",'" + m_tables[_tableName]->GetKey() + "')";
	}
	else
	{
		value = "'" + value + "'";
	}
	if(count == 0)
	{
		
		return " WHERE " + _columnName + operation + value;
	}
	else
	{
		return " AND " + _columnName + operation + value;
	}
	
}

std::string Statement::OrderDataDesc(std::string _columnName, int limit)
{
	if(limit > 0)
	{
		return " ORDER BY " + _columnName + " DESC LIMIT " + std::to_string(limit);
	}
	else
	{
		return " ORDER BY " + _columnName + " DESC ";
	}
	
}

std::weak_ptr<Table> Statement::CreateTable(std::string tableName)
{
	std::shared_ptr<Table> m_table(new Table);
	std::weak_ptr<Table> m_returnTable;
	
	
	
	if(!m_tables[tableName])
	{		
		m_table->CreateTable(tableName);	
		m_tables[tableName] = m_table;				
	}	
	
	m_returnTable = m_tables[tableName];
	return m_returnTable;
}