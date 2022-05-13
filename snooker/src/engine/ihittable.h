#ifndef IHITTABLE_H_
#define IHITTABLE_H_
#include "datatype.h"
#include "hittype.h"
#include <memory>
namespace umity {
using std::unique_ptr;

// no hit: No hit is occured
// vertical: Hit is at the vertical direction
// horizontal: Hit is at the horizontal direction
// free: junstoppablet take two objects as mass points
enum class HitType {nohit, vertical, horizontal, free};

class IHittable {
	unique_ptr<Hitbox> hb; // hitbox
	protected:
	Vec v; // velocity
	masstype m; // mass
	Vec f; // net force
	float bounce; // the degree of bouncing
	uint16_t cBit; // the categoryBit for filtering
	uint16_t mBit; // the maskBit for filtering
	bool unstoppable; // denotes if the object is unstoppable
	public:

	IHittable(unique_ptr<Hitbox> hb, Vec v, masstype m);
	IHittable(IHittable&&) = default;
	void setv(Vec nv);
	Vec getv() const;
	void setm(float nm);
	float getm() const;
	void setf(Vec nf);
	Vec getf() const;
	void setb(float nb);
	float getb() const;
	void setcb(uint16_t ncb);
	uint16_t getcb() const;
	void setmb(uint16_t nmb);
	uint16_t getmb() const;
	bool isus() const;
	void setus(bool nus);
	void addv(Vec nv);
	void addf(Vec nf);
	void addimp(Vec np);
	unique_ptr<Hitbox>& getbox();
	unique_ptr<Hitbox> const& getbox() const;
	hitinfotype ishit(Pos nps, IHittable const& other, Pos ops) const;
};
}
#endif
