#include "referee.h"
#include "engine/gamebody.h"
#include "startscene.h"
#include "credit.h"
#include "setting.h"

using namespace snooker;
using std::make_unique;
int main(int argc, char* argv[]) {
	Gamebody gb;
	gb.addscene("startscene", make_unique<Startscene>(gb));
	gb.addscene("gamecontent", make_unique<Referee>(gb));
	gb.addscene("setting", make_unique<Setting>(gb));
	gb.addscene("P0win", make_unique<Credit>(gb, 0));
	gb.addscene("P1win", make_unique<Credit>(gb, 1));
	gb.addscene("startscene");
	gb.run();
	return 0;
}
