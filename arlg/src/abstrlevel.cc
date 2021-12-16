#include "abstrlevel.h"
namespace arlg {

Abstrlevel::Abstrlevel(Gamebody& gb, uint8_t lev): Gamescene(gb), lev{lev}, nenemy{0} {}

uint8_t Abstrlevel::getlev() { return lev; }

uint8_t& Abstrlevel::getnene() { return nenemy; }

}
