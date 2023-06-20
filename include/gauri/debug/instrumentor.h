#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>
#include <string>

#include <thread>

namespace gauri
{
struct ProfileResult
{
    std::string Name;
    long long Start, End;
    uint32_t ThreadID;
};

struct InstrumentationSession
{
    std::string Name;
};

class Instrumentor
{
  public:
    Instrumentor() : m_CurrentSession(nullptr), m_ProfileCount(0)
    {
    }

    void BeginSession(const std::string &name, const std::string &filepath = "results.json")
    {
        m_OutputStream.open(filepath);
        WriteHeader();
        m_CurrentSession = new InstrumentationSession{name};
    }

    void EndSession()
    {
        WriteFooter();
        m_OutputStream.close();
        delete m_CurrentSession;
        m_CurrentSession = nullptr;
        m_ProfileCount = 0;
    }

    void WriteProfile(const ProfileResult &result)
    {
        if (m_ProfileCount++ > 0)
        {
            m_OutputStream << ", ";
        }

        std::string name = result.Name;
        std::replace(name.begin(), name.end(), '"', '\'');

        m_OutputStream << "{";
        m_OutputStream << "\"cat\":\"function\",";
        m_OutputStream << "\"dur\":" << (result.End - result.Start) << ", ";
        m_OutputStream << "\"name\":\"" << name << "\",";
        m_OutputStream << "\"ph\":\"X\",";
        m_OutputStream << "\"pid\":0,";
        m_OutputStream << "\"tid\":" << result.ThreadID << ",";
        m_OutputStream << "\"ts\":" << result.Start;
        m_OutputStream << "}";

        m_OutputStream.flush();
    }

    void WriteHeader()
    {
        m_OutputStream << "{\"otherData\": {}, \"traceEvents\":[";
        m_OutputStream.flush();
    }

    void WriteFooter()
    {
        m_OutputStream << "]}";
        m_OutputStream.flush();
    }

    static Instrumentor &Get()
    {
        static Instrumentor instance;
        return instance;
    }

  private:
    InstrumentationSession *m_CurrentSession;
    std::ofstream m_OutputStream;
    int m_ProfileCount;
};

class ImstrumentationTimer
{
  public:
    ImstrumentationTimer(const char *name) : m_Name(name), m_Stopped(false)
    {
        m_StartTimepoint = std::chrono::high_resolution_clock::now();
    }
    ~ImstrumentationTimer()
    {
        if (!m_Stopped)
        {
            Stop();
        }
    }

    void Stop()
    {
        using std::chrono::high_resolution_clock;
        using std::chrono::microseconds;
        using std::chrono::time_point_cast;

        auto endTimepoint = high_resolution_clock::now();

        long long start = time_point_cast<microseconds>(m_StartTimepoint).time_since_epoch().count();
        long long end = time_point_cast<microseconds>(endTimepoint).time_since_epoch().count();

        float duration = (end - start) * 0.001f;

        uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
        Instrumentor::Get().WriteProfile({m_Name, start, end, threadID});

        m_Stopped = true;
    }

  private:
    const char *m_Name;
    std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
    bool m_Stopped;
};
} // namespace gauri

#define GR_PROFILE 1
#if GR_PROFILE
#define GR_PROFILE_BEGIN_SESSION(name, filepath) ::gauri::Instrumentor::Get().BeginSession(name, filepath)
#define GR_PROFILE_END_SESSION() ::gauri::Instrumentor::Get().EndSession()
#define GR_PROFILE_SCOPE(name) ::gauri::ImstrumentationTimer timer##__LINE__(name);
#define GR_PROFILE_FUNCTION() GR_PROFILE_SCOPE(__FUNCSIG__)
#else
#define GR_PROFILE_BEGIN_SESSION(name, filepath)
#define GR_PROFILE_END_SESSION()
#define GR_PROFILE_SCOPE(name)
#define GR_PROFILE_FUNCTION()
#endif // GR_PROFILE
