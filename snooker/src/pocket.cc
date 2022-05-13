#include "pocket.h"
#include "whiteball.h"
#include "referee.h"
namespace snooker {

using std::make_unique;

Pocket::Pocket(Gamescene& gs, Pos ps):
		Object(nullptr, make_unique<Squarebox>(2., 2.), Vec{0, 0}, 0, gs, ps, "pocket", "Pocket") {
	auto im = make_unique<Rec>(' ', 4, 4);
	im -> setdiff(Vec{-2, -2});
	im -> setcolpr(5);
	getimage() = std::move(im);
	setcb(0x2);
	setmb(0x1);
	beview();
	setus(true);
}

void Pocket::accept(Object& other, Vec normal) {
	if(other.getname() == "whiteball")
		static_cast<Whiteball&>(other).onhit(static_cast<Pocket&>(*this), normal);
	else if(other.getcls() == "Ball")
		static_cast<Ball&>(other).onhit(static_cast<Pocket&>(*this), normal);
	else Object::accept(other, normal);
}

void Pocket::onhit(Ball& other, Vec normal) {
	static_cast<Referee&>(getgs()).receiveball(other.getname());
}

}
