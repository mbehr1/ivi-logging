// Provides abstraction to thread related functionality

#pragma once

#include <cstdio>
#include <cstdlib>
#include <pthread.h>
#include <string>

namespace logging {

thread_local std::string thread_name;

// get thread name
inline int thread_getname(char* __buf, size_t __buflen)
{
// if we are not on android environment assume that we can use pthread without limitations,
// otherwise we need to take into account that some pthread functionality is dependent on the
// android platform
#ifndef __BIONIC__
    return pthread_getname_np(pthread_self(), __buf, __buflen);
#else
#if __ANDROID_API__ >= 26
    return pthread_getname_np(pthread_self(), __buf, __buflen);
#else
    snprintf(__buf, __buflen, "%s", thread_name.c_str());
    return 0;
#endif
#endif
}

// set thread name
inline int thread_setname(const char* name)
{
#ifndef __BIONIC__
    return pthread_setname_np(pthread_self(), name);
#else
// assume that pthread_setname_np is only available if pthread_getname_np also is
#if __ANDROID_API__ >= 26
    return pthread_setname_np(pthread_self(), name);
#else
    thread_name = name;
    return 0;
#endif
#endif
}

} // namespace logging
