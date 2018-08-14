#include "ReflectCore.h"

#include <algorithm>
#include <mutex>
#include <map>
#include <Windows.h>
#include "ReflectBase.h"
#include "ReflectFactory.h"
class ReflectCore::DataPrivate
{
public:
	DataPrivate()
	{

	}
	~DataPrivate()
	{
		std::lock_guard<std::mutex> loc(dataMutex);
		std::for_each(reflects.begin(), reflects.end(), [](std::pair<std::string, ReflectBase *> data) {
			delete data.second; 
		});
		reflects.clear();
		std::for_each(reflectFactory.begin(), reflectFactory.end(), [](std::pair<std::string,ReflectFactory*> data) {
			delete data.second;
		});
		reflectFactory.clear();
	}
public:
	std::map<std::string, ReflectBase *> reflects;
	std::map<std::string, ReflectFactory*> reflectFactory;
	std::mutex dataMutex;
};

ReflectCore::ReflectCore()
	:_p(new DataPrivate())
{
}

ReflectCore * ReflectCore::_instance = nullptr;
ReflectCore::CGarbo ReflectCore::Garbo;
static std::mutex instanceMutex;

ReflectCore::~ReflectCore()
{
	delete _p;
	_p = nullptr;
}

ReflectCore * ReflectCore::Instance()
{
	if (nullptr == _instance)
	{
		std::lock_guard<std::mutex> loc(instanceMutex);
		if (nullptr == _instance)
		{
			_instance = new ReflectCore();
		}
	}
	return _instance;
}

const std::map<std::string, ReflectBase *> & ReflectCore::getReflects() const
{
	std::lock_guard<std::mutex> loc(_p->dataMutex);
	return _p->reflects;
}

void ReflectCore::registerReflectFactory(const std::string &className, ReflectFactory *const factory)
{
	std::lock_guard<std::mutex> loc(_p->dataMutex);
	if (_p->reflectFactory.find(className) == _p->reflectFactory.end())
	{
		_p->reflectFactory.insert(std::make_pair(className, factory));
	}
}

void ReflectCore::loadReflectLib(const std::string &className, const std::string &libPath)
{
	if (_p->reflectFactory.find(className) != _p->reflectFactory.end()) return;
	if (!::LoadLibrary(libPath.c_str())) return;

	std::lock_guard<std::mutex> loc(_p->dataMutex);
	if (_p->reflectFactory.find(className) != _p->reflectFactory.end())
	{
		_p->reflects.emplace(std::make_pair(className,_p->reflectFactory.at(className)->CreateReflect()));
	}	
}


