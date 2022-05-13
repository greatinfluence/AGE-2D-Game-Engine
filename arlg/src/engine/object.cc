#include "object.h"
#include <utility>
#include <cassert>

namespace umity {

Object::Object(unique_ptr<Paintable> image, unique_ptr<Hitbox> hb, Vec v, masstype m,
		Gamescene& gs, Pos ps, std::string name, std::string cls):
				IDrawable(std::move(image)), IHittable(std::move(hb), v, m),
				gs{gs}, vw{gs.getvw()}, hm{gs.gethm()}, ps{ps}, name{name}, cls{cls},
				visibility{false}, hittability{false}, isview{false}, countdown{-1} {}

Object::~Object() {
	invisiblize();
	unhittablize();
}

void Object::visiblize() {
	if(!visibility) {
		vw.regist(*this);
		visibility = true;
	}
}

void Object::invisiblize() {
	if(visibility) {
		vw.deregist(*this);
		visibility = false;
	}
}

void Object::hittablize() {
	if(!hittability) {
		hm.regist(*this);
		hittability = true;
	}
}

void Object::unhittablize() {
	if(hittability) {
		hm.deregist(*this);
		hittability = false;
	}
}

void Object::beview() { isview = true; }

void Object::besolid() { isview = false; }

bool Object::ifview() { return isview; }

Gamescene& Object::getgs() { return gs; }

postype& Object::getcountdown() { return countdown; }

void Object::run() {}

void Object::afterkill() {}

void Object::move(timetype t) {
	// x = x0 + v0 * t + a * t * t
	// v = v0 + a * t
	// where a = f / m
	Vec a = Vec{0, 0};
	if(m != 0) {
		// We don't consider the acceleration of massless objects
		a = f / m;
	}
	ps = ps + v * t + a * t * t;
	v = v + a * t;
}

hitinfotype Object::ishit(Object& other) const {
	return std::move(IHittable::ishit(ps, other, other.getpos()));
}

void Object::accept(Object& other, Vec normal) { other.onhit(*this, normal); }

void Object::onhit(Object& other, Vec normal) {}

std::string const& Object::getname() const {return name;}

std::string const& Object::getcls() const {return cls;}

Pos& Object::getpos() {return ps;}

Pos const& Object::getpos() const {return ps;}
}
