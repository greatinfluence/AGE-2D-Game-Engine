#ifndef POCKET_H_
#define POCKET_H_
#include "engine/object.h"
namespace snooker {

using namespace umity;

class Ball;

class Pocket: public Object {
	public:
	Pocket(Gamescene& gs, Pos ps);
	void accept(Object& other, Vec normal) override;
	void onhit(Ball& other, Vec normal);
};

}

#endif
