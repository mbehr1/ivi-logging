/**
 * This file define how to output standard types to the logging system
 */
#pragma once

#include "ivi-logging-common.h"
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <exception>
#include <type_traits>

namespace logging {

template<typename ElementType, class LogDataType = logging::LogData, typename =
		 typename std::enable_if<std::is_base_of<logging::LogData, LogDataType>::value>::type>
LogDataType& operator<<(LogDataType& log, const std::vector<ElementType>& v) {
	log << "[ ";
	for (auto& element : v) {
		log << element;
		log << ", ";
	}
	log << "]";
	return log;
}

template<typename K,typename V,typename... H, template <typename...> class T, class LogDataType = logging::LogData, typename =
		 typename std::enable_if< std::is_same< std::pair<const K,V> , typename T < K, V, H ... >::value_type >::value>::type>
LogDataType& operator<<(LogDataType& log, const T<K,V,H...>& v) {
	log << " [ ";
	for (auto& element : v) {
		log << " { ";
		log << element.first;
		log << " = ";
		log << element.second;
		log << " }, ";
	}
	log << " ] ";
	return log;
}

template<typename LogDataType, typename =
         typename std::enable_if<std::is_base_of<logging::LogData, LogDataType>::value>::type>
LogDataType& operator<<(LogDataType& log, const std::exception& ex) {
    log << ex.what();
    return log;
}

}

namespace std {

template<typename LogDataType, typename =
		 typename std::enable_if<std::is_base_of<logging::LogInfo, LogDataType>::value>::type>
LogDataType&
  endl(LogDataType& log) {
	log << "\n";
	return log;
  }

template<typename LogDataType, typename =
		 typename std::enable_if<std::is_base_of<logging::LogInfo, LogDataType>::value>::type>
LogDataType&
  ends(LogDataType& log) {
	// TODO : implement
	return log;
  }

template<typename LogDataType, typename =
		 typename std::enable_if<std::is_base_of<logging::LogInfo, LogDataType>::value>::type>
LogDataType&
  flush(LogDataType& log) {
	// TODO : implement
	return log;
  }

}

