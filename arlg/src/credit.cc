#include "credit.h"
namespace arlg {

Credit::Credit(Gamebody& gb): Gamescene(gb) {}

void Credit::preparation() {
	auto content = readbitmap("pic/credit.txt", true);
	addobject(std::move(std::make_unique<Staticpic>(std::make_unique<Bm>(content),
				*this, Pos{1, 1, 9}, "credit")));
	for(auto& x: objs) {
		x -> visiblize();
		x -> hittablize();
	}
}

void Credit::logicbeforemove() {
	int key = getkey();
	if(key == -1) return;
	if(key == 's') modifcenter(getcenter() + Vec{1, 0});
	if(key == 'w') modifcenter(getcenter() + Vec{-1, 0});
	if(key == 'q') {
		getgb().gameover();
		sceneover();
	}
}

}
