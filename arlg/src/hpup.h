#ifndef HPUP_H_
#define HPUP_H_
#include "engine/object.h"

namespace arlg {

using namespace umity;

class IDamagable;

class Hpup: public Object {
	public:
	Hpup(Gamescene& gs, Pos ps);
	void accept(Object& other, Vec normal) override;
	void onhit(IDamagable& other, Vec normal);

};


}
#endif
