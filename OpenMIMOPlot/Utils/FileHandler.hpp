#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP

#include <string>

class FileHandler
{
public:
	static bool ReadTextFile(std::string_view filepath, std::string* content);
	static bool WriteTextFile(std::string_view filepath, std::string content);
private:

};


#endif // FILE_HANDLER_HPP
