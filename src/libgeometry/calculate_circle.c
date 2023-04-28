#include "calculate_circle.h"

#define pi 3.1415926535

void calculate_circle(double r, double* area_num, double* perimetr)
{
    *area_num = pi * r * r;
    *perimetr = 2 * pi * r;
}
