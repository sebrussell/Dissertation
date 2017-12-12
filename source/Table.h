#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

enum Type
{
	STRNG,
	DBL,
	GET,
	DUPLICATE_ADD
};

struct GetValue
{
	std::string m_columnNameToGet, m_tableName, m_columnNameToCompare, m_abreviation, m_value;
};


class Table
{
	public:
		Table();
		~Table();
		void CreateTable(std::string _name) { m_tableName = _name; }
		
		void AddColumn(std::string _columnName, Type _type);
		
		
		void SetStringColumn(std::string _columnName, std::string _value);
		void SetDoubleColumn(std::string _columnName, double _value);
		void SetGetValueColumn(std::string _columnName, GetValue _value);
		
		std::string SetValues();
		std::string FormatString(std::string _string);
	private:
		std::string m_tableName;
		std::map<std::string, std::string> m_strings;
		std::map<std::string, double> m_doubles;
		std::map<std::string, GetValue> m_getValuesDouble;
		std::vector<std::string> m_duplicateAdds;

};

#endif