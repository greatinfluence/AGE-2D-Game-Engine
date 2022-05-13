#ifndef STARTSCENE_H_
#define STARTSCENE_H_
#include "engine/gamescene.h"
namespace snooker {

using namespace umity;

using std::make_unique;

class Startscene: public Gamescene {
	int option;
	public:
	Startscene(Gamebody& gb);
	void preparation() override;
	void logicbeforemove() override;
};
}
#endif
