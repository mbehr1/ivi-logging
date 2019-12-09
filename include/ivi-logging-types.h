/**
 * This file define how to output standard types to the logging system
 */
#pragma once

#include "ivi-logging-common.h"
#include "ivi-logging-stl.h"
#include <exception>
#include <map>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

namespace logging {

static constexpr const char* NULL_POINTER_STRING = "nullptr";

template <typename LogDataType,
    typename = typename std::enable_if<std::is_base_of<logging::LogData, LogDataType>::value>::type>
LogDataType& operator<<(LogDataType& log, const StringBuilder& b)
{
    log << b.str();
    return log;
}
}
