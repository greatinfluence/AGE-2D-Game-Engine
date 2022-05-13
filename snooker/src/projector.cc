#include "projector.h"
namespace snooker {

Projector::Projector(Gamescene& gs, Pos ps, Vec v, timetype lt):
	Object(nullptr, nullptr, v, 0, gs, ps, "projector", "Projector"), lt{lt} {
	auto im = std::make_unique<Ch>('*');
	im -> setdiff(Vec{-0.5, -0.5});
	im -> setcolpr(1);
	getimage() = std::move(im);
}

void Projector::move(timetype t) {
	lt -= t;
	if(lt == 0) getcountdown() = 5;
	Object::move(t);
}

}
