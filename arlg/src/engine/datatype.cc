#include "datatype.h"
namespace umity {

postype sq(postype x) {return x * x;}

Vec::Vec(postype y, postype x): y{y}, x{x} {}

Vec Vec::operator+(Vec const& other) const {
	return Vec{y + other.y, x + other.x};
}

Vec Vec::operator-(Vec const& other) const {
	return Vec{y - other.y, x - other.x};
}

Vec Vec::operator*(timetype const t) const {
	return Vec{y * t, x * t};
}

Vec Vec::operator/(timetype const t) const {
	return Vec{y / t, x / t};
}

postype Vec::normsq() const {
	return sq(y) + sq(x);
}

Vec Pos::operator-(Pos const& other) const {
	return Vec{y - other.y, x - other.x};
}

Pos Pos::operator+(Vec const& other) const {
	return Pos{y + other.y, x + other.x, dep};
}

Pos Pos::operator-(Vec const& other) const {
	return Pos{y - other.y, x - other.x, dep};
}

Pos& Pos::operator+=(Vec const& other) {
	y += other.y;
	x += other.x;
	return *this;
}
Pos& Pos::operator-=(Vec const& other) {
	y -= other.y;
	x -= other.x;
	return *this;
}
postype Dot(Vec a, Vec b) { return a.x * b.x + a.y * b.y; }

pixeltype getpixeltype(postype x) {
	if(x >= 0) return (postype)(x + 0.5);
	else return (postype)(x - 0.5);
}
}
