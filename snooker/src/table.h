#ifndef TABLE_H_
#define TABLE_H_
#include "engine/object.h"

namespace snooker {

using namespace umity;

class Table: public Object {
	public:
	Table(Gamescene& gs, Pos ps);
};

}
#endif
