#include "random.h"
#include <cstdlib>
#include <ctime>
namespace arlg {

void randinit() {
	srand(time(NULL));
}

int getrand() {
	if(RAND_MAX == 32767) {
		// too small! Use the combination of two rand values
		return rand() << 15 | rand();
	}
	return rand();
}

int randint(int l, int r) {
	return l + getrand() % (r - l);
}

bool judge(float p) {
	return getrand() % 10000 <= p * 10000; 
}

}
