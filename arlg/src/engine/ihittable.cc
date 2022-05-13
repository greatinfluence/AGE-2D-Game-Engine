#include "ihittable.h"
#include <utility>
namespace umity {

IHittable::IHittable(unique_ptr<Hitbox> hb, Vec v, masstype m):
	hb{std::move(hb)}, v{v}, m{m}, f{0, 0}, bounce{1},
						cBit{0}, mBit{0}, unstoppable{false} {}

void IHittable::setv(Vec nv) { v = nv; }
Vec IHittable::getv() const { return v; }

void IHittable::setf(Vec nf) { f = nf; }
Vec IHittable::getf() const { return f; }

void IHittable::setm(float nm) { m = nm; }
float IHittable::getm() const { return m; }

void IHittable::setb(float nb) { bounce = nb; }
float IHittable::getb() const { return bounce; }

void IHittable::setcb(uint16_t ncb) { cBit = ncb; }
uint16_t IHittable::getcb() const { return cBit; }

void IHittable::setmb(uint16_t nmb) { mBit = nmb; }
uint16_t IHittable::getmb() const { return mBit; }

void IHittable::setus(bool nus) { unstoppable = nus; }
bool IHittable::isus() const { return unstoppable; }

void IHittable::addv(Vec nv) {v = v + nv;}

void IHittable::addf(Vec nf) {f = f + nf;}

void IHittable::addimp(Vec np) {v = v + np / m;}

unique_ptr<Hitbox>& IHittable::getbox() { return hb; }
unique_ptr<Hitbox> const& IHittable::getbox() const { return hb; }


hitinfotype IHittable::ishit(Pos nps, IHittable const& other, Pos ops) const {
	if((cBit & other.getmb()) == 0 || (mBit & other.getcb()) == 0) {
		// They can never collide due to filtering
		return nullptr;
	}
	if(unstoppable && other.isus()) {
		// unstoppable objects never collides with each other
		return nullptr;
	}
	return std::move(hb -> ishit(nps, v, *other.hb, ops, other.getv()));
}
}
