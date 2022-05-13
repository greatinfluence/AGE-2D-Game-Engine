#ifndef SETTING_H_
#define SETTING_H_
#include "engine/gamescene.h"

namespace snooker {

using namespace umity;

class Setting: public Gamescene {
	public:
	Setting(Gamebody& gb);
	void preparation() override;
	void logicbeforemove() override;
	void logicaftermove() override;
	void afterwords() override;
};

}

#endif
