#pragma once

#include <format>
#include <memory>

#include "spdlog/fmt/ostr.h"
#include "spdlog/spdlog.h"

namespace gauri
{
class Log
{
  public:
    static void Init();

    inline static std::shared_ptr<spdlog::logger> &GetCoreLogger()
    {
        return s_CoreLogger;
    }

    inline static std::shared_ptr<spdlog::logger> &GetClientLogger()
    {
        return s_ClientLogger;
    }

  private:
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
    static std::shared_ptr<spdlog::logger> s_ClientLogger;
};

#define GR_CORE_ERROR(...) ::gauri::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GR_CORE_WARN(...) ::gauri::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GR_CORE_INFO(...) ::gauri::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GR_CORE_TRACE(...) ::gauri::Log::GetCoreLogger()->trace(__VA_ARGS__)

#define GR_ERROR(...) ::gauri::Log::GetClientLogger()->error(__VA_ARGS__)
#define GR_WARN(...) ::gauri::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GR_INFO(...) ::gauri::Log::GetClientLogger()->info(__VA_ARGS__)
#define GR_TRACE(...) ::gauri::Log::GetClientLogger()->trace(__VA_ARGS__)

} // namespace gauri
