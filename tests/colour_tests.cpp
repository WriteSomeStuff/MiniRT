#include "tests.h"

#define PRECISION 0.0001

static bool	is_within(t_vec a, t_vec b)
{
	if (fabs(a.x - b.x) < PRECISION && fabs(a.y - b.y) < PRECISION && fabs(a.z - b.z) < PRECISION)
		return (true);
	return (false);
}

static void	refl_res(t_vec c1, t_vec c2, float fraction, t_vec result)
{
	if (is_within(reflection_result(c1, c2, fraction), result) == true)
		std::cout << GREEN << "[OK] ";
	else
		std::cout << RED << "\n[FAIL]\n";
}

static void	combo_clr(t_vec c1, t_vec c2, t_vec result)
{
	if (is_within(combine_colours(c1, c2), result) == true)
		std::cout << GREEN << "[OK] ";
	else
		std::cout << RED << "\n[FAIL]\n";
}

void	test_reflection_result()
{
	std::cout << RESET << "Reflection test:" << std::endl;
	refl_res(vec(1, 1, 1), vec(1, 1, 1), 0.5, vec(0.5, 0.5, 0.5));
	refl_res(vec(0, 0, 0), vec(1, 1, 1), 1, vec(0, 0, 0));
	refl_res(vec(1, 1, 1), vec(0, 1, 1), 0.5f, vec(0, 0.5, 0.5));
	std::cout << std::endl;
}

void	test_combine_colours()
{
	std::cout << RESET << "Combine colours test:" << std::endl;
	combo_clr(vec(1, 1, 1), vec(1, 1, 1), vec(1, 1, 1));
	combo_clr(vec(0.5, 0.5, 0.5), vec(1, 1, 1), vec(1, 1, 1));
	combo_clr(vec(0.5, 0.5, 0.5), vec(0.5, 0.5, 0.5), vec(0.75, 0.75, 0.75));
	combo_clr(vec(0.1, 0.1, 0.1), vec(0.1, 0.9, 0.5), vec(0.19, 0.91, 0.55));
	std::cout << std::endl;
}
