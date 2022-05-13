#ifndef LEVEL_H_
#define LEVEL_H_
#include "abstrlevel.h"
#include "random.h"
#include "enemy.h"
#include "player.h"
#include "exit.h"
namespace arlg {

class Level: public Abstrlevel {
	public:
	Level(Gamebody& gb, uint8_t lev);
	void preparation() override;
	void logicbeforemove() override;
	void logicaftermove() override;
};
}
#endif
