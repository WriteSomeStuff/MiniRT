/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   alloc.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/28 14:28:45 by cschabra      #+#    #+#                 */
/*   Updated: 2024/02/28 14:31:58 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	*rt_malloc(t_data *data, size_t size)
{
	void	*alloc;

	alloc = malloc(size);
	if (alloc == NULL)
		exit_error(data, ": malloc failed");
	return (alloc);
}

void	*rt_calloc(t_data *data, size_t size)
{
	void	*p;

	p = rt_malloc(data, size);
	ft_bzero(p, size);
	return (p);
}
