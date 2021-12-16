#ifndef GAMEBODY_H_
#define GAMEBODY_H_
#include "window.h"
#include "fps.h"
#include <map>
#include <memory>
#include <queue>
namespace umity {

class Gamescene;
class Object;

using std::unique_ptr;
using std::string;

class Gamebody {
	unique_ptr<Window> win;
	std::map<string, unique_ptr<Gamescene>> ss;
	bool gameon;
	std::queue<string> sseq;
	unique_ptr<Fpsmanager> fm;
	public:
	Gamebody(timetype fps = 2);
	virtual ~Gamebody();
	Window& getwin();
	void addscene(string const sname, unique_ptr<Gamescene> gs);
	void delscene(string const sname);
	Gamescene& getscene(string const sname);
	void callscene(string const sname);
	void addobject(string const sname, unique_ptr<Object> obj);
	void addscene(string sname);
	void gameover();
	void run();
	Fpsmanager& getfm();
};
}
#endif
