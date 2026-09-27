
#ifndef SPACE_API_H
#define SPACE_API_H

#ifdef SPACE_STATIC_DEFINE
#  define SPACE_API
#  define SPACE_NO_EXPORT
#else
#  ifndef SPACE_API
#    ifdef space_EXPORTS
        /* We are building this library */
#      define SPACE_API __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define SPACE_API __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef SPACE_NO_EXPORT
#    define SPACE_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef SPACE_DEPRECATED
#  define SPACE_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef SPACE_DEPRECATED_EXPORT
#  define SPACE_DEPRECATED_EXPORT SPACE_API SPACE_DEPRECATED
#endif

#ifndef SPACE_DEPRECATED_NO_EXPORT
#  define SPACE_DEPRECATED_NO_EXPORT SPACE_NO_EXPORT SPACE_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef SPACE_NO_DEPRECATED
#    define SPACE_NO_DEPRECATED
#  endif
#endif

#endif /* SPACE_API_H */
