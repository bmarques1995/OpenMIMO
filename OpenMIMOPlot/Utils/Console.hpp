#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <spdlog/spdlog.h>
#include <cstdarg>
#include <memory>

namespace OpenMIMO
{
    class ConsoleWrapper
    {
    public:
        static void Init();
        static void End();

        static std::shared_ptr<spdlog::logger> GetLogger();
    private:
        static std::shared_ptr<spdlog::logger> s_Logger;
    };
}

#define Console_Log(...) ::OpenMIMO::ConsoleWrapper::GetLogger()->info(__VA_ARGS__);::OpenMIMO::ConsoleWrapper::GetLogger()->flush();
#define Console_Warn(...) ::OpenMIMO::ConsoleWrapper::GetLogger()->warn(__VA_ARGS__);::OpenMIMO::ConsoleWrapper::GetLogger()->flush();
#define Console_Error(...) ::OpenMIMO::ConsoleWrapper::GetLogger()->error(__VA_ARGS__);::OpenMIMO::ConsoleWrapper::GetLogger()->flush();


#endif
