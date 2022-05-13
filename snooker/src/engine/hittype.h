#ifndef HITTYPE_H_
#define HITTYPE_H_
#include "datatype.h"
#include <memory>
namespace umity {

using masstype = float;

enum class HitboxType {square, round};

using hitinfotype = std::unique_ptr<Vec>;
using std::unique_ptr;

class Hitbox {
	public:
	virtual ~Hitbox();
	virtual hitinfotype ishit(Pos nps, Vec nv, Hitbox const& other,
										Pos ops, Vec ov) const = 0;
	virtual HitboxType gettype() const = 0;
};

class Squarebox: public Hitbox {
	public:
	postype hfhet, hfwid; // hfhet and hfwid are one half of the actrual quantities
	Squarebox(postype hfhet, postype hfwid);
	hitinfotype ishit(Pos nps, Vec nv, Hitbox const& other,
								Pos ops, Vec ov) const override;
	HitboxType gettype() const override;
};

class Roundbox: public Hitbox {
	public:
	postype r;
	Roundbox(postype r);
	hitinfotype ishit(Pos nps, Vec nv, Hitbox const& other,
								Pos ops, Vec ov) const override;
	HitboxType gettype() const override;
};
}
#endif
