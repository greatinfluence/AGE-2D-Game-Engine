#include "readbitmap.h"
#include <fstream>
namespace umity {
Bitmap readbitmap(std::string filename, bool trans) {
	std::ifstream file{filename};
	Bitmap bm;
	postype y = 0, x = 0;
	char ch = 0;
	while(~(ch = file.get())) {
		if(ch == '\n') {
			// New line
			++ y;
			x = 0;
		}
		else {
			if(ch != ' ' || !trans) {
				bm.emplace_back(y, x, ch);
			}
			++ x;
		}
	}
	return bm;
}

}
