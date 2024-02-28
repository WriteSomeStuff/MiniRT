/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_up.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 15:42:06 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/02/28 16:46:51 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	exit_error(t_data *data, char *msg)
{
	(void)data;
	// clean_up(data);
	ft_putstr_fd("Error", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	clear_list(t_input **input)
{
	t_input	*p;

	if (input == NULL)
		return ;
	while (*input)
	{
		p = (*input)->next;
	// data->info 2D array free
		free((*input)->info);
		free(*input);
		*input = p;
	}
	*input = NULL;
}

void	clean_up(t_data *data)
{
	clear_list(&data->input);
	close(data->fd);
}
