#include "staticpic.h"
#include <cassert>

namespace arlg {

Staticpic::Staticpic(unique_ptr<Paintable> image, Gamescene& gs, Pos ps,
		std::string name, std::string cls):
			Object(std::move(image), nullptr, Vec{0, 0}, 0, gs, ps, name, cls) {}

}
