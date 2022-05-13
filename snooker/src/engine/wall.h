#ifndef WALL_H_
#define WALL_H_
#include "object.h"
#include <limits>
namespace umity {

class Wall: public Object {
	public:
	Wall(postype hfhet, postype hfwid, Gamescene& gs, Pos ps);
	void accept(Object& other, Vec normal) override;
};
}
#endif
