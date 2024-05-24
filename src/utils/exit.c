/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/24 16:32:44 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/05/24 16:33:39 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	exit_error(t_data *data, char *msg)
{
	clean_up(data);
	ft_putstr_fd("Error", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	exit_success(t_data *data)
{
	clean_up(data);
	exit(EXIT_SUCCESS);
}
