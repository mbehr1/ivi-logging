// logging using android log features
#pragma once

#include "ivi-logging-common.h"
#include "ivi-logging-console.h"
#include "ivi-logging.h"
#include <android/log.h>
#include <iostream>
#include <string>
#include <syslog.h>
#include <unistd.h>

namespace logging {
class AndroidLogData;

class AndroidLogContext : public StreamLogContextAbstract
{
public:
    typedef AndroidLogData LogDataType;

    FILE* getFile(StreamLogData&) override { return nullptr; }
};

class AndroidLogData : public StreamLogData
{
    const std::string _id = "IVIL";

    static int getAndroidLogLevel(LogLevel logLevel)
    {
        int v = ANDROID_LOG_INFO;
        switch (logLevel) {
        case LogLevel::Debug:
            v = ANDROID_LOG_DEBUG;
            break;
        case LogLevel::Info:
            v = ANDROID_LOG_INFO;
            break;
        case LogLevel::Warning:
            v = ANDROID_LOG_WARN;
            break;
        case LogLevel::Error:
            v = ANDROID_LOG_ERROR;
            break;
        case LogLevel::Fatal:
            v = ANDROID_LOG_FATAL;
            break;
        case LogLevel::Verbose:
            v = ANDROID_LOG_VERBOSE;
            break;
        default:
            v = ANDROID_LOG_INFO;
            break;
        }
        return v;
    }

public:
    ~AndroidLogData()
    {
        if (data.length() > 0) {
            __android_log_print(getAndroidLogLevel(m_data->getLogLevel()), _id.c_str(), "%s", data.c_str());
        }
    }
    void addData(std::string data) { this->data += data; }

private:
    std::string data = "";
};

template <typename T>
inline std::enable_if_t<std::is_constructible<std::string, T>::value, AndroidLogData&> operator<<(
    AndroidLogData& data, T v)
{
    if (data.isEnabled())
        data.addData(std::string(v));
    return data;
}

template <typename T>
inline std::enable_if_t<std::is_fundamental<T>::value && !std::is_constructible<std::string, T>::value, AndroidLogData&>
operator<<(AndroidLogData& data, T v)
{
    if (data.isEnabled())
        data.addData(std::to_string(v));
    return data;
}

inline AndroidLogData& operator<<(AndroidLogData& data, bool v)
{
    if (data.isEnabled())
        data.addData(v ? "true" : "false");
    return data;
}
} // namespace logging
