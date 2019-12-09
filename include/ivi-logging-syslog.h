#pragma once

#include "ivi-logging-common.h"
#include "ivi-logging-console.h"
#include <iostream>
#include <string>
#include <syslog.h>
#include <unistd.h>

namespace logging {
class SyslogLogData;

class SyslogLogContext : public StreamLogContextAbstract
{
public:
    typedef SyslogLogData LogDataType;

    FILE* getFile(StreamLogData&) override { return nullptr; }
};

class SyslogLogData : public StreamLogData
{
    static int getSyslogLevel(LogLevel logLevel)
    {
        int v = LOG_INFO;
        switch (logLevel) {
        case LogLevel::Debug:
            v = LOG_DEBUG;
            break;
        case LogLevel::Info:
            v = LOG_INFO;
            break;
        case LogLevel::Warning:
            v = LOG_WARNING;
            break;
        case LogLevel::Error:
            v = LOG_ERR;
            break;
        case LogLevel::Fatal:
            v = LOG_EMERG;
            break;
        case LogLevel::Verbose:
            v = LOG_INFO;
            break;
        default:
            v = LOG_INFO;
            break;
        }
        return v;
    }

public:
    ~SyslogLogData()
    {
        openlog(NULL, LOG_PID, LOG_USER);
        syslog(LOG_MAKEPRI(LOG_USER, getSyslogLevel(m_data->getLogLevel())), "%s", data.c_str());
        closelog();
    }
    void addData(std::string data) { this->data += data; }

private:
    std::string data = "";
};

template <typename T>
inline std::enable_if_t<std::is_constructible<std::string, T>::value, SyslogLogData&> operator<<(
    SyslogLogData& data, T v)
{
    if (data.isEnabled())
        data.addData(std::string(v));
    return data;
}

template <typename T>
inline std::enable_if_t<std::is_fundamental<T>::value && !std::is_constructible<std::string, T>::value, SyslogLogData&>
operator<<(SyslogLogData& data, T v)
{
    if (data.isEnabled())
        data.addData(std::to_string(v));
    return data;
}

inline SyslogLogData& operator<<(SyslogLogData& data, bool v)
{
    if (data.isEnabled())
        data.addData(v ? "true" : "false");
    return data;
}

} // namespace logging
