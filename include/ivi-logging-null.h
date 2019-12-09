#pragma once

#include "ivi-logging-common.h"

namespace logging {

class NullLogContext;

/**
 * This class provides the same interface as other LogData classes, but actually does nothing with the objects which are streamed to it.
 * It can be useful to disable some logging.
 */
class NullLogData : public LogData
{

public:
    void init(NullLogContext&, LogInfo&) {}

    bool isEnabled() const { return false; }

    template <typename... Args> void writeFormatted(const char*, Args...) {}
};

class NullLogContext
{

public:
    typedef NullLogData LogDataType;

    void setParentContext(LogContextCommon&) {}

    bool isEnabled(LogLevel) { return false; }

    void registerContext() {}
};

template <typename T> inline NullLogData& operator<<(NullLogData& data, const T&) { return data; }

inline NullLogData& operator<<(NullLogData& data, const bool) { return data; }

inline NullLogData& operator<<(NullLogData& data, const char*) { return data; }

template <size_t N> inline NullLogData& operator<<(NullLogData& data, const char (&v)[N])
{
    (void)v;
    return data;
}

inline NullLogData& operator<<(NullLogData& data, const std::string&) { return data; }

inline NullLogData& operator<<(NullLogData& data, const float) { return data; }

// TODO : strangely, it seems like none of the types defined in "stdint.h" is equivalent to "long int" on a 32 bits platform
#if __WORDSIZE == 32
inline NullLogData& operator<<(NullLogData& data, const long int) { return data; }
inline NullLogData& operator<<(NullLogData& data, const unsigned long int) { return data; }
#endif

inline NullLogData& operator<<(NullLogData& data, const double) { return data; }

inline NullLogData& operator<<(NullLogData& data, const uint64_t) { return data; }

inline NullLogData& operator<<(NullLogData& data, const int64_t) { return data; }

inline NullLogData& operator<<(NullLogData& data, const uint32_t) { return data; }

inline NullLogData& operator<<(NullLogData& data, const int32_t) { return data; }

inline NullLogData& operator<<(NullLogData& data, const uint16_t) { return data; }

inline NullLogData& operator<<(NullLogData& data, const int16_t) { return data; }

inline NullLogData& operator<<(NullLogData& data, const uint8_t) { return data; }

inline NullLogData& operator<<(NullLogData& data, const int8_t) { return data; }
}
