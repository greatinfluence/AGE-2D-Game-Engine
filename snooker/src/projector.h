#ifndef PROJECTOR_H_
#define PROJECTOR_H_
#include "engine/object.h"

namespace snooker {

using namespace umity;

class Projector: public Object {
	timetype lt; // life time
	public:
	Projector(Gamescene& gs, Pos ps, Vec v, timetype lt);
	void move(timetype t) override;
};

}

#endif
