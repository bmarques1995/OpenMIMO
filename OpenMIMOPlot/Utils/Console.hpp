#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <spdlog/spdlog.h>
#include <spdlog/common.h>
#include <spdlog/details/log_msg.h>
#include <spdlog/details/backtracer.h>
#include <cstdarg>
#include <memory>
#include <string>

template<typename... Args>
using format_string_t = std::string_view;

namespace OpenMIMO
{
    class ConsoleWrapper
    {
    public:
        static void Init();
        static void End();

        template<typename... Args>
        static void Debug(format_string_t<Args...> fmt, Args &&... args)
        {
            s_Logger->trace(fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        static void Log(format_string_t<Args...> fmt, Args &&... args)
        {
            s_Logger->info(fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        static void Warn(format_string_t<Args...> fmt, Args &&... args)
        {
            s_Logger->warn(fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        static void Error(format_string_t<Args...> fmt, Args &&... args)
        {
            s_Logger->error(fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        static void Critical(format_string_t<Args...> fmt, Args &&... args)
        {
            s_Logger->critical(fmt, std::forward<Args>(args)...);
        }

    private:
        static std::shared_ptr<spdlog::logger> s_Logger;
    };
}

#endif
