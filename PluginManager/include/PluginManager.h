#ifndef PluginCore_h__
#define PluginCore_h__

#include <string>
#include <vector>
#include <map>
#include "PluginManager_global.h"
//������Ĺ���
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
	class CGarbo // ����Ψһ��������������������ɾ��ʵ���������ڳ����˳�ʱ��ȫ�ֱ����ᱻ���������ԣ�
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
	static CGarbo Garbo; // ����һ����̬��Ա���ڳ������ʱ��ϵͳ�����������������
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

