#ifndef LOGGER_H_
#define LOGGER_H_
#include <fstream>
namespace umity {

extern std::ofstream gamelogger{"gamelogger.txt", std::ios_base::app};

}
#endif
