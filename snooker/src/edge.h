#ifndef EDGE_H_
#define EDGE_H_
#include"engine/object.h"

namespace snooker {

using namespace umity;

class Edge: public Object {
	public:
	Edge(Gamescene& gs, Pos ps, pixeltype het, pixeltype wid);
};

}

#endif
