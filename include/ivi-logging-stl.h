/**
 * This file define how to output standard types to the logging system
 */
#pragma once

#include "ivi-logging-common.h"
#include <exception>
#include <map>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

namespace logging {

template <typename ElementType, class LogDataType = logging::LogData,
    typename = typename std::enable_if<std::is_base_of<logging::LogData, LogDataType>::value>::type>
LogDataType& operator<<(LogDataType& log, const std::vector<ElementType>& v)
{
    log << "[ ";
    size_t n = v.size();
    for (auto& element : v) {
        log << element;
        if (--n)
            log << ", ";
    }
    log << "]";
    return log;
}

template <typename ElementType, size_t lenght, class LogDataType = logging::LogData,
    typename = typename std::enable_if<std::is_base_of<logging::LogData, LogDataType>::value>::type>
LogDataType& operator<<(LogDataType& log, const std::array<ElementType, lenght>& v)
{
    log << "[ ";
    size_t n = lenght;
    for (auto& element : v) {
        log << element;
        if (--n)
            log << ", ";
    }
    log << "]";
    return log;
}

template <typename K, typename V, typename... H, template <typename...> class T, class LogDataType,
    typename = typename std::enable_if<std::is_base_of<logging::LogData, LogDataType>::value>::type,
    typename
    = typename std::enable_if<std::is_same<std::pair<const K, V>, typename T<K, V, H...>::value_type>::value>::type>
LogDataType& operator<<(LogDataType& log, const T<K, V, H...>& v)
{
    log << " [ ";
    size_t n = v.size();
    for (auto& element : v) {
        log << "{ ";
        log << element.first;
        log << " = ";
        log << element.second;
        log << " }";
        if (--n)
            log << ", ";
    }
    log << " ] ";
    return log;
}

template <typename LogDataType,
    typename = typename std::enable_if<std::is_base_of<logging::LogData, LogDataType>::value>::type>
LogDataType& operator<<(LogDataType& log, const std::exception& ex)
{
    log << ex.what() << ", excp=" << typeid(ex).name();
    return log;
}
}

namespace std {

template <typename LogDataType,
    typename = typename std::enable_if<std::is_base_of<logging::LogInfo, LogDataType>::value>::type>
LogDataType& endl(LogDataType& log)
{
    log << "\n";
    return log;
}

template <typename LogDataType,
    typename = typename std::enable_if<std::is_base_of<logging::LogInfo, LogDataType>::value>::type>
LogDataType& ends(LogDataType& log)
{
    // TODO : implement
    return log;
}

template <typename LogDataType,
    typename = typename std::enable_if<std::is_base_of<logging::LogInfo, LogDataType>::value>::type>
LogDataType& flush(LogDataType& log)
{
    // TODO : implement
    return log;
}
}
