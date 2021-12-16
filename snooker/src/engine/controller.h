#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include "window.h"
namespace umity {

class Controller {
	Window& win;
	public:
	Controller(Window& win);
	int getkey();
};
}
#endif
