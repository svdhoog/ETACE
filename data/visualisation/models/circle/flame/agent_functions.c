#include <stdio.h>
//#include <math.h>
#include "header.h"
#include "Agent_agent_header.h"

#define PI 3.1415926535
#define dx 1e-2

int set_xy(void)
{
	int t = iteration_loop;

	double s = fmod(t*dx,2*PI);

	A = ID;

	X = A + CONST_RADIUS*cos(s);

	B = RUN;

	Y = B + CONST_RADIUS*sin(s);

	printf("\nIT %d s %f ID %d CONST_RADIUS %f A %f B %f x %f y %f", t, s, ID, CONST_RADIUS, A, B, X, Y);

	return 0;
}

