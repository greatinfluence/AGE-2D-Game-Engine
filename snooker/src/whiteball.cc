#include "whiteball.h"
#include <cmath>
#include "projector.h"
#include "referee.h"

namespace snooker {

using std::make_unique;

Whiteball::Whiteball(Gamescene& gs, Pos ps): Ball(gs, ps, "white", 1),
						mxcd{1.}, cd{0}, angle{0}, mag{1.}, dir{0, 1}, canplace{true} {}

void Whiteball::behit() {
	setv(dir);
}

void Whiteball::changeangle(postype diff) {
	if(diff >= tau) diff -= floor(diff / tau) * tau;
	else if(diff < 0) diff += ceil(- diff / tau) * tau;
	angle += diff;
	if(angle < 0) angle += tau;
	else if(angle >= tau) angle -= tau;
	dir = Vec{mag * (postype)sin(angle), mag * (postype)cos(angle)};
}

void Whiteball::changemag(postype diff) {
	mag += diff;
	if(mag < 0) mag = 0;
	postype mxmag = getgs().getgb().getfm().getfps();
	if(mag > mxmag) mag = mxmag;
	dir = Vec{mag * (postype)sin(angle), mag * (postype)cos(angle)};
}

void Whiteball::onhit(Object& other, Vec normal) {
	canplace = false;
} 

void Whiteball::onhit(Pocket& other, Vec normal) { setv(Vec{0, 0}); } 

bool Whiteball::ifplace() const { return canplace; }

void Whiteball::move(timetype t) {
	if(getv().normsq() <= 1e-3 && mag > 0 && !ifview() &&
			!static_cast<Referee&>(getgs()).ismoving()) {
		cd += t;
		if(cd < mxcd) {
			Ball::move(t);
			return;
		}
		cd = 0;
		// Static, and could be hit, throw projector
		Pos prjps = getpos();
		-- prjps.dep;
		auto prj = make_unique<Projector>(getgs(), prjps, dir, mag / af);
		prj -> visiblize();
		getgs().addobject(std::move(prj));
	}
	Ball::move(t);
}

void Whiteball::run() {
	canplace = true;
}

}
