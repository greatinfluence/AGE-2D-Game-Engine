#include "startscene.h"
#include "engine/readbitmap.h"
#include "staticpic.h"
#include <cassert>
namespace arlg {
Startscene::Startscene(Gamebody& gb): Gamescene(gb), option{0} {}

postype const TITLEPOS = 2;

postype const OPTIONPOS[3] = {10, 14, 18};

using std::move;
using std::make_unique;
void Startscene::preparation() {
	Bitmap title = readbitmap("pic/title.txt", true);
	Bitmap gamestart = readbitmap("pic/gamestart.txt");
	Bitmap sett = readbitmap("pic/setting.txt");
	Bitmap ext = readbitmap("pic/exit.txt");
	
	addobject(move(make_unique<Object>(make_unique<Ch>('*'),
			nullptr, Vec{0, 0}, 0, *this, Pos{OPTIONPOS[0], 20, 9}, "ptr")));
	addobject(move(make_unique<Staticpic>(make_unique<Bm>(title), *this, Pos{TITLEPOS, 5, 9},
	"title")));
	addobject(move(make_unique<Staticpic>(make_unique<Bm>(gamestart), *this, Pos{OPTIONPOS[0], 5, 9},
	"option")));
	addobject(move(make_unique<Staticpic>(make_unique<Bm>(sett), *this, Pos{OPTIONPOS[1], 5, 9},
	"option")));
	addobject(move(make_unique<Staticpic>(make_unique<Bm>(ext), *this, Pos{OPTIONPOS[2], 5, 9},
	"option")));
	option = 0;
	for(auto& x: objs) x -> visiblize();
	vw -> draw();
}

void Startscene::logicbeforemove() {
	int key = getkey();
	if(key == -1) {
		// No key is received
		return;
	}
	if(key == 'w' || key == KEY_UP) {
		if(option > 0) -- option;
	}
	else if(key == 's' || key == KEY_DOWN) {
		if(option < 2) {
			++ option;
		}
	}
	else if(key == '\n' || key == KEY_ENTER || key == 'z') {
		if(option == 2) {
			getgb().gameover();
			sceneover();
		}
		else if(option == 1) {
			getgb().addscene("setting");
			getgb().addscene("startscene");
			sceneover();
		}
		else if(option == 0) {
			getgb().addscene("Level1");
			sceneover();
		}
	}
	(*objs.begin()) -> getpos() = Pos{OPTIONPOS[option], 20, 9};
}

}
