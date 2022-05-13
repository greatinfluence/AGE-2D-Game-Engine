#include "hittype.h"
#include <utility>
namespace umity {

Hitbox::~Hitbox() {}

Squarebox::Squarebox(postype hfhet, postype hfwid):
						hfhet{hfhet}, hfwid{hfwid} {}

Roundbox::Roundbox(postype r): r{r} {}

HitboxType Squarebox::gettype() const {return HitboxType::square;}
HitboxType Roundbox::gettype() const {return HitboxType::round;}

// justcollide(base, v, r) return t such that |v * t + base| = r
static timetype justcollide(Vec base, Vec v, postype r) {
	timetype lb = - time_prec, rb = 0;
	while((base + v * lb).normsq() < sq(r)) {
		lb *= 2;
		if(lb < 1e7) return 0;
	}
	rb = lb / 2;
	while(rb >= lb + time_prec) {
		timetype md = (lb + rb) / 2;
		if((base + v * md).normsq() < sq(r)) rb = md;
		else lb = md;
	}
	return lb;
}

hitinfotype Squarebox::ishit(Pos nps, Vec nv, Hitbox const& other,
										Pos ops, Vec ov) const {
	if(nps.dep != ops.dep) {
		// objects in different layers never collides
		return nullptr;
	}
	nps = nps + nv * time_prec; // move a little
	ops = ops + ov * time_prec;
	bool fpx = false, fpy = false; // fpx denotes if x axis is flipped, so does fpy
	if(nps.x > ops.x) {
		// We can do such transformation because the position of each objects
		//     doesn't matter, what matters is their relative position
		std::swap(nps.x, ops.x);
		nv.x = - nv.x;
		ov.x = - ov.x;
		fpx = true;
	}
	if(nps.y > ops.y) {
		// same reason as code above
		std::swap(nps.y, ops.y);
		nv.y = - nv.y;
		ov.y = - ov.y;
		fpy = true;
	}
	if(other.gettype() == HitboxType::square) {
		Squarebox const& o = static_cast<Squarebox const&>(other);
		if(nps.x + (postype) hfwid >= ops.x - (postype) o.hfwid &&
			nps.y + (postype) hfhet >= ops.y - (postype) o.hfhet) {
			// collides, move the object backwards to see what is the hit direction
			if((ops.x - nps.x - o.hfwid - hfwid) * (nv.y - ov.y)
				<= (ops.y - nps.y - o.hfhet - hfhet) * (nv.x - ov.x)) {
				// collides on x direction
				return std::move(std::make_unique<Vec>(1, 0));
			}
			else {
				// collides on y direction
				return std::move(std::make_unique<Vec>(0, 1));
			}
		}
		else {
			// No collision
			return nullptr;
		}
	}
	else if(other.gettype() == HitboxType::round) {
		Roundbox const& o = static_cast<Roundbox const&>(other);
		//gamelogger << nps.x << ' ' << nps.y << ' ' << ops.x << ' ' << ops.y << std::endl;
		if(ops.x <= nps.x + (postype) hfwid) {
			// Could only collids the width
			if(ops.y - nps.y <= (postype) o.r) {
				return std::move(std::make_unique<Vec>(1, 0));
			}
			else {
				return nullptr;
			}
		}
		else if(ops.y <= nps.y + (postype) hfhet) {
			// Could only collids the height
			if(ops.x - nps.x <= (postype) o.r) {
				return std::move(std::make_unique<Vec>(0, 1));
			}
			else {
				return nullptr;
			}
		}
		else {
			// Could only collids the corner
			if((ops - nps - Vec{(postype) hfhet, (postype) hfwid}).normsq()
					<= sq(o.r)) {
				// get the instant of collision
				timetype t = justcollide(ops - nps -
											Vec{(postype) hfhet, (postype) hfwid},
												ov - nv, o.r);
				Vec nm{ops - nps + (ov - nv) * t -
							Vec{(postype) hfhet, (postype) hfwid}};
				if(fpx) nm.x = - nm.x;
				if(fpy) nm.y = - nm.y;
				return std::move(std::make_unique<Vec>(std::move(nm)));
			}
			else {
				return nullptr;
			}
		}
	}
	else {
		throw std::invalid_argument("Unrecongnized type of hitbox");
	}
}

hitinfotype Roundbox::ishit(Pos nps, Vec nv, Hitbox const& other,
									Pos ops, Vec ov) const {
	if(nps.dep != ops.dep) {
		// objects in different layers never collides
		return nullptr;
	}
	if(other.gettype() == HitboxType::square) {
		// We have written square collide circle, so just reuse it
		return other.ishit(ops, ov, *this, nps, nv);
	}
	else if(other.gettype() == HitboxType::round) {
		nps = nps + nv * time_prec;
		ops = ops + ov * time_prec;
		Roundbox const& o = static_cast<Roundbox const&>(other);
		if((nps - ops).normsq() < sq(r + o.r)) {
			// collides
			timetype t = justcollide(ops - nps, ov - nv, r + o.r);
			return std::move(std::make_unique<Vec>(std::move(
				nps - ops + (nv - ov) * t)));
		}
		else {
			return nullptr;
		}
	}
	else {
		throw std::invalid_argument("Unrecongnized type of hitbox");
	}
}
}
