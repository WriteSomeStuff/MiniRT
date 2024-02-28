/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_lights.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/28 16:08:02 by cschabra      #+#    #+#                 */
/*   Updated: 2024/02/28 17:47:50 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_ambient(t_data *data, char **info)
{
	check_split(data, info, 2);
	verify_info(data, info);
}

void	init_light(t_data *data, char **info)
{
	check_split(data, info, 3);
	verify_info(data, info);
}
