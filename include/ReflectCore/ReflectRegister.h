#ifndef Register_h__
#define Register_h__

#include "ReflectBase.h"
#include "ReflectFactory.h"
#include "ReflectCore.h"

#define REGISTER_FACTORY(class_name)\
class ReflectFactory_##class_name:public ReflectFactory{\
public:\
	virtual ReflectBase *CreateReflect(){\
		return new class_name;}\
};\
int register_factory_##class_name(){\
	ReflectCore::Instance()->registerReflectFactory(#class_name , new ReflectFactory_##class_name);\
	return 0;\
}

#define REGISTER_REFLECT(class_name)\
REGISTER_FACTORY(class_name)\
static int register_##class_name = register_factory_##class_name();

#endif // Register_h__