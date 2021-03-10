
#ifndef CMAES_EXPORT_H
#define CMAES_EXPORT_H

#ifdef CMAES_STATIC_DEFINE
#  define CMAES_EXPORT
#  define CMAES_NO_EXPORT
#else
#  ifndef CMAES_EXPORT
#    ifdef cmaes_EXPORTS
        /* We are building this library */
#      define CMAES_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define CMAES_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef CMAES_NO_EXPORT
#    define CMAES_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef CMAES_DEPRECATED
#  define CMAES_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef CMAES_DEPRECATED_EXPORT
#  define CMAES_DEPRECATED_EXPORT CMAES_EXPORT CMAES_DEPRECATED
#endif

#ifndef CMAES_DEPRECATED_NO_EXPORT
#  define CMAES_DEPRECATED_NO_EXPORT CMAES_NO_EXPORT CMAES_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef CMAES_NO_DEPRECATED
#    define CMAES_NO_DEPRECATED
#  endif
#endif

#endif /* CMAES_EXPORT_H */
