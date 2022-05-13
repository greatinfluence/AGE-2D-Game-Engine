#include "level.h"
#include "fire.h"
#include <cassert>
namespace arlg {

Level::Level(Gamebody& gb, uint8_t lev): Abstrlevel(gb, lev) {}

void Level::preparation() {
	using std::make_unique;
	addobject(std::move(make_unique<Player>(*this,
						Pos{(postype)randint(1, Nlines - Status - 2) + 0.5f,
							(postype)randint(1, Ncols - 2) + 0.5f, 1},
							5, 5, 1.97)));
	addobject(std::move(make_unique<Exit>(*this,
						Pos{(postype)randint(1, Nlines - Status - 2) + 0.5f,
							(postype)randint(1, Ncols - 2) + 0.5f, 1})));
	for(auto i = 0; i < 7; ++ i) {
		addobject(std::move(make_unique<Fire>(*this,
						Pos{(postype)randint(1, Nlines - Status - 2) + 0.5f,
							(postype)randint(1, Ncols - 2) + 0.5f, 1})));
	}

	if(getlev() == 1) {
		for(auto i = 0; i < 6; ++ i) {
			addobject(std::move(make_unique<Walker>(*this,
						Pos{(postype)randint(1, Nlines - Status - 2) + 0.5f,
							(postype)randint(1, Ncols - 2) + 0.5f, 1})));
		}
	}
	else if(getlev() == 2) {
		for(auto i = 0; i < 4; ++ i) {
			addobject(std::move(make_unique<Walker>(*this,
						Pos{(postype)randint(1, Nlines - Status - 2) + 0.5f,
							(postype)randint(1, Ncols - 2) + 0.5f, 1})));
		}
		for(auto i = 0; i < 3; ++ i) {
			addobject(std::move(make_unique<Stalker>(*this,
						Pos{(postype)randint(1, Nlines - Status - 2) + 0.5f,
							(postype)randint(1, Ncols - 2) + 0.5f, 1},
							(*objs.begin()) -> getpos())));
		}
	}
	else if(getlev() == 3) {
		for(auto i = 0; i < 4; ++ i) {
			addobject(std::move(make_unique<Walker>(*this,
						Pos{(postype)randint(1, Nlines - Status - 2) + 0.5f,
							(postype)randint(1, Ncols - 2) + 0.5f, 1})));
		}
		for(auto i = 0; i < 4; ++ i) {
			addobject(std::move(make_unique<Popup>(*this,
						Pos{(postype)randint(1, Nlines - Status - 2) + 0.5f,
							(postype)randint(1, Ncols - 2) + 0.5f, 1}, 4, 2.5, 5.2)));
		}
	}
	else if(getlev() == 4) {
		for(auto i = 0; i < 5; ++ i)
			addobject(std::move(make_unique<Stalker>(*this,
						Pos{(postype)randint(1, Nlines - Status - 2) + 0.5f,
							(postype)randint(1, Ncols - 2) + 0.5f, 1},
							(*objs.begin()) -> getpos())));
		for(auto i = 0; i < 4; ++ i) {
			auto hd = make_unique<SnakeHead>(*this,
						Pos{(postype)randint(5, Nlines - Status - 6) + 0.5f,
							(postype)randint(5, Ncols - 6) + 0.5f, 1});
			auto bd = make_unique<SnakeBody>(*this, *hd);
			addobject(std::move(hd));
			addobject(std::move(bd));
		}
	}
	else if(getlev() == 5) {
		for(auto i = 0; i < 2; ++ i) {
			addobject(std::move(make_unique<Walker>(*this,
						Pos{(postype)randint(1, Nlines - Status - 2) + 0.5f,
							(postype)randint(1, Ncols - 2) + 0.5f, 1})));
		}
		for(auto i = 0; i < 3; ++ i) {
			addobject(std::move(make_unique<Stalker>(*this,
						Pos{(postype)randint(1, Nlines - Status - 2) + 0.5f,
							(postype)randint(1, Ncols - 2) + 0.5f, 1},
							(*objs.begin()) -> getpos())));
		}
		for(auto i = 0; i < 2; ++ i) {
			addobject(std::move(make_unique<Popup>(*this,
						Pos{(postype)randint(1, Nlines - Status - 2) + 0.5f,
							(postype)randint(1, Ncols - 2) + 0.5f, 1})));
		}
		for(auto i = 0; i < 3; ++ i) {
			auto hd = make_unique<SnakeHead>(*this,
						Pos{(postype)randint(5, Nlines - Status - 6) + 0.5f,
							(postype)randint(5, Ncols - 6) + 0.5f, 1});
			auto bd = make_unique<SnakeBody>(*this, *hd);
			addobject(std::move(hd));
			addobject(std::move(bd));
		}
	}
	for(auto& x: objs) {
		x -> hittablize();
		x -> visiblize();
	}
	getvw().draw();
}

void Level::logicbeforemove() {
	int key = getcr().getkey();
	if(key == -1) {
		// No key is received
		return;
	}
	auto& player = static_cast<Player&>(**objs.begin());
	if(key == 'w' || key == 'a' || key == 's' || key == 'd') player.shoot(key);
	else if(key == KEY_UP) player.move('w');
	else if(key == KEY_LEFT) player.move('a');
	else if(key == KEY_DOWN) player.move('s');
	else if(key == KEY_RIGHT) player.move('d');
}

void Level::logicaftermove() {
	auto& win = getgb().getwin();
	win.printstatus(0, "Level " + std::to_string(getlev()) + "/6");
	auto& player = static_cast<Player&>(**objs.begin());
	win.printstatus(1, "Health: " + std::to_string(player.gethp()));
}

}
