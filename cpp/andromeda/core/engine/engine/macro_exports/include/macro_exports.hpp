#pragma once


#if defined(_WIN32)
    #if defined(ENGINECORE_EXPORT)
        #define ENGINECORE_API __declspec(dllexport)
    #else
        #define ENGINECORE_API __declspec(dllimport)
    #endif /* ENGINECORE_API */
    #define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
    // GCC
    #define ENGINECORE_API __attribute__((visibility("default")))
#endif
