// #include "tests.h"

// #define PRECISION 0.0001

// static bool	is_within(t_vec a, t_vec b)
// {
// 	if (fabs(a.x - b.x) < PRECISION && fabs(a.y - b.y) < PRECISION && fabs(a.z - b.z) < PRECISION)
// 		return (true);
// 	return (false);
// }

// void	troubleshoot(t_vec vector, t_vec result)
// {
// 	if (is_within(normalize_vector(vector), result) == true)
// 		std::cout << GREEN << "[OK] ";
// 	else
// 		std::cout << RED << "[FAIL] ";
// }

// void	test_normalize_vector()
// {
// 	int x, y;

// 	troubleshoot(vec(1, 0, 0), vec(1, 0, 0));
// 	troubleshoot(vec(6, 2, 1), vec(0.937043, 0.312348, 0.156174));
// 	troubleshoot(vec(-1, 0, 100), vec(-0.0099995, 0, 0.99995));
// 	std::cout << std::endl;
// }