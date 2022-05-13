#ifndef EXIT_H_
#define EXIT_H_
#include "engine/object.h"
#include "abstrlevel.h"
#include "player.h"
namespace arlg {

class Exit: public Object {
	bool activated;
	public:
	Exit(Gamescene& gs, Pos ps);
	void accept(Object& other, Vec normal) override;
	void onhit(Player& other, Vec normal);
	void run() override;
};

}
#endif
