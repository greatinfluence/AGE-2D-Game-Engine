#ifndef PLAYER_H_
#define PLAYER_H_
#include "idamagable.h"
#include "enemy.h"
#include "bullet.h"

namespace arlg {

class Player final: public IDamagable {
	timetype mxcd, cd;
	public:
	Player(Gamescene& gs, Pos ps, hptype maxhp, hptype hp, timetype mxcd = 2.);
	void accept(Object& other, Vec normal) override;
	void onhit(Enemy& other, Vec normal);
	void move(char dir);
	void shoot(char dir);
	void move(timetype t) override;
	void afterkill() override;
};
}
#endif
