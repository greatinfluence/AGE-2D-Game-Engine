#ifndef GAMESCENE_H_
#define GAMESCENE_H_
#include "datatype.h"
#include "window.h"
#include "view.h"
#include "hitmanager.h"
#include "controller.h"
#include "gamebody.h"
#include <vector>
#include <list>
namespace umity {

class Object;

class Wall;

class Gamescene {
	Gamebody& gb;
	bool gameon;
	protected:
	unique_ptr<View> vw;
	unique_ptr<Hitmanager> hm;
	unique_ptr<Controller> cr;
	std::list<unique_ptr<Object>> objs;
	vector<unique_ptr<Wall>> walls;
	public:
	Gamescene(Gamebody& gb);
	Gamescene(Gamescene&& gs);
	virtual ~Gamescene();
	View& getvw();
	Hitmanager& gethm();
	Controller& getcr();
	Gamebody& getgb();
	void sceneover();
	void addobject(unique_ptr<Object> obj);
	void run();
	int getkey();
	virtual void preparation();
	virtual void logicbeforemove();
	virtual void logicaftermove();
	virtual void afterwords();
	void modifcenter(Vec nc);
	Vec getcenter();
};
}
#endif
