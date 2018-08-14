#ifndef ReflectFactory_h__
#define ReflectFactory_h__

#include "ReflectCore_global.h"
class ReflectBase;
class REFLECTCORE_LIB_EXPORT ReflectFactory {
public:
	ReflectFactory();
	virtual ~ReflectFactory();
public:
	virtual ReflectBase * CreateReflect() = 0;
};
#endif // ReflectFactory_h__

