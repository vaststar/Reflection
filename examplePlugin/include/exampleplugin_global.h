#ifndef exampleplugin_global_h__
#define exampleplugin_global_h__

#ifdef EXAMPLEPLUGIN_LIB
#define EXAMPLEPLUGIN_EXPORT _declspec(dllexport)
#else
#define EXAMPLEPLUGIN_EXPORT _declspec(dllimport)
#endif
#endif // exampleplugin_global_h__
