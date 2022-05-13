#ifndef FINALRUSH_H_
#define FINALRUSH_H_
#include "level.h"
namespace arlg {

class Finalrush: public Level {
	decltype(objs.begin()) bossps;
	public:
	Finalrush(Gamebody& gb);
	void changeboss();
	void preparation() override;
	void logicaftermove() override;
	Pos& getplayerpos();
};

};

#endif
