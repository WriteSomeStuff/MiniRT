#include "tests.h"

#define PRECISION 0.001

static float	diff(float a, float b)
{
	return (fabs(a - b));
}

static void	quadrats(t_vec abc, float res1, float res2, bool hit)
{
	float	r1 = 0;
	float	r2 = 0;
	bool	quad;

	quad = quadratic_equation(&abc, &r1, &r2);
	if (diff(r1, res1) < PRECISION && diff(r2, res2) < PRECISION)
		std::cout << GREEN << "[OK] ";
	else
	{
		std::cout << RED << "\n[FAIL]\n";
		std::cout << RESET << "expected: " << res1 << ", " << res2 << ", " << hit;
		std::cout << "\nreceived: " << r1 << ", " << r2 << ", " << quad << std::endl;
	}
}

void	test_quadratic_equation()
{
	std::cout << RESET << "Quadratic equation test:\n";
	quadrats(vec(-10, 50, 50), -0.854102, 5.8541, true);
	quadrats(vec(10, 5, 5), 0, 0, false);
	quadrats(vec(0, 50, 50), 0, 0, false);
	quadrats(vec(100, 50, 50), 0, 0, false);
	quadrats(vec(2, -7, 2), 0.313859, 3.18614, true);
	quadrats(vec(4, 4, -4), -1.61803, 0.618034, true);
	std::cout << std::endl;
}
