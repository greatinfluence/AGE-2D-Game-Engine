#include "painttype.h"
#include <iostream>
namespace umity {

Bit::Bit(pixeltype y, pixeltype x, char ch): y{y}, x{x}, ch{ch} {}

Paintable::Paintable(): diff{Vec{0, 0}}, colpr{0} {}

void Paintable::setdiff(Vec nd) {
	diff = nd;
}

Vec Paintable::getdiff() {
	return diff;
}

void Paintable::setcolpr(int cp) { colpr = cp; }

int Paintable::getcolpr() { return colpr; }

Paintable::~Paintable() {}

Ch::Ch(char ch): Paintable(), ch{ch} {}

PaintableType Ch::gettype() const {return PaintableType::ch;}

Rec::Rec(char ch, pixeltype het, pixeltype wid): Paintable(), ch{ch}, het{het}, wid{wid}
													{}

PaintableType Rec::gettype() const {return PaintableType::rec;}

Bm::Bm(Bitmap z): Paintable(), z{z} {}

PaintableType Bm::gettype() const {return PaintableType::bm;}

}
