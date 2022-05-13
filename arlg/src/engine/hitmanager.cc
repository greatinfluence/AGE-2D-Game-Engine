#include "hitmanager.h"
#include <cassert>
#include "object.h"
namespace umity {
void Hitmanager::regist(Object& ih) {
	lst.push_back(&ih);
}

void Hitmanager::deregist(Object& ih) {
	lst.remove(&ih);
}

static void separate(Object& oba, Object& obb, Vec normal) {
	// First, we need to confirm the direction of oba to move to get rid of b
	// We can compute it by <psa - psb, normal> * normal.
	// Similarly the other direction is <psb - psa, normal> * normal.
	Vec dira = normal * Dot(oba.getpos() - obb.getpos(), normal);
	dira = dira / sqrt(dira.normsq()); // Regularize
	Vec dirb = Vec{0, 0} - dira;
	if(oba.isus()) {
		// a should not be moved
		dira = Vec{0, 0};
	}
	else if(obb.isus()) {
		// b should not be moved
		dirb = Vec{0, 0};
	}
	else {
		// move a and b based on the proportion of their mass.
		dira = dira * (oba.getm() / (oba.getm() + obb.getm()));
		dirb = dirb * (obb.getm() / (oba.getm() + obb.getm()));
	}
	timetype lb = 0, rb = time_prec;
	while(1) {
		oba.getpos() += dira * rb;
		obb.getpos() += dirb * rb;
		if(oba.ishit(obb) != nullptr) {
			// Not separated
			oba.getpos() -= dira * rb;
			obb.getpos() -= dirb * rb;
			rb *= 2;
		}
		else {
			// Separated
			oba.getpos() -= dira * rb;
			obb.getpos() -= dirb * rb;
			break;
		}
	}
	while(rb >= lb + time_prec) {
		timetype md = (lb + rb) / 2;
		oba.getpos() += dira * md;
		obb.getpos() += dirb * md;
		if(oba.ishit(obb) != nullptr) lb = md;
		else rb = md;
		oba.getpos() -= dira * md;
		obb.getpos() -= dirb * md;
	}
	oba.getpos() += dira * rb;
	obb.getpos() += dirb * rb;
}

static void moveforbounce(Object& oba, Object& obb, Vec normal) {
	separate(oba, obb, normal);
	float bounce = std::max(oba.getb(), obb.getb()); // The bounce coef used
	// The formula used:
	//     va = (ma*ua + mb*ub + mb*bounce*(ub-ua))/(ma+mb)
	//     vb = (ma*ua + mb*ub + ma*bounce*(ua-ub))/(ma+mb)
	// where this speed exchange will only happens along the direction of hitinfo
	if(oba.isus()) {
		// obb must be common object and ma counts as infty now
		Vec va = oba.getv(), vb = obb.getv();
		Vec vahor = normal * Dot(va, normal) / normal.normsq();
		Vec vbhor = normal * Dot(vb, normal) / normal.normsq();
		Vec vbperp = vb - vbhor;
		vbhor = vahor + (vahor - vbhor) * bounce;
		obb.setv(vbperp + vbhor);
	}
	else if(obb.isus()) {
		// oba must be common object and mb counts as infty now
		Vec va = oba.getv(), vb = obb.getv();
		Vec vahor = normal * Dot(va, normal) / normal.normsq();
		Vec vbhor = normal * Dot(vb, normal) / normal.normsq();
		Vec vaperp = va - vahor;
		vahor = vbhor + (vbhor - vahor) * bounce;
		oba.setv(vaperp + vahor);
	}
	else {
		// They are all regular objects
		Vec va = oba.getv(), vb = obb.getv();
		float ma = oba.getm(), mb = obb.getm();
		Vec vahor = normal * Dot(va, normal) / normal.normsq();
		Vec vbhor = normal * Dot(vb, normal) / normal.normsq();
		Vec nvahor = (vahor * ma + vbhor * mb + (vbhor - vahor) * mb * bounce) /
						(ma + mb);
		Vec nvbhor = (vahor * ma + vbhor * mb + (vahor - vbhor) * ma * bounce) /
						(ma + mb);
		oba.setv(va - vahor + nvahor);
		obb.setv(vb - vbhor + nvbhor);
	}
}

static size_t Nwalls = 4; // The number of the walls

void Hitmanager::detecthit() const {
	for(auto k = 0; k < 5; ++ k) {
	size_t ps = 0;
	for(auto i = lst.begin(); i != lst.end(); ++ i, ++ ps) {
		auto j = i;
		++ j;
		for(; j != lst.end(); ++ j) {
			if((((*i) -> getmb()) & ((*j) -> getcb())) == 0 ||
				(((*i) -> getcb()) & ((*j) -> getmb())) == 0) {
				// They should not collides with each other by design
				continue;
			}
			if(ps < Nwalls) (*i) -> getpos().dep = (*j) -> getpos().dep;
			auto hitinfo = (**i).ishit(**j);
			if(hitinfo != nullptr) {
				(**i).accept(**j, *hitinfo);
				(**j).accept(**i, *hitinfo);
				if(!(*i) -> ifview() && !(*j) -> ifview())
					moveforbounce(**i, **j, *hitinfo);
			}
		}
	}
	}
}
}
