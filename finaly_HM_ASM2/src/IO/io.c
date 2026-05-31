#include "../../include/IO/io.h"

#include <math.h>
#include <stdio.h>

void print_help(void)
{
    printf("Usage: ./integral [options]\n");
    printf("  -h, --help\n");
    printf("  -r, --root\n");
    printf("  -i, --iterations\n");
    printf("  -R, --test-root F1:F2:A:B:E:R\n");
    printf("  -I, --test-integral F:A:B:E:R\n");
}

void print_area(double area)
{
    printf("%.10lf\n", area);
}

void print_roots(double x13, double x23, double x12)
{
    printf("%.10lf %.10lf %.10lf\n", x13, x23, x12);
}

void print_iterations(int iterations)
{
    printf("%d\n", iterations);
}

void print_test_result(double result, double expected)
{
    const double abs_error = fabs(result - expected);
    const double rel_error = expected == 0.0 ? abs_error : abs_error / fabs(expected);
    printf("%.10lf %.10lf %.10lf\n", result, abs_error, rel_error);
}
