#include "gamescene.h"
#include "wall.h"
#include <utility>
#include <thread>
#include <cassert>
#include <chrono>
#include <ratio>
namespace umity {

Gamescene::Gamescene(Gamebody& gb): gb{gb}, gameon{true},
									vw{std::move(std::make_unique<View>(gb.getwin()))},
									hm{std::move(std::make_unique<Hitmanager>())},
									cr{std::move(std::make_unique<Controller>(gb.getwin()))} {}

Gamescene::Gamescene(Gamescene&& gs): gb{gs.gb}, gameon{gs.gameon},
										vw{std::move(gs.vw)}, hm{std::move(gs.hm)},
										cr{std::move(gs.cr)},
											objs{std::move(gs.objs)},
												walls{std::move(gs.walls)} {}

Gamescene::~Gamescene() {}

View& Gamescene::getvw() { return *vw;}
Hitmanager& Gamescene::gethm() { return *hm; }
Controller& Gamescene::getcr() { return *cr; }
Gamebody& Gamescene::getgb() { return gb; }

void Gamescene::addobject(unique_ptr<Object> obj) {
	objs.emplace_back(std::move(obj));
}

void Gamescene::preparation() {}

void Gamescene::logicbeforemove() {}

void Gamescene::logicaftermove() {}

void Gamescene::afterwords() {
	objs.clear();
	walls.clear();
}

void Gamescene::run() {
	auto& fm = getgb().getfm();
	using namespace std::chrono;
	// add left wall
	walls.emplace_back(std::move(std::make_unique<Wall>(Wall{
								((postype)Nlines - Status) / 2, 0.5,
								*this, Pos{((postype)Nlines - Status) / 2, 0.5}
											+ getcenter()})));
	// add right wall
	walls.emplace_back(std::move(std::make_unique<Wall>(Wall{
								((postype)Nlines - Status) / 2, 0.5,
								*this, Pos{((postype)Nlines - Status) / 2, 
												((postype)Ncols - 0.5)}
											+ getcenter()})));
	// add top wall
	walls.emplace_back(std::move(std::make_unique<Wall>(Wall{
								0.5, ((postype)Ncols - 1) / 2,
								*this, Pos{0.5, ((postype)Ncols - 1) / 2}
											+ getcenter()})));
	// add bottom wall
	walls.emplace_back(std::move(std::make_unique<Wall>(Wall{
								0.5, ((postype)Ncols - 1) / 2,
								*this, Pos{(postype)Nlines - Status - 0.5,
												((postype)Ncols - 1) / 2}
											+ getcenter()})));
	for(auto& x: walls) x -> hittablize();
	gameon = true;
	preparation();
	while(gameon) {
		steady_clock::time_point t1 = steady_clock::now();
		logicbeforemove();
		if(!gameon) break;
		for(auto obj = objs.begin(); obj != objs.end();) {
			(*obj) -> run();
			auto& countdown = (*obj) -> getcountdown();
			if(countdown >= 0) {
				++ countdown;
			}
			if(countdown >= 5) {
				(*obj) -> afterkill();
				obj = objs.erase(obj);
			}
			else ++ obj;
		}
		if(!gameon) break;
		for(auto obj = objs.begin(); obj != objs.end(); ++ obj) {
			(*obj) -> move(fm.gettimediff());
		}
		if(!gameon) break;
		hm -> detecthit();
		if(!gameon) break;
		logicaftermove();
		if(!gameon) break;
		vw -> draw();
		gb.getwin().refresh();
		steady_clock::time_point t2 = steady_clock::now();
		uint32_t time_span = duration_cast
					<duration<timetype, std::milli>>(t2 - t1).count();
		
		if(fm.getmtdiff() > time_span) {
			std::this_thread::sleep_for(
				std::chrono::milliseconds(fm.getmtdiff() - time_span));
		}
	}
	afterwords();
}

int Gamescene::getkey() { return getcr().getkey(); }

void Gamescene::sceneover() { gameon = false; }

void Gamescene::modifcenter(Vec nc) {
	auto diff = nc - vw -> getcenter();
	vw -> getcenter() = nc;
	if(!walls.empty()) {
		for(auto& x: walls) x -> getpos() += diff;
	}
}

Vec Gamescene::getcenter() { return vw -> getcenter(); }

}
