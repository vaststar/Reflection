#ifndef ReflectCore_h__
#define ReflectCore_h__

#include <string>
#include <map>
#include "ReflectCore_global.h"
//反射核心功能
class ReflectBase;
class ReflectFactory;
class REFLECTCORE_LIB_EXPORT ReflectCore
{
public:
	const std::map<std::string,ReflectBase *> &getReflects()const;
	void registerReflectFactory(const std::string &className, ReflectFactory *const factory);
	void loadReflectLib(const std::string &className,const std::string &libPath);
public:
	static ReflectCore *Instance();
	~ReflectCore();
private:
	explicit ReflectCore();
	static ReflectCore *_instance;
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
	ReflectCore(const ReflectCore &) = delete;
	ReflectCore(ReflectCore &&) = delete;
	ReflectCore &operator=(const ReflectCore &) = delete;
	ReflectCore &operator=(ReflectCore &&) = delete;
private:
	class DataPrivate;
	DataPrivate *_p;
};
#endif // ReflectCore_h__

