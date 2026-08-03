#pragma once


#if defined(_WIN32)
    #if defined(RENDERING_EXPORT)
        #define RENDERING_API __declspec(dllexport)
    #else
        #define RENDERING_API __declspec(dllimport)
    #endif /* RENDERING_API */
    #define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
    // GCC
    #define RENDERING_API __attribute__((visibility("default")))
#endif
