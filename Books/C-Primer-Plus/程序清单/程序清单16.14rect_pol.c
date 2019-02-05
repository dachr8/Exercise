//rect_pol.c -- Convert Cartesian coordinates to polar coordinates

#include <stdio.h>
#include <math.h>

#define RAD_TO_DEG (180/(4*atan(1)))

typedef struct polar_v {
	double magnitude, angle;
}Polar_V;

typedef struct rect_v {
	double x, y;
}Rect_V;


int main(void) {
	Rect_V input;
	Polar_V result;

	puts("Enter x and y coordinates (enter q to quit):");
	while (scanf("%lf %lf", &input.x, &input.y) == 2) {
		result.magnitude = sqrt(input.x*input.x + input.y*input.y);
		if (result.magnitude)
			result.angle = RAD_TO_DEG * atan2(input.y, input.x);
		else
			result.angle = 0.0;
		printf("magnitude = %.2f, angle = %.2f\n", result.magnitude, result.angle);
	}
	puts("Bye.");

	return 0;
}
