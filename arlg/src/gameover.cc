#include "gameover.h"
#include "engine/readbitmap.h"
#include "staticpic.h"
namespace arlg {

Gameover::Gameover(Gamebody& gb): Gamescene(gb) {}

void Gameover::preparation() {
	using std::make_unique;
	Bitmap gameover = readbitmap("pic/gameover.txt");
	addobject(std::move(make_unique<Staticpic>(make_unique<Bm>(gameover), *this,
						Pos{2, 5, 9}, "gameover")));
	(*objs.begin()) -> visiblize();
	vw -> draw();
}

void Gameover::logicbeforemove() {
	if(getkey() != ERR) {
		sceneover();
		getgb().gameover();
	}
}

}
