#include "ApplicationStarter.hpp"
#include "Utils/FileHandler.hpp"

#include <Windows.h>

json ApplicationStarter::s_JSONProperties;

const json& ApplicationStarter::GetStartupJson()
{
    return s_JSONProperties;
}

void ApplicationStarter::BuildStarter()
{
    std::string jsonContent;
    if (FileHandler::ReadTextFile("settings.json", &jsonContent) && PropertiesPassed())
        s_JSONProperties = json::parse(jsonContent);
    else
        BuildStandardStarter();
}

bool ApplicationStarter::PropertiesPassed()
{
    //Here you register all properties you want to verify in the settings.json
    bool properties = true;
    properties = properties && (s_JSONProperties["WindowAPI"].dump() == "null");
    properties = properties && (s_JSONProperties["GraphicsAPI"].dump() == "null");
    return properties;
}

void ApplicationStarter::BuildStandardStarter()
{
    s_JSONProperties["WindowAPI"] = "GLFW";
    s_JSONProperties["GraphicsAPI"] = "GL4";
    FileHandler::WriteTextFile("settings.json", s_JSONProperties.dump(4));
}
