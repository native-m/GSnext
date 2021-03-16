#pragma once

#include <spdlog/spdlog.h>

class GnLog
{
public:
    static void Initialize();

    template<class... Args>
    static void Critical(Args&&... args)
    {
        g_logger->critical(std::forward<Args>(args)...);
    }

    template<class... Args>
    static void Error(Args&&... args)
    {
        g_logger->error(std::forward<Args>(args)...);
    }

    template<class... Args>
    static void Warn(Args&&... args)
    {
        g_logger->warn(std::forward<Args>(args)...);
    }

    template<class... Args>
    static void Info(Args&&... args)
    {
        g_logger->info(std::forward<Args>(args)...);
    }

private:
    static std::shared_ptr<spdlog::logger> g_logger;
};
