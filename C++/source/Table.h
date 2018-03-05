#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

class TextReader;

enum Type
{
	STRNG,
	DBL,
	GET,
	DUPLICATE_ADD,
	FLT,
	INTEGER,
	ENCRYPT
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
		
		std::string AlterTableAddColumn(std::string _columnName, Type _type);
		
		std::string GetKey() { return m_secretKey; }
		
		void SetStringColumn(std::string _columnName, std::string _value);
		void SetEncryptColumn(std::string _columnName, std::string _value);
		void SetDoubleColumn(std::string _columnName, double _value);
		void SetIntColumn(std::string _columnName, int _value);
		void SetFloatColumn(std::string _columnName, float _value);
		void SetGetValueColumn(std::string _columnName, GetValue _value);
		
		std::string SetValues();
		std::string UpdateValues(std::string _columnToSet, std::string _columnToChange, Type _type, int _number = 0, bool _duplicate = false);
		std::string FormatString(std::string _string);
	private:
		std::string m_tableName;
		std::map<std::string, std::string> m_strings;
		std::map<std::string, std::string> m_encrypts;
		std::map<std::string, double> m_doubles;
		std::map<std::string, int> m_ints;
		std::map<std::string, float> m_floats;
		std::map<std::string, GetValue> m_getValuesDouble;
		std::vector<std::string> m_duplicateAdds;
		
		std::string m_secretKey;

};

#endif