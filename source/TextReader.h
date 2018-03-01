#ifndef TEXTREADER_H
#define TEXTREADER_H

#include <json/json.h>
#include <string>
#include <fstream>
#include <iostream>
#include <map>

class TextReader
{
	public:
		TextReader() {};
		~TextReader() {};
		static std::string ReadPassword(std::string _fileLocation);
		static std::map<std::string, std::string> GetCountryCodes(std::string _fileLocation);
};

#endif