#include "../../include/Runtime/rt.h"

#include "../../include/Common/common.h"
#include "../../include/ComputationalModule/comp.h"
#include "../../include/ComputationalModule/functions.h"
#include "../../include/IO/io.h"

#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Roots {
    double x13;
    double x23;
    double x12;
} Roots;

static double test_f1(double x)
{
    return x;
}

static double test_df1(double x)
{
    (void)x;
    return 1.0;
}

static double test_f2(double x)
{
    (void)x;
    return 2.0;
}

static double test_df2(double x)
{
    (void)x;
    return 0.0;
}

static double test_f3(double x)
{
    return x * x;
}

static double test_df3(double x)
{
    return 2.0 * x;
}

static func_ptr get_test_value_func(int func_id)
{
    if (func_id == 1) {
        return test_f1;
    }
    if (func_id == 2) {
        return test_f2;
    }
    if (func_id == 3) {
        return test_f3;
    }
    return NULL;
}

static func_ptr get_test_derivative_func(int func_id)
{
    if (func_id == 1) {
        return test_df1;
    }
    if (func_id == 2) {
        return test_df2;
    }
    if (func_id == 3) {
        return test_df3;
    }
    return NULL;
}

static Roots calculate_roots(double eps_root)
{
    Roots roots;

    roots.x13 = root(value_f1, value_f3, df_f1, df_f3, -2.0, -1.0, eps_root);
    roots.x23 = root(value_f2, value_f3, df_f2, df_f3, 0.0, 1.0, eps_root);
    roots.x12 = root(value_f1, value_f2, df_f1, df_f2, 1.0, 2.0, eps_root);

    return roots;
}

static double calculate_area(const Roots* roots, double eps_integral)
{
    double area = 0.0;

    area += integral(value_f1, roots->x13, roots->x23, eps_integral);
    area -= integral(value_f3, roots->x13, roots->x23, eps_integral);

    area += integral(value_f1, roots->x23, roots->x12, eps_integral);
    area -= integral(value_f2, roots->x23, roots->x12, eps_integral);

    return area;
}

static int handle_test_root(const char* argument)
{
    int func_id1 = 0;
    int func_id2 = 0;
    double dot_a = 0.0;
    double dot_b = 0.0;
    double eps = 0.0;
    double expected = 0.0;

    soft_assert(sscanf(argument, "%d:%d:%lf:%lf:%lf:%lf",
               &func_id1, &func_id2, &dot_a, &dot_b, &eps, &expected) != 6, "problem with sacnf", -1);

    func_ptr f1 = get_test_value_func(func_id1);
    func_ptr f2 = get_test_value_func(func_id2);
    func_ptr df1 = get_test_derivative_func(func_id1);
    func_ptr df2 = get_test_derivative_func(func_id2);

    soft_assert(f1 == NULL, "f1 is NULL ptr", -1);
    soft_assert(f2 == NULL, "f2 is NULL ptr", -1);
    soft_assert(df1 == NULL, "df1 is NULL ptr", -1);
    soft_assert(df2 == NULL, "df2 is NULL ptr", -1);

    
    double result = root(f1, f2, df1, df2, dot_a, dot_b, eps);
    print_test_result(result, expected);
    return 0;
}

static int handle_test_integral(const char* argument)
{
    int func_id = 0;
    double dot_a = 0.0;
    double dot_b = 0.0;
    double eps = 0.0;
    double expected = 0.0;

    soft_assert(sscanf(argument, "%d:%lf:%lf:%lf:%lf",
               &func_id, &dot_a, &dot_b, &eps, &expected) != 5, "Problem with scanf", -1);

    func_ptr value_f = get_test_value_func(func_id);

    soft_assert(value_f == NULL, "value_f is NULL", -1);

    double result = integral(value_f, dot_a, dot_b, eps);
    print_test_result(result, expected);
    return 0;
}

int run_program(int argc, char** argv)
{
    const double eps_root = 1e-7;
    const double eps_integral = 1e-6;

    static const struct option long_options[] = {
        {"help", no_argument, NULL, 'h'},
        {"root", no_argument, NULL, 'r'},
        {"iterations", no_argument, NULL, 'i'},
        {"test-root", required_argument, NULL, 'R'},
        {"test-integral", required_argument, NULL, 'I'},
        {NULL, 0, NULL, 0}
    };

    if (argc == 1) {
        Roots roots = calculate_roots(eps_root);
        double area = calculate_area(&roots, eps_integral);
        print_area(area);
        return 0;
    }

    int option = 0;
    while ((option = getopt_long(argc, argv, "hriR:I:", long_options, NULL)) != -1) {
        if (option == 'h') {
            print_help();
            return 0;
        }

        if (option == 'r') {
            Roots roots = calculate_roots(eps_root);
            print_roots(roots.x13, roots.x23, roots.x12);
            return 0;
        }

        if (option == 'i') {
            total_iterations = 0;
            (void)calculate_roots(eps_root);
            print_iterations(total_iterations);
            return 0;
        }

        if (option == 'R') {
            return handle_test_root(optarg);
        }

        if (option == 'I') {
            return handle_test_integral(optarg);
        }

        print_help();
        return 1;
    }

    print_help();
    return 1;
}
