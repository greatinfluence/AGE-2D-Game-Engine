#include "controller.h"
namespace umity {
	Controller::Controller(Window& win): win{win} {}
	int Controller::getkey() { return win.getkey(); }
}
