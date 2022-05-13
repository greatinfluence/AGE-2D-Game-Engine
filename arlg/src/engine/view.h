#ifndef VIEW_H_
#define VIEW_H_
#include "window.h"
#include "painttype.h"
#include <list>
#include "objectob.h"

namespace umity {

class Object;

class View final: public ObjectOb {
	Window& win;
	std::list<Object*> lst;
	Vec center;
	public:
	View(Window& win);
	void regist(Object& id) override;
	void deregist(Object& id) override;
	void draw() const;
	Vec& getcenter();
};
}
#endif
