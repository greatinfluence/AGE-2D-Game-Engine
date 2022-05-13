#include "finalrush.h"
#include "boss.h"
namespace arlg {

Finalrush::Finalrush(Gamebody& gb): Level(gb, 6) {}

void Finalrush::changeboss() {
	bossps = objs.begin();
	while(next(bossps) != objs.end()) ++ bossps;
}

void Finalrush::preparation() {
	using std::make_unique;
	addobject(std::move(make_unique<Player>(*this,
						Pos{(postype)randint(1, Nlines - Status - 2) + 0.5f,
							(postype)randint(1, Ncols - 2) + 0.5f, 1},
							8, 8, 0.97)));
	addobject(std::move(make_unique<Bosspeace>(*this,
						Pos{(postype)randint(5, Nlines - Status - 6) + 0.5f,
							(postype)randint(8, Ncols - 9) + 0.5f, 1})));
	bossps = objs.begin();
	while(next(bossps) != objs.end()) ++ bossps;
	for(auto& x: objs) {
		x -> visiblize();
		x -> hittablize();
	}
}

void Finalrush::logicaftermove() {
	auto& win = getgb().getwin();
	win.printstatus(0, "Level 6/6");
	auto& player = static_cast<Player&>(**objs.begin());
	win.printstatus(1, "Health: " + std::to_string(player.gethp()));
	std::string hp = "";
	hptype bosshp = static_cast<IDamagable&>(**bossps).gethp();
	for(auto i = 0; i < bosshp; ++ i) hp += "*";
	for(auto i = bosshp; i < 35; ++ i) hp += " ";
	if(bosshp < 10) hp += " ";
	win.printstatus(2, "HP: " + hp + std::to_string(bosshp));
}

Pos& Finalrush::getplayerpos() {
	return (*objs.begin()) -> getpos();
}

}
