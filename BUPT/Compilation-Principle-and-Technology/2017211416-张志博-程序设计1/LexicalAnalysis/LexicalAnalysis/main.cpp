#include <iostream>
#include "work.h"


using namespace std;


int main(int argc, char* argv[]) {
	if (argc == 3) {
		init(argv[1], argv[2]);
		work(argv[2]);
		return 0;
	} else
		return 1;
}
