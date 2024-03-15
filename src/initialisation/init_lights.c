/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_lights.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/28 16:08:02 by cschabra      #+#    #+#                 */
/*   Updated: 2024/03/15 17:47:32 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	check_rgb_values(t_data *data, const t_vec3 *vec)
{
	int32_t	i;

	i = 0;
	while (i < 3)
	{
		if ((int32_t)(*vec)[i] < 0 || (int32_t)(*vec)[i] > 255)
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
	check_rgb_values(data, &tmp.vec3);
	data->ambient->colour = ft_pixel((uint8_t)tmp.x, (uint8_t)tmp.y, \
		(uint8_t)tmp.z, 0xff);
}

void	init_light(t_data *data, char **info)
{
	t_vec	tmp;

	check_split(data, info, 3);
	verify_info(data, info);
	data->light->source = create_vector(data, info[0]);
	data->light->luminosity = a_to_float(data, info[1]);
	tmp = create_vector(data, info[2]);
	check_rgb_values(data, &tmp.vec3);
	data->ambient->colour = ft_pixel((uint8_t)tmp.x, (uint8_t)tmp.y, \
		(uint8_t)tmp.z, 0xff);
}
