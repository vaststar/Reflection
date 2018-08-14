#ifndef ReflectCore_h__
#define ReflectCore_h__

#include <string>
#include <map>
#include "ReflectCore_global.h"
//������Ĺ���
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
	ReflectCore(const ReflectCore &) = delete;
	ReflectCore(ReflectCore &&) = delete;
	ReflectCore &operator=(const ReflectCore &) = delete;
	ReflectCore &operator=(ReflectCore &&) = delete;
private:
	class DataPrivate;
	DataPrivate *_p;
};
#endif // ReflectCore_h__

