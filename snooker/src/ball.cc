#include "ball.h"
#include "pocket.h"
#include "engine/readbitmap.h"
namespace snooker {
using std::make_unique;

Ball::Ball(Gamescene& gs, Pos ps, string name, int color):
	Object(nullptr, make_unique<Roundbox>(1.5), Vec{0, 0}, 10, gs, ps, name, "Ball") {
	auto im = make_unique<Bm>(readbitmap("pic/ball.txt", true));
	im -> setdiff(Vec{-1.5, -1.5});
	im -> setcolpr(color);
	getimage() = std::move(im);
	setcb(0x1);
	setmb(0x3);
}

void Ball::accept(Object& other, Vec normal) {
	if(other.getcls() == "Pocket")
		static_cast<Pocket&>(other).onhit(static_cast<Ball&>(*this), normal);
	else Object::accept(other, normal);
}

void Ball::onhit(Pocket& other, Vec normal) {
	getcountdown() = 5;
}

void Ball::move(timetype t) {
	Vec v = getv();
	Pos ps = getpos();
	if(v.normsq() < sq(0.5)) {
		setv(Vec{0, 0});
		return;
	}
	if(v.normsq() < 1e-3) {
		// The ball is not moving at all
		return;
	}
	Vec a = v / sqrt(v.normsq()) * (- af);
	if(v.normsq() >= sq(af * t)) {
		// The ball's speed has not been decreased to zero
		ps = ps + v * t + a * t * t;
		v = v + a * t;
	}
	else {
		// The ball's speed has been decreased to zero
		timetype t0 = sqrt(v.normsq()) / af;
		ps = ps + v * t0 + a * t0 * t0;
		v = Vec{0, 0};
	}
	getpos() = ps;
	setv(v);
}

}
