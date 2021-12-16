#ifndef BALL_H_
#define BALL_H_
#include "engine/object.h"
namespace snooker {

using namespace umity;

float const af = 0.05;

class Pocket;

class Ball: public Object {
	public:
	Ball(Gamescene& gs, Pos ps, string name, int color);
	void accept(Object& other, Vec normal) override;
	virtual void onhit(Pocket& other, Vec normal);
	void move(timetype t) override;
};

}

#endif
