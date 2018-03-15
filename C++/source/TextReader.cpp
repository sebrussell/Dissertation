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

std::map<std::string, std::string> TextReader::GetCountryCodes(std::string _fileLocation)
{
	std::map<std::string, std::string> temp;
	
	bool alive = true;
    while (alive){
    Json::Value root;   // will contains the root value after parsing.
    Json::Reader reader;
    std::ifstream test(_fileLocation, std::ifstream::binary);
    bool parsingSuccessful = reader.parse( test, root, false );
    if ( !parsingSuccessful )
    {
        // report to the user the failure and their locations in the document.
        std::cout  << reader.getFormatedErrorMessages()
               << "\n";
    }

	
	for(int i = 0; i < root.size(); i++)
	{
		temp[root[i]["alpha-2"].asString()] = root[i]["alpha-3"].asString();		
	}
	
	
    alive = false;
    }
	
	return temp;
}