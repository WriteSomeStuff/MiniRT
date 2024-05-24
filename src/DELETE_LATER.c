/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   DELETE_LATER.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/24 16:40:10 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/05/24 16:40:28 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_vector(t_vec vector)
{
	printf("%lf %lf %lf\n", vector.x, vector.y, vector.z);
}

void	print_2d_charray(char **array)
{
	int	i;

	i = 0;
	printf("args: ");
	if (array == NULL)
	{
		printf("%p\n", array);
		return ;
	}
	printf("\n");
	while (array[i] != NULL)
	{
		printf("String [%d]: %s\n", i, array[i]);
		i++;
	}
	printf("String [%d]: %s\n", i, array[i]);
}
