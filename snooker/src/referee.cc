#include "referee.h"
#include "ball.h"
#include "whiteball.h"
#include "edge.h"
#include "pocket.h"
#include "table.h"
#include "engine/wall.h"
namespace snooker {

Referee::Referee(Gamebody& gb): Gamescene(gb), score{0, 0}, cur{0} {};

pixeltype LEN = 271, HEI = 136;

using std::make_unique;

void Referee::receiveball(string name) {
	if(name == "white") {
		// Stroke the white ball into the pocket
		auto& wb = static_cast<Whiteball&>(**objs.begin());
		wb.beview();
		wb.getpos() = Pos{68, 25, 1};
		isreplacing = true;
		score[cur] -= 4;
	}
	else if(name == "red") {
		lasred = true;
		-- nredballs;
		++ score[cur];
		getpoint = true;
	}
	else if(name == "blue") {
		if(lasred || nredballs == 0) {
			score[cur] += 5;
			getpoint = true;
		}
		else {
			score[cur] -= 4;
		}
		if(nredballs > 0) {
			auto blueball = make_unique<Ball>(*this, Pos{68, 50, 1}, "blue", 2);
			blueball -> visiblize();
			blueball -> hittablize();
			addobject(std::move(blueball));
		}
		else {
			-- ncolorballs;
		}
		lasred = false;
	}
	else if(name == "black") {
		if(nredballs > 0) {
			if(lasred) {
				score[cur] += 7;
				getpoint = true;
			}
			else {
				score[cur] -= 4;
			}
		}
		else if(ncolorballs > 0) {
			score[cur] -= 4;
		}
		else {
			score[cur] += 7;
			getpoint = true;
			if(score[0] < score[1]) {
				getgb().addscene("P1win");
				sceneover();
				return;
			}
			else if(score[0] > score[1]) {
				getgb().addscene("P0win");
				sceneover();
				return;
			}
		}
		auto blkball = make_unique<Ball>(*this, Pos{68, 254, 1}, "black", 3);
		blkball -> visiblize();
		blkball -> hittablize();
		addobject(std::move(blkball));
	}
}

void Referee::preparation() {
	for(auto& x: walls) {
		// All the walls are now views
		x -> unhittablize();
		x -> beview();
	}
	addobject(std::move(make_unique<Whiteball>(*this,
				Pos{34.5, 18.5, 3})));
	addobject(std::move(make_unique<Edge>(*this,
				Pos{34, 0, 3}, 70, 2)));
	addobject(std::move(make_unique<Edge>(*this,
				Pos{34, 136, 3}, 70, 2)));
	addobject(std::move(make_unique<Edge>(*this,
				Pos{0, 68, 3}, 2, 138)));
	addobject(std::move(make_unique<Edge>(*this,
				Pos{68, 68, 3}, 2, 138)));
	addobject(std::move(make_unique<Pocket>(*this, Pos{1, 1, 3})));
	addobject(std::move(make_unique<Pocket>(*this, Pos{67, 1, 3})));
	addobject(std::move(make_unique<Pocket>(*this, Pos{0, 68, 3})));
	addobject(std::move(make_unique<Pocket>(*this, Pos{68, 68, 3})));
	addobject(std::move(make_unique<Pocket>(*this, Pos{1, 135, 3})));
	addobject(std::move(make_unique<Pocket>(*this, Pos{67, 135, 3})));
	addobject(std::move(make_unique<Ball>(*this, Pos{34.5, 30.5, 3}, "blue", 2)));
	addobject(std::move(make_unique<Ball>(*this, Pos{22.5, 30.5, 3}, "blue", 2)));
	addobject(std::move(make_unique<Ball>(*this, Pos{46.5, 30.5, 3}, "blue", 2)));
	addobject(std::move(make_unique<Ball>(*this, Pos{34.5, 68.5, 3}, "blue", 2)));
	addobject(std::move(make_unique<Ball>(*this, Pos{34.5, 101.5, 3}, "blue", 2)));
	addobject(std::move(make_unique<Ball>(*this, Pos{34.5, 105.5, 3}, "red", 4)));
	addobject(std::move(make_unique<Ball>(*this, Pos{32.5, 108.5, 3}, "red", 4)));
	addobject(std::move(make_unique<Ball>(*this, Pos{36.5, 108.5, 3}, "red", 4)));
	addobject(std::move(make_unique<Ball>(*this, Pos{34.5, 111.5, 3}, "red", 4)));
	addobject(std::move(make_unique<Ball>(*this, Pos{31.5, 111.5, 3}, "red", 4)));
	addobject(std::move(make_unique<Ball>(*this, Pos{37.5, 111.5, 3}, "red", 4)));
	addobject(std::move(make_unique<Ball>(*this, Pos{34.5, 123.5, 3}, "black", 3)));
	for(auto& x: objs) x -> hittablize();
	addobject(std::move(make_unique<Table>(*this, Pos{34, 68, 1})));
	for(auto& x: objs) x -> visiblize();
	isreplacing = true;
	nredballs = 6;
	ncolorballs = 6;
	lasred = false;
	(**objs.begin()).beview();
	modifcenter(Vec{24, 0});
	ballmoving = false;
}

void Referee::logicbeforemove() {
	if(ballmoving) {
		bool hasmoving = false;
		for(auto& x: objs) {
			if((x -> getv()).normsq() > 1e-3) {
				// There are some ball still moving
				hasmoving = true;
				break;
			}
		}
		if(hasmoving == false) {
			ballmoving = false;
			if(!getpoint) cur ^= 1;
		}
	}
	auto x = getcr().getkey();
	auto& wb = static_cast<Whiteball&>(**objs.begin());
	auto fps = getgb().getfm().getfps();
	Pos wbpos = wb.getpos();
	Vec movement{0, 0};
	switch(x) {
		case 'q':
			wb.changeangle(- tau / 4 / fps);
			break;
		case 'e':
			wb.changeangle(tau / 4 / fps);
			break;
		case 'r':
			wb.changemag(0.5 / fps);
			break;
		case 'f':
			wb.changemag(- 0.5 / fps);
			break;
		case KEY_UP:
			if(getcenter().y > -5)
				modifcenter(getcenter() + Vec{-1, 0});
			break;
		case KEY_DOWN:
			if(getcenter().y < 60)
				modifcenter(getcenter() + Vec{1, 0});
			break;
		case KEY_LEFT:
			if(getcenter().x > -5)
				modifcenter(getcenter() + Vec{0, -1});
			break;
		case KEY_RIGHT:
			if(getcenter().x < 66)
				modifcenter(getcenter() + Vec{0, 1});
			break;
		case 'i':
			if(getcenter().y > 0)
				modifcenter(getcenter() + Vec{-5, 0});
			break;
		case 'k':
			if(getcenter().y < 55)
				modifcenter(getcenter() + Vec{5, 0});
			break;
		case 'j':
			if(getcenter().x > 0)
				modifcenter(getcenter() + Vec{0, -5});
			break;
		case 'l':
			if(getcenter().x < 61)
				modifcenter(getcenter() + Vec{0, 5});
			break;
		case 'x':
			modifcenter(Vec{wbpos.y - 10, wbpos.x - 20});
			break;
		case 'w':
			if(isreplacing) movement = Vec{-1, 0};
			break;
		case 's':
			if(isreplacing) movement = Vec{1, 0};
			break;
		case 'a':
			if(isreplacing) movement = Vec{0, -1};
			break;
		case 'd':
			if(isreplacing) movement = Vec{0, 1};
			break;
		case ' ':
			if(isreplacing) {
				if(wb.ifplace()) {
					wb.besolid();
					isreplacing = false;
				}
			}
			else if(wb.getv().normsq() < 1e-3) {
				getpoint = false;
				ballmoving = true;
				for(auto obj = objs.begin(); obj != objs.end();) {
					if((*obj) -> getcls() == "Projector")
						obj = objs.erase(obj);
					else ++ obj;
				}
				wb.behit();
			}
			break;
	}
	Pos const startps{34.5, 30.5, 1};
	if(movement.normsq() > 0.5) {
		Pos np = wb.getpos() + movement;
		if((startps - np).normsq() <= sq(12) && np.x <= startps.x) {
			wb.getpos() = np;
		}
	}
}

void Referee::logicaftermove() {
	auto& win = getgb().getwin();
	win.printstatus(0, "Player 0 score: " + std::to_string(score[0]));
	win.printstatus(1, "Player 1 score: " + std::to_string(score[1]));
	win.printstatus(2, "Current player: " + std::to_string(cur));
	if(ballmoving)       win.printstatus(2, "The balls are still moving ", 20);
	else if(isreplacing) win.printstatus(2, "Replacing the white ball   ", 20);
	else                 win.printstatus(2, "Ready to hit the white ball", 20);
}

bool Referee::ismoving() const { return ballmoving; }

}

