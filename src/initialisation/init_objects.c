/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_objects.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/28 16:08:04 by cschabra      #+#    #+#                 */
/*   Updated: 2024/03/21 15:37:21 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_objects(t_data *data, t_input *input)
{
	while (input != NULL)
	{
		data->f[input->token](data, input->info);
		input = input->next;
	}
}

void	init_camera(t_data *data, char **info)
{
	check_split(data, info, 3);
	verify_info(data, info);
	data->cam->viewpoint = create_vector(data, info[0]);
	data->cam->orientation = create_vector(data, info[1]);
	data->cam->fov = (uint32_t)a_to_float(data, info[2]);
}

void	init_cylinder(t_data *data, char **info)
{
	static int32_t	i = 0;

	check_split(data, info, 5);
	verify_info(data, info);
	data->cyls[i].center = create_vector(data, info[0]);
	data->cyls[i].orientation = create_vector(data, info[1]);
	data->cyls[i].radius = a_to_float(data, info[2]) / 2.0f;
	data->cyls[i].height = a_to_float(data, info[3]);
	data->cyls[i].colour = create_vector(data, info[4]);
	check_rgb_values(data, &data->cyls[i].colour.vec3);
	rgb_to_floats(&data->cyls[i].colour);
	i++;
}

void	init_plane(t_data *data, char **info)
{
	static int32_t	i = 0;

	check_split(data, info, 3);
	verify_info(data, info);
	data->planes[i].location = create_vector(data, info[0]);
	data->planes[i].orientation = create_vector(data, info[1]);
	data->planes[i].colour = create_vector(data, info[2]);
	check_rgb_values(data, &data->planes[i].colour.vec3);
	rgb_to_floats(&data->planes[i].colour);
	i++;
}

void	init_sphere(t_data *data, char **info)
{
	static int32_t	i = 0;

	check_split(data, info, 3);
	verify_info(data, info);
	data->spheres[i].center = create_vector(data, info[0]);
	data->spheres[i].radius = a_to_float(data, info[1]) / 2.0f;
	data->spheres[i].colour = create_vector(data, info[2]);
	check_rgb_values(data, &data->spheres[i].colour.vec3);
	rgb_to_floats(&data->spheres[i].colour);
	i++;
}
