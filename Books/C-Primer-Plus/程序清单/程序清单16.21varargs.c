//varargs.c -- Use variable number of arguments

#include <stdio.h>
#include <stdarg.h>

double sum(int lim, ...);


int main(void) {
	double s = sum(3, 1.1, 2.5, 13.3), t = sum(6, 1.1, 2.1, 13.1, 4.1, 5.1, 6.1);

	printf("return value for sum(3, 1.1, 2.5, 13.3):                %g\n", s);
	printf("return value for sum(6, 1.1, 2.1, 13.1, 4.1, 5.1, 6.1): %g\n", t);
	
	return 0;
}

double sum(int lim, ...) {
	va_list ap; //Declare an object storage parameter
	double tot = 0;

	va_start(ap, lim); //Initialize ap as a parameter list
	for (int i = 0; i < lim; ++i)
		tot += va_arg(ap, double); //Access each item in the parameter list
	va_end(ap); //Cleanup work

	return tot;
}
