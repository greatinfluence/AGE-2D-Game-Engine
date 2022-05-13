#include "idamagable.h"
namespace arlg {

IDamagable::IDamagable(unique_ptr<Paintable> image, unique_ptr<Hitbox> hb, Vec v,
	masstype m, Gamescene& gs, Pos ps, std::string name, hptype maxhp, hptype hp):
			Object(std::move(image), std::move(hb), v, m, gs, ps, name, "Damagable"),
			maxhp{maxhp}, hp{hp}, isvul{true} {}

IDamagable::~IDamagable() {}

void IDamagable::changehp(hptype diff) {
	if(!isvul && diff <= 0) return;
	hp += diff;
	if(maxhp > 0 && hp > maxhp) hp = maxhp;
	if(hp <= 0) getcountdown() = 5;
}

void IDamagable::sethp(hptype nhp) {
	hp = nhp;
	if(hp <= 0) getcountdown() = 5;
}

bool IDamagable::ifvul() { return isvul; }

void IDamagable::bevul() { isvul = true; }

void IDamagable::beinvul() { isvul = false; }

void IDamagable::accept(Object& other, Vec normal) {
	if(other.getcls() == "Hpup") {
		static_cast<Hpup&>(other).onhit(static_cast<IDamagable&>(*this), normal);
	}
}

void IDamagable::onhit(Bullet& other, Vec normal) {
	changehp(-1);
	if(gethp() <= 0) {
		getcountdown() = 5;
	}
	beinvul();
}

void IDamagable::onhit(Fire& other, Vec normal) {
	changehp(-1);
	if(gethp() <= 0) {
		getcountdown() = 5;
	}
	beinvul();
}

void IDamagable::onhit(Hpup& other, Vec normal) {
	changehp(1);
	beinvul();
}


void IDamagable::run() {
	if(!isvul) bevul();
}

hptype IDamagable::gethp() { return hp; }
hptype IDamagable::getmaxhp() { return maxhp; }

}
