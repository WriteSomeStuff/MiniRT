/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_objects.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/28 16:08:04 by cschabra      #+#    #+#                 */
/*   Updated: 2024/03/14 14:24:24 by vvan-der      ########   odam.nl         */
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
	t_vec			tmp;

	check_split(data, info, 5);
	verify_info(data, info);
	data->cyls[i].center = create_vector(data, info[0]);
	data->cyls[i].orientation = create_vector(data, info[1]);
	data->cyls[i].radius = a_to_float(data, info[2]) / 2.0f;
	data->cyls[i].height = a_to_float(data, info[3]);
	tmp = create_vector(data, info[4]);
	check_rgb_values(data, tmp);
	data->cyls[i].colour = ft_pixel((uint8_t)tmp.v[0], (uint8_t)tmp.v[1], \
		(uint8_t)tmp.v[2], 0xff);
	i++;
}

void	init_plane(t_data *data, char **info)
{
	static int32_t	i = 0;
	t_vec			tmp;

	check_split(data, info, 3);
	verify_info(data, info);
	data->planes[i].location = create_vector(data, info[0]);
	data->planes[i].orientation = create_vector(data, info[1]);
	tmp = create_vector(data, info[2]);
	check_rgb_values(data, tmp);
	data->planes[i].colour = ft_pixel((uint8_t)tmp.v[0], (uint8_t)tmp.v[1], \
		(uint8_t)tmp.v[2], 0xff);
	i++;
}

void	init_sphere(t_data *data, char **info)
{
	static int32_t	i = 0;
	t_vec			tmp;

	check_split(data, info, 3);
	verify_info(data, info);
	data->spheres[i].center = create_vector(data, info[0]);
	data->spheres[i].radius = a_to_float(data, info[1]) / 2.0f;
	tmp = create_vector(data, info[2]);
	check_rgb_values(data, tmp);
	data->spheres[i].colour = ft_pixel((uint8_t)tmp.v[0], (uint8_t)tmp.v[1], \
		(uint8_t)tmp.v[2], 0xff);
	i++;
}
