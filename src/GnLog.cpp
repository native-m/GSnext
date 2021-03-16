#include <gsnext/GnLog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/msvc_sink.h>

void GnLog::Initialize()
{
    if (g_logger != nullptr) {
        return;
    }

    std::vector<spdlog::sink_ptr> l;

    l.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/GSnext.log", true));
    l.push_back(std::make_shared<spdlog::sinks::msvc_sink_mt>());

    g_logger = std::make_shared<spdlog::logger>("GSnext", l.begin(), l.end());
    g_logger->set_level(spdlog::level::trace);
    g_logger->flush_on(spdlog::level::trace);
    spdlog::register_logger(g_logger);
}

std::shared_ptr<spdlog::logger> GnLog::g_logger = nullptr;
