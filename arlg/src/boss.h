#ifndef BOSS_H_
#define BOSS_H_
#include "enemy.h"
#include "finalrush.h"
namespace arlg {

class Bosspeace: public Enemy {
	public:
	Bosspeace(Abstrlevel& gs, Pos ps);
	void afterkill() override;
};

class Bossrage: public Enemy {
	timetype mxcd, cd;
	public:
	Bossrage(Abstrlevel& gs, Pos ps);
	void summon();
	void move(timetype t) override;
	void afterkill() override;
};

}

#endif
