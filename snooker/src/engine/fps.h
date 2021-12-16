#ifndef FPS_H_
#define FPS_H_
#include "datatype.h"

namespace umity {

class Fpsmanager {

	timetype fps, timediff;
	uint32_t mtdiff;
	public:
	Fpsmanager(timetype fps = 2);
	timetype getfps();

	timetype gettimediff();

	uint32_t getmtdiff();

	void modiffps(timetype nfps);
};

}

#endif
