#include "TextReader.h"

std::string TextReader::ReadPassword(std::string _fileLocation)
{
    std::ifstream inf(_fileLocation);
 
    // If we couldn't open the input file stream for reading
    if (!inf)
    {
        // Print an error and exit
        std::cerr << "Uh oh, " + _fileLocation + " could not be opened for reading!" << std::endl;
    }
 
    // While there's still stuff left to read
	std::string strInput = "";
    while (inf)
    {
        // read stuff from the file into a string and print it        
        std::getline(inf, strInput);
    }
	
	return strInput;
}