#ifndef TESTS_H
# define TESTS_H

#ifdef __cplusplus
    #define new __new__
extern "C"
{
#endif

#include "miniRT.h"

#ifdef __cplusplus
    #undef new
}
#endif

#include <iostream>
#include <iomanip>

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define RESET	"\e[m"

void	test_normalize_vector();
void	test_vector_length();
void	quat_test();
void	test_reflection_result();
void	test_combine_colours();
void	test_quadratic_equation();
void	parse_test();

#endif