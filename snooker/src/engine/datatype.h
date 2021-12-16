#ifndef DATATYPE_H_
#define DATATYPE_H_
#include <cstdint>
#include <stdexcept>
#include <cmath>
namespace umity {

using dptype = int32_t;
using postype = float;
using pixeltype = int32_t;
using timetype = float;

timetype const time_prec = 0.001; // The precision of the timetype

struct Vec {
	postype y, x;
	Vec(postype y, postype x);
	postype normsq() const;
	Vec operator+(Vec const& other) const;
	Vec operator-(Vec const& other) const;
	Vec operator*(timetype const t) const;
	Vec operator/(timetype const t) const;
};

struct Pos {
	postype y, x;
	dptype dep;
	Vec operator-(Pos const& other) const;
	Pos operator+(Vec const& other) const;
	Pos operator-(Vec const& other) const;
	Pos& operator+=(Vec const& other);
	Pos& operator-=(Vec const& other);
};

postype Dot(Vec a, Vec b);

pixeltype getpixeltype(postype x);

postype sq(postype x);
}
#endif
