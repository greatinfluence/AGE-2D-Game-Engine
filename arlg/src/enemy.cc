#include "enemy.h"
#include "random.h"
#include "player.h"
#include <cassert>
namespace arlg {

using std::make_unique;

Enemy::Enemy(unique_ptr<Paintable> image, unique_ptr<Hitbox> hb, Abstrlevel& gs, Pos ps,
				hptype maxhp, hptype hp):
	IDamagable(std::move(image), std::move(hb),
		Vec{0, 0}, 60, gs, ps, "enemy", maxhp, hp) {
	setcb(0x2);
	setmb(0x35);
	++ gs.getnene();
}

Enemy::~Enemy() {}

void Enemy::accept(Object& other, Vec normal) {
	if(other.getname() == "player") {
		static_cast<Player&>(other).onhit(static_cast<Enemy&>(*this), normal);
	}
	else IDamagable::accept(other, normal);
}

void Enemy::afterkill() {
	-- static_cast<Abstrlevel&>(getgs()).getnene();
}

Walker::Walker(Abstrlevel& gs, Pos ps):
	Enemy(nullptr, make_unique<Squarebox>(1, 1), gs, ps, 3, 3) {
	umity::Rec im{'a', 2, 2};
	im.setdiff(Vec{-1, -1});
	getimage() = make_unique<umity::Rec>(im);
	setm(200);
}

void Walker::move(timetype t) {
	if(v.normsq() < 1e-3) {
		// is static
		if(judge(0.25)) {
			if(judge(0.25)) setv(Vec{1.9, 0});
			else if(judge(0.3334)) setv(Vec{-1.9, 0});
			else if(judge(0.5)) setv(Vec{0, 1.9});
			else setv(Vec{0, -1.9});
		}
	}
	else {
		// is moving
		if(judge(0.2)) {
			setv(Vec{0, 0});
		}
	}
	Enemy::move(t);
}

Stalker::Stalker(Abstrlevel& gs, Pos ps, Pos const& pp):
	Enemy(nullptr, make_unique<Squarebox>(1, 1), gs, ps, 2, 2), pp{pp} {
	umity::Rec im{'b', 2, 2};
	im.setdiff(Vec{-1, -1});
	getimage() = make_unique<umity::Rec>(im);
	setm(200);
}

void Stalker::move(timetype t) {
	Vec toplayer = pp - getpos();
	setv(toplayer / sqrt(toplayer.normsq()));
	Enemy::move(t);
}

void Stalker::afterkill() {
	if(judge(0.25)) {
		auto& gs = static_cast<Abstrlevel&>(getgs());
		auto wk = make_unique<Walker>(gs, getpos());
		wk -> visiblize();
		wk -> hittablize();
		gs.addobject(std::move(wk));
	}
	Enemy::afterkill();
}

Popup::Popup(Abstrlevel& gs, Pos ps, timetype mxcd, timetype aspd, timetype lst):
	Enemy(nullptr, make_unique<Squarebox>(0.5, 0.5), gs, ps, 4, 4), mxcd{mxcd}, aspd{aspd},
		lst{lst}, cd{0.00001}, hsst{0}, ivstate{'c'}, vstate{'D'} {
	setus(true);
	ivstate.setdiff(Vec{-0.5, -0.5});
	vstate.setdiff(Vec{-0.5, -0.5});
	getimage() = std::move(make_unique<Ch>(ivstate));
	beinvul();
}

void Popup::move(timetype t) {
	if(cd > 0) {
		cd += t;
		if(cd > mxcd) {
			bevul();
			getimage() = std::move(make_unique<Ch>(vstate));
			hsst = 0;
			cd = -0.0001;
		}
	}
	else {
		cd -= t;
		if(cd < - lst) {
			beinvul();
			getimage() = std::move(make_unique<Ch>(ivstate));
			cd = 0.0001;
		}
	}
}

void Popup::run() {
	if(cd < 0) {
		auto& gs = getgs();
		int s = - cd / aspd;
		if(s > hsst) {
			auto bu = make_unique<Bullet>(getgs(), Vec{-1, 0}, getpos(), false);
			bu -> visiblize();
			bu -> hittablize();
			gs.addobject(std::move(bu));
			auto bd = make_unique<Bullet>(getgs(), Vec{1, 0}, getpos(), false);
			bd -> visiblize();
			bd -> hittablize();
			gs.addobject(std::move(bd));
			auto bl = make_unique<Bullet>(getgs(), Vec{0, -1}, getpos(), false);
			bl -> visiblize();
			bl -> hittablize();
			gs.addobject(std::move(bl));
			auto br = make_unique<Bullet>(getgs(), Vec{0, 1}, getpos(), false);
			br -> visiblize();
			br -> hittablize();
			gs.addobject(std::move(br));
			hsst = s;
		}
	}
}

float const SPD = 1.9;

static Vec const dirs[4] = {Vec{SPD, 0}, Vec{0, SPD}, Vec{-SPD, 0}, Vec{0, -SPD}};

SnakeHead::SnakeHead(Abstrlevel& gs, Pos ps):
	Enemy(nullptr, make_unique<Squarebox>(0.5, 0.5), gs, ps, 10000, 10000), dir{randint(0, 3)} {
	Ch im{'Z'};
	im.setdiff(Vec{-0.5, -0.5});
	getimage() = make_unique<Ch>(im);
	setm(1000);
	setv(dirs[dir]);
	beinvul();
}

int SnakeHead::getdir() const { return dir; }

void SnakeHead::move(timetype t) {
	if(Dot(dirs[dir], getv()) <= 0){
		// The snake is moving in the opposite direction
		dir = (dir + 2) & 3;
		getpos() = getpos() + dirs[dir] * (4 / SPD);
		assert(getpos().x > 0 && getpos().y > 0);
	}
	setv(dirs[dir]);
	sethp(10000);
	Enemy::move(t);
}

void SnakeHead::run() { assert(!ifvul()); beinvul(); }

SnakeBody::SnakeBody(Abstrlevel& gs, SnakeHead& hd):
		Enemy(nullptr, nullptr, gs, hd.getpos(), 3, 3),	hd{hd} {
	if(hd.getdir() & 1) {
		Rec im{'z', 1, 3};
		im.setdiff(Vec{-0.5, -1.5});
		Squarebox box{0.5, 1.5};
		getimage() = make_unique<Rec>(im);
		getbox() = make_unique<Squarebox>(box);
	} else {
		Rec im{'z', 3, 1};
		im.setdiff(Vec{-1.5, -0.5});
		Squarebox box{1.5, 0.5};
		getimage() = make_unique<Rec>(im);
		getbox() = make_unique<Squarebox>(box);
	}
	getpos() = hd.getpos() - dirs[hd.getdir()] * (2 / SPD);
	setm(3000);
}

void SnakeBody::move(timetype t) {
	setv(hd.getv());
	getpos() = hd.getpos() - dirs[hd.getdir()] * (2 / SPD);
}

void SnakeBody::afterkill() {
	hd.getcountdown() = 5;
}

}
