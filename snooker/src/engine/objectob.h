#ifndef OBJECTOB_H_
#define OBJECTOB_H_
namespace umity {
class Object;

class ObjectOb {
	public:
	virtual void regist(Object& ob) = 0;
	virtual void deregist(Object& ob) = 0;
};
}
#endif
