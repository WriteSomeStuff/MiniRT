/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_lights.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/28 16:08:02 by cschabra      #+#    #+#                 */
/*   Updated: 2024/03/14 14:24:22 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	check_rgb_values(t_data *data, t_vec vec)
{
	int32_t	i;

	i = 0;
	while (i < 3)
	{
		if ((uint32_t)vec.v[i] < 0 || (uint32_t)vec.v[i] > 255)
			exit_error(data, ": incorrect RGB values");
		i++;
	}
}

void	init_ambient(t_data *data, char **info)
{
	t_vec	tmp;

	check_split(data, info, 2);
	verify_info(data, info);
	data->ambient->luminosity = a_to_float(data, info[0]);
	tmp = create_vector(data, info[1]);
	check_rgb_values(data, tmp);
	data->ambient->colour = ft_pixel((uint8_t)tmp.v[0], (uint8_t)tmp.v[1], \
		(uint8_t)tmp.v[2], 0xff);
}

void	init_light(t_data *data, char **info)
{
	t_vec	tmp;

	check_split(data, info, 3);
	verify_info(data, info);
	data->light->source = create_vector(data, info[0]);
	data->light->luminosity = a_to_float(data, info[1]);
	tmp = create_vector(data, info[2]);
	check_rgb_values(data, tmp);
	data->ambient->colour = ft_pixel((uint8_t)tmp.v[0], (uint8_t)tmp.v[1], \
		(uint8_t)tmp.v[2], 0xff);
}
