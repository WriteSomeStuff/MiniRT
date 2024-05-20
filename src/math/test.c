#include <stdlib.h>
#include <stdio.h>

void	increase_x(int *x)
{
	(*x)++;
}

int	main()
{
	int x = 5;
	increase_x(&x);
	printf("%d\n", x);
}
