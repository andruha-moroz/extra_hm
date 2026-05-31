#include "../../include/Common/common.h"
#include "../../include/ComputationalModule/comp.h"
#include <math.h>

// Total number of iterations spent by all root() calls.
int total_iterations = 0;
// Number of iterations spent by the last root() call.
int last_root_iterations = 0;

double root(func_ptr v_f1, func_ptr v_f2, func_ptr d_f1, func_ptr d_f2, double dot_a, double dot_b, double eps1) {
    const int MAX_ITERATIONS = 1000;
    last_root_iterations = 0;

    
    soft_assert(v_f1 == NULL, "v_f1 is NULL", -1);
    soft_assert(v_f2 == NULL, "v_f2 is NULL", -1);
    soft_assert(d_f1 == NULL, "d_f1 is NULL", -1);
    soft_assert(d_f2 == NULL, "d_f2 is NULL", -1);
    double x_curr = (dot_a + dot_b) / 2.0;
    double x_next;

    while (1) {
        soft_assert(last_root_iterations > MAX_ITERATIONS, "Maximum number of iterations exceeded", NAN);
        last_root_iterations++;
        total_iterations++;

        double res_F = v_f1(x_curr) - v_f2(x_curr);
        double df_F = d_f1(x_curr) - d_f2(x_curr);

        soft_assert(fabs(df_F) < 1e-12, "df_F Almost zero", NAN);

        x_next = x_curr - res_F / df_F;

        if (fabs(x_next - x_curr) < eps1) {
            return x_next;
        }
        soft_assert(x_next < dot_a - 1.0 || x_next > dot_b + 1.0, "Value exceeded the limits", NAN);

        x_curr = x_next;
    }
}

double simpson(func_ptr value_f, double dot_a, double dot_b, int num) {
    double step_h = (dot_b - dot_a) / num;
    double sum = value_f(dot_a) + value_f(dot_b);

    for (int idx = 1; idx < num; idx++) {
        double dot_x = dot_a + idx * step_h;
        if (idx % 2 == 0) sum += 2.0 * value_f(dot_x);
        else              sum += 4.0 * value_f(dot_x);
    }
    return sum * (step_h / 3.0);
}

double integral(func_ptr value_f, double dot_a, double dot_b, double eps2) {
    soft_assert(value_f == NULL, "value_f is NULL pointer", NAN);

    int start_num = 4;
    double i_old = simpson(value_f, dot_a, dot_b, start_num);
    double i_new = simpson(value_f, dot_a, dot_b, start_num * 2);

    while (fabs(i_new - i_old) / 15.0 > eps2) { 
        start_num *= 2;
        soft_assert(start_num > 100000, "Integral did not converge", NAN);
        i_old = i_new;
        i_new = simpson(value_f, dot_a, dot_b, start_num * 2);
    }
    return i_new;
}
