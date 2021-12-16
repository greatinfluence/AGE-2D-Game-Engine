#ifndef CREDIT_H_
#define CREDIT_H_
#include "engine/gamescene.h"
#include "engine/readbitmap.h"
#include "staticpic.h"

namespace arlg {
using namespace umity;

class Credit: public Gamescene {
	public:
	Credit(Gamebody& gb);
	void preparation() override;
	void logicbeforemove() override;

};

}

#endif
