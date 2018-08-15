#include "PluginManager/PluginManager.h"
#include "PluginCore/PluginBase.h"
#include <iostream>

int main()
{
	PluginManager::Instance()->startManager("PluginConfig.json");
	PluginManager::Instance()->getPlugins().at("examplePlugin")->InitPlugin();
	system("pause");
	return 0;
}