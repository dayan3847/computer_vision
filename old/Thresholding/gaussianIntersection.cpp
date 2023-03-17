#include <math.h>

int gaussianIntersection(double m1, double s1, double m2, double s2, double &x1, double &x2)
{
	double s1s, s2s, A, B, C, D;

	s1s = s1*s1;
	s2s = s2*s2;
	A = s1s - s2s;
	B = 2*(s2s*m1-s1s*m2);
	C = s1s*m2*m2 - s2s*m1*m1 -2 * s1s * s2s * log (s1/s2);
	D = B*B - 4 * A * C;
	if (D == 0)
	{
		x1 = x2 = - B /(2 * A);
		return 0;
	}
	if (D<0)
	{
		x1 = x2 = 0;
		return -1;
	}
	x1 = (-B + sqrt(D))/(2*A);
	x2 = (-B - sqrt(D))/(2*A);
	return 0;
}
