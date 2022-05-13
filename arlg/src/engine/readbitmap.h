#ifndef READBITMAP_H_
#define READBITMAP_H_
#include "painttype.h"
#include <string>
namespace umity {
Bitmap readbitmap(std::string filename, bool trans = false);
}
#endif
