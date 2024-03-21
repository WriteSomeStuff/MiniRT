/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_lights.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/28 16:08:02 by cschabra      #+#    #+#                 */
/*   Updated: 2024/03/21 15:52:48 by vvan-der      ########   odam.nl         */
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
	float	luminosity;

	check_split(data, info, 2);
	verify_info(data, info);
	luminosity = a_to_float(data, info[0]);
	data->ambient->colour = create_vector(data, info[1]);
	check_rgb_values(data, &data->ambient->colour.vec3);
	rgb_to_floats(&data->ambient->colour);
	data->ambient->colour.vec3 *= luminosity;
}

void	init_light(t_data *data, char **info)
{
	float	luminosity;

	check_split(data, info, 3);
	verify_info(data, info);
	data->light->source = create_vector(data, info[0]);
	luminosity = a_to_float(data, info[1]);
	data->light->colour = create_vector(data, info[2]);
	check_rgb_values(data, &data->light->colour.vec3);
	rgb_to_floats(&data->light->colour);
	data->light->colour.vec3 *= luminosity;
}
