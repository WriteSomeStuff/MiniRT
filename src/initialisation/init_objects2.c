/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_objects2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/28 16:08:02 by cschabra      #+#    #+#                 */
/*   Updated: 2024/08/16 13:05:56 by cschabra      ########   odam.nl         */
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
	data->ambient = create_vector(data, info[1]);
	check_rgb_values(data, &data->ambient.vec3);
	rgb_to_floats(&data->ambient);
	data->ambient.vec3 *= luminosity;
}

void	init_light(t_data *data, char **info)
{
	int		i;

	i = data->sphere_count;
	check_split(data, info, 4);
	verify_info(data, info);
	data->spheres[i].center = create_vector(data, info[0]);
	data->spheres[i].colour = create_vector(data, info[2]);
	data->spheres[i].colour.vec3 *= a_to_float(data, info[1]);
	if (info[3] != NULL)
		data->spheres[i].radius = a_to_float(data, info[3]) / 2.0f;
	data->spheres[i].object = LIGHT;
	data->spheres[i].instance = object_count(data);
	check_rgb_values(data, &data->spheres[i].colour.vec3);
	rgb_to_floats(&data->spheres[i].colour);
	data->sphere_count++;
}

void	init_disc(t_data *data, char **info)
{
	int	i;

	i = data->disc_count;
	check_split(data, info, 7);
	verify_info(data, info);
	data->discs[i].center = create_vector(data, info[0]);
	data->discs[i].orientation = create_vector(data, info[1]);
	data->discs[i].orientation = normalize_vector(data->discs[i].orientation);
	data->discs[i].rev_norm.vec3 = data->discs[i].orientation.vec3 * -1;
	data->discs[i].hole_radius = a_to_float(data, info[2]) / 2;
	data->discs[i].radius = a_to_float(data, info[3]) / 2;
	data->discs[i].colour = create_vector(data, info[4]);
	data->discs[i].glossiness = a_to_float(data, &info[5][2]);
	if (data->discs[i].glossiness < 0 || data->discs[i].glossiness > 1)
		exit_error(data, ": invalid glossiness value");
	data->discs[i].specular = a_to_float(data, &info[6][2]);
	if (data->discs[i].specular < 0 || data->discs[i].specular > 1)
		exit_error(data, ": invalid specular value");
	data->discs[i].object = DISC;
	data->discs[i].instance = object_count(data);
	check_rgb_values(data, &data->discs[i].colour.vec3);
	rgb_to_floats(&data->discs[i].colour);
	data->disc_count++;
}

void	init_sphere(t_data *data, char **info)
{
	int	i;

	i = data->sphere_count;
	check_split(data, info, 5);
	verify_info(data, info);
	data->spheres[i].orientation = vec(0, 1, 0);
	data->spheres[i].rotated = 0;
	data->spheres[i].center = create_vector(data, info[0]);
	data->spheres[i].radius = a_to_float(data, info[1]) / 2.0f;
	data->spheres[i].colour = create_vector(data, info[2]);
	data->spheres[i].glossiness = a_to_float(data, &info[3][2]);
	if (data->spheres[i].glossiness < 0 || data->spheres[i].glossiness > 1)
		exit_error(data, ": invalid glossiness value");
	data->spheres[i].specular = a_to_float(data, &info[4][2]);
	if (data->spheres[i].specular < 0 || data->spheres[i].specular > 1)
		exit_error(data, ": invalid specular value");
	if (info[5] != NULL)
		data->spheres[i].tex = load_texture(data, &info[5][2]);
	data->spheres[i].object = SPHERE;
	data->spheres[i].instance = object_count(data);
	check_rgb_values(data, &data->spheres[i].colour.vec3);
	rgb_to_floats(&data->spheres[i].colour);
	data->sphere_count++;
}
