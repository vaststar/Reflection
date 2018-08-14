#ifndef PluginManager_global_h__
#define PluginManager_global_h__

#ifdef PLUGINMANAGER_LIB
#define PLUGINMANAGER_LIB_EXPORT _declspec(dllexport)
#else
#define PLUGINMANAGER_LIB_EXPORT _declspec(dllimport)
#endif
#endif // PluginCore_global_h__
