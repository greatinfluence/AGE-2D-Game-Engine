#ifndef ENEMY_H_
#define ENEMY_H_
#include "idamagable.h"
#include "abstrlevel.h"
#include "fire.h"
namespace arlg {

class Enemy: public IDamagable {
	public:
	Enemy(unique_ptr<Paintable> image, unique_ptr<Hitbox> hb, Abstrlevel& gs, Pos ps,
			hptype maxhp, hptype hp);
	virtual ~Enemy();
	void accept(Object& other, Vec normal) override;
	void afterkill() override;
};

class Walker: public Enemy {
	public:
	Walker(Abstrlevel& gs, Pos ps);
	void move(timetype t) override;
};

class Stalker: public Enemy {
	Pos const& pp; // player's pos
	public:
	Stalker(Abstrlevel& gs, Pos ps, Pos const& pp);
	void move(timetype t) override;
	void afterkill() override;
};

class Popup: public Enemy {
	timetype mxcd; // max cd
	timetype aspd; // attack speed
	timetype lst; // skill lasting
	timetype cd;
	int hsst; // has shoot
	Ch ivstate, vstate;
	public:
	Popup(Abstrlevel& gs, Pos ps, timetype mxcd = 3, timetype aspd = 1.5, timetype lst = 3.2);
	void move(timetype t) override;
	void run() override;
};

class SnakeHead: public Enemy {
	int dir;
	public:
	SnakeHead(Abstrlevel& gs, Pos ps);
	int getdir() const;
	void move(timetype t) override;
	void run() override;
};

class SnakeBody: public Enemy {
	SnakeHead& hd;
	public:
	SnakeBody(Abstrlevel& gs, SnakeHead& hd);
	void move(timetype t) override;
	void afterkill() override;
};

}
#endif
