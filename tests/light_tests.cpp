#include "tests.h"

#define PRECISION 0.001

static bool	check(t_vec vector, t_vec result)
{
	if (fabs(vector.x - result.x) < PRECISION && fabs(vector.y - result.y) < PRECISION && fabs(vector.z - result.z) < PRECISION)
		return (true);
	return (false);
}

static void	reflect_result(t_vec in, t_vec norm, t_vec result)
{
	t_vec	res = reflect(in, norm);

	if (check(res, result) == true)
		std::cout << GREEN << "[OK] ";
	else
	{
		std::cout << RED << "[FAIL]\n";
		std::cout << "expected: ";
		print_vector(result);
		std::cout << "received: ";
		print_vector(res);
	}
}

/*	Reflect is only called when a different function has determined an object will be intersected by the ray,
	so testcases where the ray goes in the wrong direction are omitted	*/

void	reflect_test()
{
	std::cout << RESET << "Reflection test:\n";
	reflect_result(normalize_vector(vec(-1, 0, 1)), vec(1, 0, 0), normalize_vector(vec(1, 0, 1)));
	reflect_result(normalize_vector(vec(-0.1, 0, 1)), vec(1, 0, 0), normalize_vector(vec(0.1, 0, 1)));
	reflect_result(normalize_vector(vec(1, 1, -1)), vec(0, 0, 1), normalize_vector(vec(1, 1, 1)));
	reflect_result(normalize_vector(vec(-1, -1, -1)), normalize_vector(vec(1, 1, 1)), normalize_vector(vec(1, 1, 1)));
	std::cout << std::endl;
}
