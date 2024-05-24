/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/24 16:34:02 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/05/24 16:34:10 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_and_null(void **variable)
{
	free(*variable);
	*variable = NULL;
}

void	free_2d(void ***input)
{
	int		i;
	void	**array;

	if (*input == NULL)
		return ;
	array = *input;
	i = 0;
	while (array[i] != NULL)
	{
		free_and_null(&array[i]);
		i++;
	}
	free(array);
	*input = NULL;
}

void	clear_list(t_input **input)
{
	t_input	*p;

	if (input == NULL)
		return ;
	while (*input)
	{
		p = (*input)->next;
		free_2d((void ***)&(*input)->info);
		free(*input);
		*input = p;
	}
	*input = NULL;
}
