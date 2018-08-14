#include "PluginManager.h"

#include <mutex>
#include <algorithm>

#include <ReflectCore/ReflectCore.h>

#include "rapidjson/rapidjson.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/document.h"

#include <PluginCore/PluginBase.h>

class PluginManager::DataPrivate
{
public:
	DataPrivate()
	{

	}
	~DataPrivate()
	{

	}
public:
	std::map<std::string, PluginBase *> plugins;
	std::map<std::string, std::vector<std::string>> pluginConfig;
};

PluginManager::PluginManager()
	:_p(new DataPrivate())
{

}

PluginManager::~PluginManager()
{
	delete _p;
	_p = nullptr;
}

PluginManager * PluginManager::_instance = nullptr;
PluginManager::CGarbo PluginManager::Garbo;
static std::mutex pluginManagerMutex;

PluginManager * PluginManager::Instance()
{
	if (nullptr == _instance)
	{
		std::lock_guard<std::mutex> loc(pluginManagerMutex);
		if (nullptr == _instance)
		{
			_instance = new PluginManager();
		}
	}
	return _instance;
}

void PluginManager::startManager(const std::string &configPath)
{
	static bool alreadyStart = false;
	//读取配置文件，解析需要加载的插件动态库
	if (!alreadyStart && ParseJsonFile(configPath, _p->pluginConfig))
	{
		alreadyStart = true;
		//加载动态库
		for (auto it : _p->pluginConfig)
		{
			if (it.second.size() >= 3 && it.second.at(2) == "true")
			{
				std::string libPath = it.second.at(1) + "/" + it.first + ".dll";
				ReflectCore::Instance()->loadReflectLib(it.first,libPath);
			}
		}
		//取插件
		std::map<std::string, ReflectBase *> reflects = ReflectCore::Instance()->getReflects();
		std::for_each(reflects.begin(), reflects.end(), [this](std::pair<std::string,ReflectBase*> data) {
			if (PluginBase *plug = dynamic_cast<PluginBase*>(data.second))
			{
				_p->plugins.emplace(std::make_pair(data.first, plug));
			}
		});

	}
	alreadyStart = false;
}

const std::map<std::string, PluginBase *> & PluginManager::getPlugins() const
{
	return _p->plugins;
}

const bool ParseJsonDoc(const RAPIDJSON_NAMESPACE::Document &document, std::map<std::string, std::vector<std::string>> &Result)
{
	Result.clear();
	for (RAPIDJSON_NAMESPACE::Value::ConstMemberIterator it = document.MemberBegin(); it != document.MemberEnd(); ++it)
	{
		std::string key = it->name.GetString();
		std::vector<std::string> val;
		bool IsRecongnisable = true;
		switch (it->value.GetType())
		{
		case RAPIDJSON_NAMESPACE::kNullType:
			val.push_back("");
			break;
		case RAPIDJSON_NAMESPACE::kFalseType:
			val.push_back("false");
			break;
		case RAPIDJSON_NAMESPACE::kTrueType:
			val.push_back("true");
			break;
		case RAPIDJSON_NAMESPACE::kStringType:
			val.push_back(it->value.GetString());
			break;
		case RAPIDJSON_NAMESPACE::kNumberType:
			if (it->value.IsInt())
			{
				val.push_back(std::to_string(it->value.GetInt()));
			}
			else if (it->value.IsDouble())
			{
				val.push_back(std::to_string(it->value.GetDouble()));
			}
			break;
		case RAPIDJSON_NAMESPACE::kObjectType:
			IsRecongnisable = false;
			break;
		case RAPIDJSON_NAMESPACE::kArrayType:
			for (RAPIDJSON_NAMESPACE::Value::ConstValueIterator arr = it->value.Begin(); arr != it->value.End(); ++arr)
			{
				if (arr->IsString())
				{
					val.push_back(arr->GetString());
				}
				else if (arr->IsInt())
				{
					val.push_back(std::to_string(arr->GetInt()));
				}
				else if (arr->IsDouble())
				{
					val.push_back(std::to_string(arr->GetDouble()));
				}
				else if (arr->IsFalse())
				{
					val.push_back("false");
				}
				else if (arr->IsTrue())
				{
					val.push_back("true");
				}
				else if (arr->IsNull())
				{
					val.push_back("");
				}
			}
			break;

		default:
			break;
		}
		if (!IsRecongnisable) continue;
		Result[key] = val;
	}

	return true;
}

bool PluginManager::ParseJsonFile(const std::string &filePath, std::map<std::string, std::vector<std::string>> &Results)const
{
	FILE *pFile = nullptr;
	fopen_s(&pFile, filePath.c_str(), "r");
	if (pFile)
	{
		char buffer[65536];
		RAPIDJSON_NAMESPACE::FileReadStream is(pFile, buffer, sizeof(buffer));

		RAPIDJSON_NAMESPACE::Document document;
		if (document.ParseStream<0, RAPIDJSON_NAMESPACE::UTF8<>, RAPIDJSON_NAMESPACE::FileReadStream>(is).HasParseError()) return false;
		return ParseJsonDoc(document, Results);
	}
	return false;
}