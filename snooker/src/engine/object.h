#ifndef OBJECT_H_
#define OBJECT_H_
#include <memory>
#include "idrawable.h"
#include "ihittable.h"
#include "datatype.h"
#include "gamescene.h"
#include "objectob.h"
namespace umity {
using std::unique_ptr;

class Object: public IDrawable, public IHittable {
	Gamescene& gs;
	ObjectOb& vw;
	ObjectOb& hm;
	Pos ps;
	std::string name;
	std::string cls;
	bool visibility, hittability, isview;
	postype countdown;
	public:
	Object(unique_ptr<Paintable> image, unique_ptr<Hitbox> hb, Vec v, masstype m,
		Gamescene& gs, Pos ps, std::string name = "object", std::string cls = "Object");
	virtual ~Object();
	Object(Object&&) = default;
	void visiblize();
	void invisiblize();
	void hittablize();
	void unhittablize();
	void beview();
	void besolid();
	bool ifview();
	Gamescene& getgs();
	postype& getcountdown();
	virtual void move(timetype t);
	hitinfotype ishit(Object& other) const;
	virtual void accept(Object& other, Vec normal);
	virtual void onhit(Object& other, Vec normal);
	virtual void run();
	virtual void afterkill();
	std::string const& getname() const;
	std::string const& getcls() const;
	
	Pos& getpos();
	Pos const& getpos() const;
};

}
#endif
