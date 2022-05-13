#ifndef REFEREE_H_
#define REFEREE_H_
#include "engine/gamescene.h"

namespace snooker {

using namespace umity;

class Referee: public Gamescene {
	int score[2];
	int cur;
	bool isreplacing;
	int nredballs;
	bool lasred;
	int ncolorballs;
	bool ballmoving;
	bool getpoint;
	public:
	Referee(Gamebody& gb);
	void receiveball(string name);
	void preparation() override;
	void logicbeforemove() override;
	void logicaftermove() override;
	bool ismoving() const;
};

}

#endif
