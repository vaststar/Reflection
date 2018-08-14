#ifndef ReflectCore_global_h__
#define ReflectCore_global_h__

#ifdef REFLECTCORE_LIB
#define REFLECTCORE_LIB_EXPORT _declspec(dllexport)
#else
#define REFLECTCORE_LIB_EXPORT _declspec(dllimport)
#endif
#endif // ReflectCore_global_h__
