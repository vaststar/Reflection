#ifndef PluginBase_h__
#define PluginBase_h__

#include "PluginManager_global.h"
#include <ReflectCore/ReflectBase.h>
#include <ReflectCore/ReflectRegister.h>

class PLUGINMANAGER_LIB_EXPORT PluginBase:public ReflectBase
{
public:
	PluginBase();
	virtual ~PluginBase();
public:
	virtual void InitPlugin() {};

};
#define REGISTER_PLUGIN REGISTER_REFLECT

#endif // PluginBase_h__
