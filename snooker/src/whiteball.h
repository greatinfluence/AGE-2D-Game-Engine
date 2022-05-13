#ifndef WHITEBALL_H_
#define WHITEBALL_H_
#include "ball.h"

namespace snooker {

static float const tau = 6.2831853;

class Whiteball: public Ball {
	float mxcd, cd;
	float angle, mag;
	Vec dir;
	bool canplace;
	public:
	Whiteball(Gamescene& gs, Pos ps);
	void behit();
	void changeangle(postype diff);
	void changemag(postype diff);
	void onhit(Object& other, Vec normal) override;
	void onhit(Pocket& other, Vec normal) override;
	bool ifplace() const;
	void move(timetype t) override;
	void run() override;
};
}

#endif
