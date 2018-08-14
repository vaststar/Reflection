#ifndef PluginBase_h__
#define PluginBase_h__

#include "PluginCore_global.h"
#include <ReflectCore/ReflectBase.h>
#include <ReflectCore/ReflectRegister.h>

class PLUGINCORE_LIB_EXPORT PluginBase:public ReflectBase
{
public:
	PluginBase();
	virtual ~PluginBase();
public:
	virtual void InitPlugin()=0;

};
#define REGISTER_PLUGIN REGISTER_REFLECT

#endif // PluginBase_h__
