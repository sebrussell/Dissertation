#ifndef TEXTREADER_H
#define TEXTREADER_H

#include <string>
#include <fstream>
#include <iostream>

class TextReader
{
	public:
		TextReader() {};
		~TextReader() {};
		static std::string ReadPassword(std::string _fileLocation);
};

#endif