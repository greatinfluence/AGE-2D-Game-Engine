#ifndef IDAMAGABLE_H_
#define IDAMAGABLE_H_
#include "engine/object.h"
#include "bullet.h"
#include <cstdint>
#include "fire.h"
#include "hpup.h"
namespace arlg {

using hptype = uint16_t;
using std::unique_ptr;

class IDamagable: public Object {
	hptype maxhp;
	hptype hp;
	bool isvul;
	public:
	IDamagable(unique_ptr<Paintable> image, unique_ptr<Hitbox> hb, Vec v,
		masstype m, Gamescene& gs, Pos ps,std::string name, hptype maxhp, hptype hp);
	virtual ~IDamagable();
	void changehp(hptype diff);
	void sethp(hptype nhp);
	hptype gethp();
	hptype getmaxhp();
	bool ifvul();
	void bevul();
	void beinvul();
	void accept(Object& other, Vec normal) override;
	void onhit(Bullet& other, Vec normal);
	void onhit(Fire& other, Vec normal);
	void onhit(Hpup& other, Vec normal);
	void run() override;
};

}
#endif
