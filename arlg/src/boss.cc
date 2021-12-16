#include "boss.h"
#include "engine/readbitmap.h"

namespace arlg {

using std::make_unique;

Bosspeace::Bosspeace(Abstrlevel& gs, Pos ps):
	Enemy(nullptr, make_unique<Squarebox>(3.5, 6.5), gs, ps, 20, 20) {
	auto im = make_unique<Bm>(readbitmap("pic/bosspeace.txt",true));
	im -> setdiff(Vec{-3.5, -6.5});
	getimage() = std::move(im);
	setm(10000);
	setv(Vec{1.35, 1.35});
}

void Bosspeace::afterkill() {
	auto br = make_unique<Bossrage>(static_cast<Abstrlevel&>(getgs()), getpos());
	br -> visiblize();
	br -> hittablize();
	getgs().addobject(std::move(br));
	static_cast<Finalrush&>(getgs()).changeboss();
}

Bossrage::Bossrage(Abstrlevel& gs, Pos ps):
	Enemy(nullptr, make_unique<Squarebox>(3.5, 6.5), gs, ps, 30, 30), mxcd{8}, cd{0} {
	auto im = make_unique<Bm>(readbitmap("pic/bossrage.txt", true));
	im -> setdiff(Vec{-3.5, -6.5});
	getimage() = std::move(im);
	setm(10000);
	setv(Vec{-1.35, -1.35});
}

void Bossrage::summon() {
	auto& gs = static_cast<Abstrlevel&>(getgs());
	if(judge(0.2)) {
		for(auto i = 0; i < 5; ++ i) {
			auto enemy = make_unique<Walker>(gs,
						Pos{(postype)randint(1, Nlines - Status - 2) + 0.5f,
							(postype)randint(1, Ncols - 2) + 0.5f, 1});
			enemy -> visiblize();
			enemy -> hittablize();
			gs.addobject(std::move(enemy));
		}
	}
	else if(judge(0.25)) {
		for(auto i = 0; i < 3; ++ i) {
			auto enemy = make_unique<Stalker>(gs,
						Pos{(postype)randint(1, Nlines - Status - 2) + 0.5f,
							(postype)randint(1, Ncols - 2) + 0.5f, 1},
							static_cast<Finalrush&>(gs).getplayerpos());
			enemy -> visiblize();
			enemy -> hittablize();
			gs.addobject(std::move(enemy));
		}
	}
	else if(judge(0.2)) {
		for(auto i = 0; i < 8; ++ i) {
			auto fire = make_unique<Fire>(gs,
						Pos{(postype)randint(1, Nlines - Status - 2) + 0.5f,
							(postype)randint(1, Ncols - 2) + 0.5f, 1});
			fire -> visiblize();
			fire -> hittablize();
			gs.addobject(std::move(fire));
		}
	}
	else if(judge(0.5)) {
		for(auto i = 0; i < 3; ++ i) {
			auto hd = make_unique<SnakeHead>(gs,
						Pos{(postype)randint(5, Nlines - Status - 6) + 0.5f,
							(postype)randint(5, Ncols - 6) + 0.5f, 1});
			auto bd = make_unique<SnakeBody>(gs, *hd);
			hd -> visiblize();
			hd -> hittablize();
			bd -> visiblize();
			bd -> hittablize();
			gs.addobject(std::move(hd));
			gs.addobject(std::move(bd));
		}
	}
	else {
		auto enemy = make_unique<Popup>(gs,
					Pos{(postype)randint(1, Nlines - Status - 2) + 0.5f,
						(postype)randint(1, Ncols - 2) + 0.5f, 1}, 4, 2.5, 5.2);
		enemy -> visiblize();
		enemy -> hittablize();
		gs.addobject(std::move(enemy));
	}
}

void Bossrage::move(timetype t) {
	cd += t;
	if(cd >= mxcd) {
		cd -= mxcd;
		summon();
	}
	Enemy::move(t);
}

void Bossrage::afterkill() {
	auto& gs = getgs();
	gs.getgb().addscene("Credit");
	gs.sceneover();
}

}
