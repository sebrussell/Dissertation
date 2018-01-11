#ifndef STATEMENT_H
#define STATEMENT_H

#include <string>
#include <memory>
#include <vector>
#include <map>

class Table;

class Statement
{
	public:
		Statement() {};
		~Statement() {};
		std::string Call(std::string _tableName);
		std::string GetData(std::string _tableName);
		std::string GetSize(std::string _tableName);
		std::string AddNumberCondition(std::string _columnName, int value);
		std::weak_ptr<Table> CreateTable(std::string tableName);
	private:
		std::map<std::string, std::shared_ptr<Table>> m_tables;

};

#endif