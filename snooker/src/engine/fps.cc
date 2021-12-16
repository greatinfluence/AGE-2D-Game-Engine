#include "fps.h"
#include <cassert>
namespace umity {

Fpsmanager::Fpsmanager(timetype fps): fps{fps}, timediff{1.f / fps},
										mtdiff{(uint32_t)(1000 / fps)} {}

timetype Fpsmanager::getfps() { return fps; }

timetype Fpsmanager::gettimediff() { return timediff; }

uint32_t Fpsmanager::getmtdiff() { return mtdiff; }

void Fpsmanager::modiffps(timetype nfps) {
	assert(nfps > 0);
	fps = nfps;
	timediff = 1. / fps;
	mtdiff = 1000 / fps;
}

}
