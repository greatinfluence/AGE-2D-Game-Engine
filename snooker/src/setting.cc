#include "setting.h"
#include "engine/readbitmap.h"
#include "staticpic.h"

namespace snooker {

Setting::Setting(Gamebody& gb): Gamescene(gb) {}

using std::move;
using std::make_unique;
void Setting::preparation() {
	Bitmap instr = readbitmap("pic/instr.txt");
	
	addobject(move(make_unique<Staticpic>(make_unique<Bm>(instr), *this, Pos{5, 5, 9},
	"option")));
	for(auto& x: objs) x -> visiblize();
	vw -> draw();
}

void Setting::logicbeforemove() {
	int key = getkey();
	if(key == -1) {
		// No key is received
		return;
	}
	if(key == 'w' || key == KEY_UP) {
		auto curfps = getgb().getfm().getfps();
		if(curfps < 1000)
			getgb().getfm().modiffps(curfps + 1);
	}
	else if(key == 's' || key == KEY_DOWN) {
		auto curfps = getgb().getfm().getfps();
		if(curfps > 1)
			getgb().getfm().modiffps(curfps - 1);
	}
	else if(key == 'q') {
		sceneover();
	}
}

void Setting::logicaftermove() {
	auto& win = getgb().getwin();
	win.printstatus(0, "Current fps: " + std::to_string((int)getgb().getfm().getfps()));
}

void Setting::afterwords() {
	auto& win = getgb().getwin();
	win.printstatus(0, "                                                                   ");
	Gamescene::afterwords();
}

}
