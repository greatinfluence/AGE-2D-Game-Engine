#include "player.h"
#include "exit.h"
#include <cassert>
namespace arlg {

Player::Player(Gamescene& gs, Pos ps, hptype maxhp, hptype hp, timetype mxcd):
	IDamagable(nullptr,
		std::make_unique<umity::Squarebox>(.5, .5),
		Vec{0, 0}, 60, gs, ps, "player", maxhp, hp), mxcd{mxcd}, cd{mxcd} {
	umity::Ch playerch{'p'};
	playerch.setdiff(Vec{-0.5, -0.5});
	playerch.setcolpr(3);
	getimage() = std::make_unique<umity::Ch>(playerch);
	setcb(0x1);
	setmb(0x7A);
}

void Player::accept(Object& other, Vec normal) { 
	if(other.getcls() == "Exit") {
		static_cast<Exit&>(other).onhit(static_cast<Player&>(*this), normal);
	}
	else {
		IDamagable::accept(other, normal);
	}
}

void Player::onhit(Enemy& other, Vec normal) {
	changehp(-1);
	beinvul();
}

void Player::move(char dir) {
	if(dir == 'w') setv(Vec{-2, 0});
	else if(dir == 's') setv(Vec{2, 0});
	else if(dir == 'a') setv(Vec{0, -2});
	else if(dir == 'd') setv(Vec{0, 2});
}

using umity::postype;

void Player::shoot(char dir) {
	if(cd < mxcd) return;
	cd = 0;
	postype const BS = 1.9; // bullet speed
	auto& gs = getgs();
	using std::make_unique;
	if(dir == 'w') {
		auto bul = make_unique<Bullet>(gs, Vec{-BS, 0},	getpos(), true);
		bul -> visiblize();
		bul -> hittablize();
		gs.addobject(std::move(bul));
	}
	else if(dir == 's') {
		auto bul = make_unique<Bullet>(gs, Vec{BS, 0},	getpos(), true);
		bul -> visiblize();
		bul -> hittablize();
		gs.addobject(std::move(bul));
	}
	else if(dir == 'a') {
		auto bul = make_unique<Bullet>(gs, Vec{0, -BS},	getpos(), true);
		bul -> visiblize();
		bul -> hittablize();
		gs.addobject(std::move(bul));
	}
	else if(dir == 'd') {
		auto bul = make_unique<Bullet>(gs, Vec{0, BS},	getpos(), true);
		bul -> visiblize();
		bul -> hittablize();
		gs.addobject(std::move(bul));
	}
}

void Player::move(timetype t) {
	cd += t;
	IDamagable::move(t);
}

void Player::afterkill() {
	auto& gs = getgs();
	gs.getgb().addscene("gameover");
	gs.sceneover();
}

}
