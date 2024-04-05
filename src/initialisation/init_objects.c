/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_objects.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/28 16:08:04 by cschabra      #+#    #+#                 */
/*   Updated: 2024/04/05 18:32:51 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static mlx_texture_t	*load_texture(t_data *data, char *path)
{
	mlx_texture_t	*tex;

	tex = mlx_load_png(path);
	if (tex == NULL)
		exit_error(data, ": texture failed to load");
	return (tex);
}

static int16_t	object_count(t_data *data)
{
	return (data->cyl_count + data->plane_count + data->sphere_count);
}

void	init_objects(t_data *data, t_input *input)
{
	while (input != NULL)
	{
		data->f[input->token](data, input->info);
		input = input->next;
	}
	obj_ambiance(data, data->cyls, data->planes, data->spheres);
	data->cyls[data->cyl_count].object = INVALID;
	data->planes[data->plane_count].object = INVALID;
	data->spheres[data->sphere_count].object = INVALID;
}

void	init_camera(t_data *data, char **info)
{
	check_split(data, info, 3);
	verify_info(data, info);
	data->cam->viewpoint = create_vector(data, info[0]);
	data->cam->orientation = create_vector(data, info[1]);
	data->cam->fov = a_to_float(data, info[2]);
	data->cam->fov_correction = tan(degree_to_radian(data->cam->fov) / 2);
}

void	init_cylinder(t_data *data, char **info)
{
	int		i;
	t_vec	tmp;
	t_cylinder	*cyl;

	i = data->cyl_count;
	cyl = &data->cyls[i];
	check_split(data, info, 5);
	verify_info(data, info);
	data->cyls[i].center = create_vector(data, info[0]);
	tmp = create_vector(data, info[1]);
	data->cyls[i].orientation = normalize_vector(&tmp);
	cyl->base.vec3 = cyl->center.vec3 - cyl->orientation.vec3 * cyl->height / 2;
	cyl->top.vec3 = cyl->center.vec3 + cyl->orientation.vec3 * cyl->height / 2;
	data->cyls[i].radius = a_to_float(data, info[2]) / 2.0f;
	data->cyls[i].height = a_to_float(data, info[3]);
	data->cyls[i].colour = create_vector(data, info[4]);
	if (info[5] != NULL)
		data->cyls[i].tex = load_texture(data, &info[5][2]);
	data->cyls[i].object = CYLINDER;
	data->cyls[i].instance = object_count(data);
	check_rgb_values(data, &data->cyls[i].colour.vec3);
	rgb_to_floats(&data->cyls[i].colour);
	data->cyl_count++;
}

void	init_plane(t_data *data, char **info)
{
	int	i;

	i = data->plane_count;
	check_split(data, info, 3);
	verify_info(data, info);
	data->planes[i].location = create_vector(data, info[0]);
	data->planes[i].orientation = create_vector(data, info[1]);
	data->planes[i].colour = create_vector(data, info[2]);
	if (info[3] != NULL)
		data->planes[i].tex = load_texture(data, &info[3][2]);
	data->planes[i].object = PLANE;
	data->planes[i].instance = object_count(data);
	check_rgb_values(data, &data->planes[i].colour.vec3);
	rgb_to_floats(&data->planes[i].colour);
	data->planes[i].orientation = normalize_vector(&data->planes[i].orientation);
	data->plane_count++;
}

void	init_sphere(t_data *data, char **info)
{
	int	i;

	i = data->sphere_count;
	check_split(data, info, 3);
	verify_info(data, info);
	data->spheres[i].center = create_vector(data, info[0]);
	data->spheres[i].radius = a_to_float(data, info[1]) / 2.0f;
	data->spheres[i].colour = create_vector(data, info[2]);
	if (info[3] != NULL)
		data->spheres[i].tex = load_texture(data, &info[3][2]);
	data->spheres[i].object = SPHERE;
	data->spheres[i].instance = object_count(data);
	check_rgb_values(data, &data->spheres[i].colour.vec3);
	rgb_to_floats(&data->spheres[i].colour);
	data->sphere_count++;
}
