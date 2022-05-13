#include "fire.h"
#include "idamagable.h"
#include "random.h"
namespace arlg {

using std::make_unique;

Fire::Fire(Gamescene& gs, Pos ps): Object(nullptr, make_unique<Squarebox>(0.5, 0.5), Vec{0, 0}, 0,
	gs, ps, "fire", "Fire"), sfire{'x'}, bfire{'X'} {
	sfire.setdiff(Vec{-0.5, -0.5});
	bfire.setdiff(Vec{-0.5, -0.5});
	beview();
	setus(true);
	getimage() = std::move(make_unique<Ch>(sfire));
	setcb(0x10);
	setmb(0xF);
}

void Fire::run() {
	if(judge(0.7)) {
		if(judge(0.5)) getimage() = std::move(make_unique<Ch>(sfire));
		else getimage() = std::move(make_unique<Ch>(bfire));
	}
}

void Fire::accept(Object& other, Vec normal) {
	if(other.getcls() == "Damagable") {
		static_cast<IDamagable&>(other).onhit(static_cast<Fire&>(*this), normal);
	}
	else if(other.getcls() == "Bullet")
		static_cast<Bullet&>(other).onhit(static_cast<Fire&>(*this), normal);
}

void Fire::onhit(Bullet& other, Vec normal) {
	getcountdown() = 5;
}

void Fire::afterkill() {
	if(judge(0.75)) {
		auto hp = std::make_unique<Hpup>(getgs(), getpos());
		hp -> visiblize();
		hp -> hittablize();
		hp -> beview();
		getgs().addobject(std::move(hp));
		
	}
}

}
