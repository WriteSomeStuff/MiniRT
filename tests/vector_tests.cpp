#include "tests.h"

#define PRECISION 0.01

static float	diff(float a, float b)
{
	return (fabs(a - b));
}

static bool	is_within(t_vec a, t_vec b)
{
	if (fabs(a.x - b.x) < PRECISION && fabs(a.y - b.y) < PRECISION && fabs(a.z - b.z) < PRECISION)
		return (true);
	return (false);
}

static void	test_length(t_vec vector, float result)
{
	if (diff(vector_length(vec(0, 0, 0), vector), result) <= PRECISION)
		std::cout << GREEN << "[OK] ";
	else
		std::cout << RED << "[FAIL] ";
}

static void	test_normalize(t_vec vector, t_vec result)
{
	if (is_within(normalize_vector(vector), result) == true)
		std::cout << GREEN << "[OK] ";
	else
		std::cout << RED << "[FAIL] ";
}

static void	test_inv_sqrt(t_vec vector, t_vec result)
{
	t_vec	outcome;

	outcome = norm_vec(vector);
	if (is_within(outcome, result) == true)
		std::cout << GREEN << "[OK] ";
	else
	{
		std::cout << RED << "\n[FAIL]\n";
		std::cout << "expected: ";
		print_vector(result);
		std::cout << "got: ";
		print_vector(outcome);
		std::cout << std::endl;
	}
}

void	test_normalize_vector()
{
	std::cout << RESET << "Normalize vector test:" << std::endl;
	test_normalize(vec(1, 0, 0), vec(1, 0, 0));
	test_normalize(vec(0, 0, 0), vec(0, 0, 0));
	test_normalize(vec(6, 2, 1), vec(0.937043, 0.312348, 0.156174));
	test_normalize(vec(-1, 0, 100), vec(-0.0099995, 0, 0.99995));
	test_normalize(vec(4000, -7000, 9999), vec(0.311418, -0.544982, 0.778468));
	std::cout << std::endl;

	std::cout << RESET << "Inverse sqrt test:" << std::endl;
	test_inv_sqrt(vec(1, 0, 0), vec(1, 0, 0));
	test_inv_sqrt(vec(0, 0, 0), vec(0, 0, 0));
	test_inv_sqrt(vec(6, 2, 1), vec(0.937043, 0.312348, 0.156174));
	test_inv_sqrt(vec(-1, 0, 100), vec(-0.0099995, 0, 0.99995));
	test_inv_sqrt(vec(4000, -7000, 9999), vec(0.311418, -0.544982, 0.778468));
	std::cout << std::endl;
}

void	test_vector_length()
{
	std::cout << RESET << "Vector length test:" << std::endl;
	test_length(vec(0, 0, 0), 0);
	test_length(vec(1, 1, 1), 1.7320508);
	test_length(vec(0.57, 0.57, 0.57), 0.98726896);
	test_length(vec(-1, -4, 5.5), 6.8738635);
	test_length(vec(-1, 0, 100), 100.00499);
	test_length(vec(4000, -7000, 9999), 12844.454);
	std::cout << std::endl;
}