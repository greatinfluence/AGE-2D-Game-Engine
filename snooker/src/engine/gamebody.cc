#include "gamebody.h"
#include "gamescene.h"
#include "object.h"
namespace umity {

Gamebody::Gamebody(timetype fps): win{std::move(std::make_unique<Window>())}, gameon{true},
					fm{std::move(std::make_unique<Fpsmanager>(fps))} {}

Gamebody::~Gamebody() {}

Window& Gamebody::getwin() {return *win;}

void Gamebody::addscene(std::string const sname, unique_ptr<Gamescene> gs) {
	ss[sname] = std::move(gs);
}

void Gamebody::delscene(std::string const sname) {
	ss.erase(sname);
}

Gamescene& Gamebody::getscene(std::string const sname) { return *ss[sname]; }

void Gamebody::callscene(std::string const sname) {
	ss[sname] -> run();
}

void Gamebody::addobject(std::string const sname, unique_ptr<Object> obj) {
	ss[sname] -> addobject(std::move(obj));
}

void Gamebody::addscene(string sname) { sseq.push(sname); }

void Gamebody::gameover() { gameon = false; }

void Gamebody::run() {
	while(gameon && !sseq.empty()) {
		callscene(sseq.front());
		sseq.pop();
	}
}

Fpsmanager& Gamebody::getfm() { return *fm; }

}
