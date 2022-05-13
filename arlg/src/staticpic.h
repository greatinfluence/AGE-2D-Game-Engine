#ifndef STATICPIC_H_
#define STATICPIC_H_
#include "engine/object.h"
#include <memory>
namespace arlg{

using namespace umity;
using std::unique_ptr;

class Staticpic: public Object {
	public:
	Staticpic(unique_ptr<Paintable> image, Gamescene& gs, Pos ps,
		std::string name = "staticpic", std::string cls = "Staticpic");
};

}
#endif
