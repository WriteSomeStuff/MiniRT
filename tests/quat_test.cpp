#include "tests.h"

#define PRECISION 0.001

static bool	check(t_vec vector, t_vec result)
{
	if (fabs(vector.x - result.x) < PRECISION && fabs(vector.y - result.y) < PRECISION && fabs(vector.z - result.z) < PRECISION)
		return (true);
	return (false);
}

static void	quat_result(t_vec vector, t_quat quat, t_vec result)
{
	rotate(&vector, quat);
	if (check(vector, result) == true)
		std::cout << GREEN << "[OK] ";
	else
		std::cout << RED << "[FAIL] ";
}

void	quat_test()
{
	std::cout << RESET << "Rotation test:\n";
	quat_result(vec(0, 0, 1), quat(degree_to_radian(-60), vec(1, 0, 0)), vec(0, 0.866, 0.5));
	quat_result(vec(0, 0, 1), quat(degree_to_radian(660), vec(1, 0, 0)), vec(0, 0.866, 0.5));
	quat_result(vec(0, 0, 0), quat(degree_to_radian(0), vec(0, 0, 0)), vec(0, 0, 0));
	quat_result(vec(1, 1, 1), quat(degree_to_radian(0), vec(0, 0, 0)), vec(1, 1, 1));
	quat_result(vec(1, 1, 1), quat(degree_to_radian(200), vec(0, 1, 0)), vec(-1.282, 1, -0.598));
	quat_result(vec(265, 2143, 1213), quat(degree_to_radian(200), vec(0, 1, 0)), vec(-663.888978, 2143, -1049.211811));
	quat_result(vec(0, 0, 1), quat(degree_to_radian(360), vec(1, 0, 0)), vec(0, 0, 1));
	quat_result(vec(0, 0, 1), quat(degree_to_radian(720), vec(1, 0, 0)), vec(0, 0, 1));
	quat_result(vec(0, 0, 1), quat(degree_to_radian(-180), vec(1, 0, 0)), vec(0, 0, -1));
	quat_result(vec(0, 0, 1), quat(degree_to_radian(180), vec(1, 0, 0)), vec(0, 0, -1));
	quat_result(vec(0, 0, 0), quat(degree_to_radian(10), vec(1, 0, 0)), vec(0, 0, 0));
	quat_result(vec(1, 1, 1), quat(degree_to_radian(10), vec(1, 0, 0)), vec(1, 0.811, 1.158));
	std::cout << std::endl;
}
