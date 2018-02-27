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
		std::string GetData(std::string _tableName, bool decrypt = false, std::string _columnToDecrypt = "");
		std::string GetSize(std::string _tableName);
		std::string AddNumberCondition(std::string _columnName, int value, int count = 0, std::string operation = "=");
		std::string AddStringCondition(std::string _columnName, std::string value, int count = 0, std::string operation = "=", bool decrypt = false, std::string _tableName = "", bool encrypt = false);
		std::string OrderDataDesc(std::string _columnName, int limit = 0);
		std::weak_ptr<Table> CreateTable(std::string tableName);
	private:
		std::map<std::string, std::shared_ptr<Table>> m_tables;

};

#endif