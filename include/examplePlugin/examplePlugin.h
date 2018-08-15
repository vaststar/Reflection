#ifndef EXAMPLEPLUGIN_H
#define EXAMPLEPLUGIN_H

#include "exampleplugin_global.h"
#include <PluginCore/PluginBase.h>


class EXAMPLEPLUGIN_EXPORT examplePlugin :public PluginBase
{
public:
	examplePlugin();
	~examplePlugin();
public:
	void InitPlugin()override final;

private:

};
REGISTER_PLUGIN(examplePlugin);

#endif // EXAMPLEPLUGIN_H
