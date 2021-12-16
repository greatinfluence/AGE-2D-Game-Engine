#include "edge.h"

namespace snooker {

using std::make_unique;

Edge::Edge(Gamescene& gs, Pos ps, pixeltype het, pixeltype wid):
		Object(nullptr, make_unique<Squarebox>(het / 2.f, wid / 2.f), Vec{0, 0}, 0, gs, ps,
			"edge", "Edge") {
	auto im = make_unique<Rec>('#', het, wid);
	im -> setdiff(Vec{- het / 2.f, - wid / 2.f});
	im -> setcolpr(5);
	getimage() = std::move(im);
	setcb(0x2);
	setmb(0x1);
	setus(true);
}
}
