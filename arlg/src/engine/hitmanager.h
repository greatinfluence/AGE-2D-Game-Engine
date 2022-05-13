#ifndef HITMANAGER_H_
#define HITMANAGER_H_
#include "ihittable.h"
#include <list>
#include "objectob.h"
namespace umity {

class Object;

class Hitmanager final: public ObjectOb {
	std::list<Object*> lst;
	public:
	void regist(Object& ih) override;
	void deregist(Object& ih) override;
	void detecthit() const;
};
}
#endif
