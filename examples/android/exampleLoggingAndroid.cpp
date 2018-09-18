#include "ivi-logging-android.h"
#include "ivi-logging-types.h"
#include <iostream>
#include <unistd.h>

/// Use that type to use Android logging API
typedef logging::LogContextT<
    logging::TypeSet<logging::AndroidLogContext>, logging::TypeSet<logging::AndroidLogContext::LogDataType>>
    LogContext;

// Set app ID
LOG_DEFINE_APP_IDS("MyAp", "This is a small application showing how to use ivi-logging");

// Instantiate a log context and define it as default for this module
LOG_DECLARE_DEFAULT_CONTEXT(mainContext, "MAIN", "This is a description of that logging context");

int main(int, const char **)
{
    std::cout << "Logging android: \n";
    // this log should also be visible in log cat
    log_info() << "Logging on Android environment!!";
    return 0;
}
