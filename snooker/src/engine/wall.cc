#include "wall.h"
#include <cmath>
namespace umity {

Wall::Wall(postype hfhet, postype hfwid, Gamescene& gs, Pos ps):
			Object(nullptr, std::move(std::make_unique<Squarebox>(hfhet, hfwid)),
			Vec{0, 0}, 0, gs, ps, "Wall", "Wall") {
	setcb(0xFFFF);
	setmb(0xFFFF);
	setus(true);
}

void Wall::accept(Object& other, Vec normal) {
	other.onhit(static_cast<Wall&>(*this), normal);
}

}
