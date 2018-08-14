#ifndef PluginCore_h__
#define PluginCore_h__

#include <string>
#include <vector>
#include <map>
#include "PluginManager_global.h"
//反射核心功能
class PluginBase;
class PLUGINMANAGER_LIB_EXPORT PluginManager
{
public:
	void startManager(const std::string &configPath);
	const std::map<std::string, PluginBase *> &getPlugins()const;
private:
	bool ParseJsonFile(const std::string &filePath, std::map<std::string, std::vector<std::string>> &Results)const;
public:
	static PluginManager *Instance();
	~PluginManager();
private:
	explicit PluginManager();
	static PluginManager *_instance;
	class CGarbo // 它的唯一工作就是在析构函数中删除实例（利用在程序退出时，全局变量会被析构的特性）
	{
	public:
		~CGarbo()
		{
			if (_instance)
			{
				delete _instance;
				_instance = nullptr;
			}
		}
	};
	static CGarbo Garbo; // 定义一个静态成员，在程序结束时，系统会调用它的析构函数
public:
	PluginManager(const PluginManager &) = delete;
	PluginManager(PluginManager &&) = delete;
	PluginManager &operator=(const PluginManager &) = delete;
	PluginManager &operator=(PluginManager &&) = delete;
private:
	class DataPrivate;
	DataPrivate *_p;
};
#endif // PluginCore_h__

