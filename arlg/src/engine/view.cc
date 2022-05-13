#include "view.h"
#include "object.h"
namespace umity {

View::View(Window& win): win{win}, center{Vec{0, 0}} {}
void View::regist(Object& id) {
	lst.push_back(&id);
}

void View::deregist(Object& id) {
	lst.remove(&id);
}

void View::draw() const {
	win.frushdepbuf();
	win.cls();
	for(auto x: lst) {
		Paintable* image = x -> getimage().get();
		auto type = image -> gettype();
		if(type == PaintableType::ch) {
			win.draw(static_cast<Ch&>(*image), x -> getpos() - center);
		}
		else if(type == PaintableType::rec) {
			win.draw(static_cast<Rec&>(*image), x -> getpos() - center);
		}
		else if(type == PaintableType::bm) {
			win.draw(static_cast<Bm&>(*image), x -> getpos() - center);
		}
		else {
			throw std::invalid_argument("Unrecongnized type of image");
		}
	}
}

Vec& View::getcenter() { return center; }

}
