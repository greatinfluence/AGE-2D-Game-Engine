#ifndef GAMEOVER_H_
#define GAMEOVER_H_
#include "engine/gamescene.h"

namespace arlg {

using namespace umity;

class Gameover: public Gamescene {
	public:
	Gameover(Gamebody& gb);
	void preparation() override;
	void logicbeforemove() override;
};

}
#endif
