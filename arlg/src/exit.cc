#include "exit.h"
namespace arlg {

using umity::Ch;
using umity::Squarebox;

Exit::Exit(Gamescene& gs, Pos ps):
	Object(nullptr, std::make_unique<Squarebox>(0.5, 0.5), Vec{0, 0}, 0,
				gs, ps, "exit", "Exit"), activated{false} {
	Ch im{'e'};
	im.setdiff(Vec{-0.5, -0.5});
	getimage() = std::move(std::make_unique<Ch>(im));
	beview();
	setcb(0x40);
	setmb(0x1);
}

void Exit::accept(Object& other, Vec normal) { other.onhit(static_cast<Exit&>(*this), normal); }

void Exit::onhit(Player& other, Vec normal) {
	if(activated) {
		auto& gs = getgs();
		auto& gb = gs.getgb();
		uint8_t lev = static_cast<Abstrlevel&>(gs).getlev();
		if(lev <= 4) {
			gb.addscene("Level" + std::to_string(lev + 1));
		}
		else {
			gb.addscene("Finalrush");
		}
		gs.sceneover();
	}
}

void Exit::run() {
	if(!activated && static_cast<Abstrlevel&>(getgs()).getnene() == 0) {
		activated = true;
		Ch im{'E'};
		im.setdiff(Vec{-0.5, -0.5});
		getimage() = std::move(std::make_unique<Ch>(im));
	}
}

}
