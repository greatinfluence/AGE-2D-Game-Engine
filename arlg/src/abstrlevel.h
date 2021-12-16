#ifndef ABSTRLEVEL_H_
#define ABSTRLEVEL_H_
#include "engine/gamescene.h"
namespace arlg {

using namespace umity;

class Abstrlevel: public Gamescene {
	uint8_t lev; // The level;
	uint8_t nenemy; // The number of enemies
	public:
	Abstrlevel(Gamebody& gb, uint8_t lev);
	uint8_t getlev();
	uint8_t& getnene();
};

}
#endif
