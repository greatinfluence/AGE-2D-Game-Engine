#ifndef BULLET_H_
#define BULLET_H_
#include "engine/object.h"
namespace arlg {

using namespace umity;

class Bullet: public Object {
	public:
	Bullet(Gamescene& gs, Vec v, Pos ps, bool isfr);
	void accept(Object& other, Vec normal) override;
};

}
#endif
