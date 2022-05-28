#ifndef APPLICATION_STARTER_HPP
#define APPLICATION_STARTER_HPP

#include <nlohmann/json.hpp>

using nlohmann::json;

class ApplicationStarter
{
public:
	static const json& GetStartupJson();
	static void BuildStarter();
private:
	static json s_JSONProperties;

	static bool PropertiesPassed();
	static void BuildStandardStarter();
};


#endif
