#include <ctest.h>

#include "calculate_circle.c"

CTEST(calculate, perimetr)
{
    double area_num, perimetr;

    calculate_circle(10, &area_num, &perimetr);
    const double a = 62.831853;

    ASSERT_DBL_NEAR_TOL(a, perimetr, 1e-2);
}

CTEST(calculate, area)
{
    double area_num, perimetr;

    calculate_circle(10, &area_num, &perimetr);
    const double b = 314.159265;

    ASSERT_DBL_NEAR_TOL(b, area_num, 1e-2);
}
