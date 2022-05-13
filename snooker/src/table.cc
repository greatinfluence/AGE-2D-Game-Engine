#include "table.h"
namespace snooker {

Table::Table(Gamescene& gs, Pos ps):
	Object(nullptr, nullptr, Vec{0, 0}, 0, gs, ps, "table", "Table") {
	auto im = std::make_unique<Rec>(' ', 68, 136);
	im -> setdiff(Vec{-34, -68});
	im -> setcolpr(1);
	getimage() = std::move(im);
}

}
