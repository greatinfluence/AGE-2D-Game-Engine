#ifndef FIRE_H_
#define FIRE_H_
#include "engine/object.h"

namespace arlg {

using namespace umity;

class Bullet;

class Fire: public Object {
	Ch sfire, bfire;
	public:
	Fire(Gamescene& gs, Pos ps);
	void run() override;
	void accept(Object& other, Vec normal) override;
	void onhit(Bullet& other, Vec normal);
	void afterkill() override;
};

}

#endif
