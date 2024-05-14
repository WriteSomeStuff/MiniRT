#include "tests.h"

#define PRECISION 0.01

static float	diff(float a, float b)
{
	return (fabs(a - b));
}

static bool	check(t_vec vector, t_vec result)
{
	if (fabs(vector.x - result.x) < PRECISION && fabs(vector.y - result.y) < PRECISION && fabs(vector.z - result.z) < PRECISION)
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
	if (check(normalize_vector(vector), result) == true)
		std::cout << GREEN << "[OK] ";
	else
		std::cout << RED << "[FAIL] ";
}

static void	test_inv_sqrt(t_vec vector, t_vec result)
{
	t_vec	outcome;

	outcome = norm_vec(vector);
	if (check(outcome, result) == true)
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

static void	check_translated(t_vec moved, t_vec expected)
{
	if (check(moved, expected) == true)
		std::cout << GREEN << "[OK] ";
	else
	{
		std::cout << RED << "[FAIL]\n";
		std::cout << "expected: ";
		print_vector(expected);
		std::cout << "received: ";
		print_vector(moved);
	}
}

void	rotate_all_test()
{
	t_data	d1;
	t_data	d2;
	char	str1[] = "tests/scenes/cam1.rt";
	char	str2[] = "tests/scenes/cam1_norm.rt";

	ft_bzero(&d1, sizeof(t_data));
	ft_bzero(&d2, sizeof(t_data));
	std::cout << RESET << "Normalize scene test:\n";
	read_file(&d1, str1);
	read_file(&d2, str2);
	normalize_scene(&d1);
	check_translated(d1.cyls[0].center, d2.cyls[0].center);
	check_translated(d1.cyls[0].base, d2.cyls[0].base);
	check_translated(d1.cyls[0].top, d2.cyls[0].top);
	check_translated(d1.cyls[0].orientation, d2.cyls[0].orientation);
	// check_translated(d1.light->source, d2.light->source);
	check_translated(d1.planes[0].location, d2.planes[0].location);
	check_translated(d1.planes[0].orientation, d2.planes[0].orientation);
	check_translated(d1.spheres[0].center, d2.spheres[0].center);
	std::cout << std::endl;
}
