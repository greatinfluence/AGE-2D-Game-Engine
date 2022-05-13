#include "startscene.h"
#include "level.h"
#include "gameover.h"
#include "finalrush.h"
#include <cstring>
#include "credit.h"
#include "setting.h"

using namespace arlg;
int main(int argc, char* argv[]) {
	using std::unique_ptr;
	using std::make_unique;
	using umity::Gamescene;
	Gamebody gb;
	randinit();
	gb.addscene("startscene", unique_ptr<Gamescene>(
				make_unique<Startscene>(gb)));
	gb.addscene("Level1", unique_ptr<Gamescene>(
				make_unique<Level>(gb, 1)));
	gb.addscene("Level2", unique_ptr<Gamescene>(
				make_unique<Level>(gb, 2)));
	gb.addscene("Level3", unique_ptr<Gamescene>(
				make_unique<Level>(gb, 3)));
	gb.addscene("Level4", unique_ptr<Gamescene>(
				make_unique<Level>(gb, 4)));
	gb.addscene("Level5", unique_ptr<Gamescene>(
				make_unique<Level>(gb, 5)));
	gb.addscene("Finalrush", unique_ptr<Gamescene>(
				make_unique<Finalrush>(gb)));
	gb.addscene("gameover", std::move(make_unique<Gameover>(gb)));
	gb.addscene("setting", std::move(make_unique<Setting>(gb)));
	gb.addscene("Credit", std::move(make_unique<Credit>(gb)));
	bool common = true;
	for(auto i = 1; i < argc; ++ i) {
		if(strlen(argv[i]) == 1 && argv[i][0] > '0' && argv[i][0] < '7') {
			common = false;
			switch(argv[i][0]) {
				case '1':
					gb.addscene("Level1");
					break;
				case '2':
					gb.addscene("Level2");
					break;
				case '3':
					gb.addscene("Level3");
					break;
				case '4':
					gb.addscene("Level4");
					break;
				case '5':
					gb.addscene("Level5");
					break;
				default:
					gb.addscene("Finalrush");
			}
		}
		else if(string(argv[i]) == "credit") {
			gb.addscene("Credit");
			common = false;
		}
	}
	if(common) {
		gb.addscene("startscene");
	}
	gb.run();
	return 0;
}
