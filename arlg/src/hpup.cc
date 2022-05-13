#include "hpup.h"
#include "idamagable.h"
namespace arlg {

using std::make_unique;

Hpup::Hpup(Gamescene& gs, Pos ps): Object(nullptr, make_unique<Squarebox>(0.5, 0.5), Vec{0, 0}, 0,
	gs, ps, "hpup", "Hpup") {
	auto im = Ch{'h'};
	im.setdiff(Vec{-0.5, -0.5});
	getimage() = std::move(make_unique<Ch>(im));
	beview();
	setus(true);
	setcb(0x20);
	setmb(0x3);
}

void Hpup::accept(Object& other, Vec normal) {
	if(other.getcls() == "Damagable")
		static_cast<IDamagable&>(other).onhit(static_cast<Hpup&>(*this), normal);
}

void Hpup::onhit(IDamagable& other, Vec normal) {
	getcountdown() = 5;
}

}
