
#ifndef COMP_H
#define COMP_H

typedef double (*func_ptr)(double);

extern int total_iterations;
extern int last_root_iterations;

double root(func_ptr value_f1, func_ptr value_f2, func_ptr df_f1, func_ptr df_f2, double dot_a, double dot_b, double eps1);
double integral(func_ptr value_f, double dot_a, double dot_b, double eps2);

#endif
