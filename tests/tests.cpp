#ifdef __cplusplus
    #define new __new__
#endif

#include <assert.h>
#include "miniRT.h"
#include "libft.h"
#include "structsRT.h"
#include "vectorsRT.h"

#ifdef __cplusplus
    #undef new
#endif

#include <iostream>
#include "tests.h"

// static void	troubleshoot_func(std::string str1, std::string str2, int& x, int& y, bool outcome, int xres, int yres)
// {
// 	if (get_input(str1, str2, x, y) == outcome)
// 	{
// 		if (outcome == false || (outcome == true && x == xres && y == yres))
// 		{
// 			std::cout << GREEN << "[OK] ";
// 		}
// 	}
// 	else
// 		std::cout << RED << "[FAIL] ";
// }

// void	test_get_input()
// {
// 	int x, y;

// 	troubleshoot_func("3", "3", x, y, true, 3, 3);
// 	troubleshoot_func("2000000000", "5", x, y, true, 2000000000, 5);
// 	troubleshoot_func("Hi", "5", x, y, false, 0, 0);
// 	troubleshoot_func("123456479156132", "5", x, y, false, 0, 0);
// 	troubleshoot_func("-5", "5", x, y, false, 0, 0);
// 	troubleshoot_func("5", "what", x, y, false, 0, 0);
// 	troubleshoot_func("5", "0", x, y, false, 0, 0);
// 	std::cout << std::endl;
// }

int main()
{
	// test_get_input();
	assert(1 == 1);
	assert(1 == 2);
}
