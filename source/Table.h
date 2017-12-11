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
	DBL
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
		std::string SetValues();
		std::string FormatString(std::string _string);
	private:
		std::string m_tableName;
		std::map<std::string, std::string> m_strings;
		std::map<std::string, double> m_doubles;

};

#endif