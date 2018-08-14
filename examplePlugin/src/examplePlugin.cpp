#include "exampleplugin.h"

#include <iostream>
examplePlugin::examplePlugin()
{

}

examplePlugin::~examplePlugin()
{

}

void examplePlugin::InitPlugin()
{
	std::cout << "init example";
}
