#include "bullet.h"
#include "idamagable.h"
#include "fire.h"
namespace arlg {

Bullet::Bullet(Gamescene& gs, Vec v, Pos ps, bool isfr):
	Object(nullptr,
		std::make_unique<umity::Squarebox>(0.5, 0.5),
		v, 0.5, gs, ps, "bullet", "Bullet") {
	umity::Ch pic{'O'};
	pic.setdiff(Vec{-0.5, -0.5});
	if(isfr) {
		pic.setcolpr(1);
		setcb(0x4);
		setmb(0x12);
	}
	else {
		pic.setcolpr(2);
		setcb(0x8);
		setmb(0x11);
	}
	getimage() = std::move(std::make_unique<umity::Ch>(pic));
}

void Bullet::accept(Object& other, Vec normal) {
	if(other.getcls() == "Damagable")
		static_cast<IDamagable&>(other).onhit(static_cast<Bullet&>(*this), normal);
	else if(other.getcls() == "Fire")
		static_cast<Fire&>(other).onhit(static_cast<Bullet&>(*this), normal);
	if(!other.ifview()) {
		getcountdown() = 5;
	}
}
}
