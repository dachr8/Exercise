//align.c -- Use _Alignof and _Alignas
//#include <stdalign.h>
//std:c11

#include <stdio.h>


int main(void) {
	double dx, dz;
	char cx, ca, cb;
	char _Alignas(double) cz;

	printf("char alignment: %zd\n",_Alignof(char));
	printf("double alignment: %zd\n",_Alignof(double));
	printf("&dx: %p\n",&dx);
	printf("&ca: %p\n",&ca);
	printf("&cx: %p\n",&cx);
	printf("&dz: %p\n",&dz);
	printf("&cb: %p\n",&cb);
	printf("&cz: %p\n",&cz);

	return 0;
}
