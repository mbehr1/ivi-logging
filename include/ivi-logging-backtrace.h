// backtrace functionality used by ivi-logging whenever execinfo.h is not available at the system
// (for instance, when in an Android environment)

#pragma once

namespace logging
{
// TODO: At the moment we are only stubbing the implementation of the functions. If backtracing is
// required some functionality has to be provided. For instance, for Android "unwind.h" could be
// considered

// Store the return addresses of the current program state
int backtrace(void ** /*array*/, int /*size*/)
{
    return 0;
}

// Get the names of the functions
char **backtrace_symbols(void *const * /*array*/, int /*size*/)
{
    return 0;
}

// Write backtrace symbols to a file
void backtrace_symbols_fd(void *const * /*array*/, int /*size*/, int /*fd*/)
{
    /* None */
}
} // namespace logging