#ifndef CREDIT_H_
#define CREDIT_H_
#include "engine/gamescene.h"
#include "engine/readbitmap.h"
#include "staticpic.h"

namespace snooker {
using namespace umity;

class Credit: public Gamescene {
	int winner;
	public:
	Credit(Gamebody& gb, int winner);
	void preparation() override;
	void logicbeforemove() override;

};

}

#endif
