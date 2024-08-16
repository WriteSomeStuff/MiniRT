/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_objects.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: soepgroente <soepgroente@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/28 16:08:04 by cschabra      #+#    #+#                 */
/*   Updated: 2024/08/16 13:05:38 by cschabra      ########   odam.nl         */
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
	data->cones[data->cone_count].object = INVALID;
	data->cyls[data->cyl_count].object = INVALID;
	data->discs[data->disc_count].object = INVALID;
	data->planes[data->plane_count].object = INVALID;
	data->spheres[data->sphere_count].object = INVALID;
}

void	init_camera(t_data *data, char **info)
{
	check_split(data, info, 3);
	verify_info(data, info);
	data->cam->viewpoint = create_vector(data, info[0]);
	data->cam->orientation = create_vector(data, info[1]);
	data->cam->orientation = normalize_vector(data->cam->orientation);
	data->cam->fov = a_to_float(data, info[2]);
	if (data->cam->fov <= 0)
		exit_error(data, ": wrong FOV");
	data->cam->fov_correction = tan(degree_to_radian(data->cam->fov) / 2);
}

void	init_cone(t_data *d, char **info)
{
	int		i;

	i = d->cone_count;
	check_split(d, info, 7);
	verify_info(d, info);
	d->cones[i].base = create_vector(d, info[0]);
	d->cones[i].orientation = normalize_vector(create_vector(d, info[1]));
	d->cones[i].height = a_to_float(d, info[2]);
	d->cones[i].radius = a_to_float(d, info[3]);
	d->cones[i].apex.vec3 = d->cones[i].base.vec3 + \
		d->cones[i].orientation.vec3 * d->cones[i].height;
	d->cones[i].angle = atan(d->cones[i].radius / d->cones[i].height);
	d->cones[i].colour = create_vector(d, info[4]);
	d->cones[i].glossiness = a_to_float(d, &info[5][2]);
	if (d->cones[i].glossiness < 0 || d->cones[i].glossiness > 1)
		exit_error(d, ": invalid glossiness value");
	d->cones[i].specular = a_to_float(d, &info[6][2]);
	if (d->cones[i].specular < 0 || d->cones[i].specular > 1)
		exit_error(d, ": invalid specular value");
	d->cones[i].object = CONE;
	d->cones[i].instance = object_count(d);
	check_rgb_values(d, &d->cones[i].colour.vec3);
	rgb_to_floats(&d->cones[i].colour);
	d->cone_count++;
}

void	init_cylinder(t_data *data, char **info)
{
	int			i;
	t_cylinder	*cyl;

	i = data->cyl_count;
	cyl = &data->cyls[i];
	check_split(data, info, 7);
	verify_info(data, info);
	cyl->center = create_vector(data, info[0]);
	cyl->orientation = normalize_vector(create_vector(data, info[1]));
	cyl->radius = a_to_float(data, info[2]) / 2.0f;
	cyl->height = a_to_float(data, info[3]);
	cyl->colour = create_vector(data, info[4]);
	cyl->glossiness = a_to_float(data, &info[5][2]);
	if (cyl->glossiness < 0 || cyl->glossiness > 1)
		exit_error(data, ": invalid glossiness value");
	cyl->specular = a_to_float(data, &info[6][2]);
	if (cyl->specular < 0 || cyl->specular > 1)
		exit_error(data, ": invalid specular value");
	cyl->object = CYLINDER;
	cyl->instance = object_count(data);
	check_rgb_values(data, &cyl->colour.vec3);
	rgb_to_floats(&cyl->colour);
	cyl->base.vec3 = cyl->center.vec3 - cyl->orientation.vec3 * cyl->height / 2;
	cyl->top.vec3 = cyl->center.vec3 + cyl->orientation.vec3 * cyl->height / 2;
	data->cyl_count++;
}

void	init_plane(t_data *data, char **info)
{
	int	i;

	i = data->plane_count;
	check_split(data, info, 5);
	verify_info(data, info);
	data->planes[i].location = create_vector(data, info[0]);
	data->planes[i].orientation = create_vector(data, info[1]);
	data->planes[i].orientation = normalize_vector(data->planes[i].orientation);
	data->planes[i].rev_norm.vec3 = data->planes[i].orientation.vec3 * -1;
	data->planes[i].colour = create_vector(data, info[2]);
	data->planes[i].glossiness = a_to_float(data, &info[3][2]);
	if (data->planes[i].glossiness < 0 || data->planes[i].glossiness > 1)
		exit_error(data, ": invalid glossiness value");
	data->planes[i].specular = a_to_float(data, &info[4][2]);
	if (data->planes[i].specular < 0 || data->planes[i].specular > 1)
		exit_error(data, ": invalid specular value");
	if (info[5] != NULL)
		data->planes[i].tex = load_texture(data, &info[5][2]);
	data->planes[i].object = PLANE;
	data->planes[i].instance = object_count(data);
	check_rgb_values(data, &data->planes[i].colour.vec3);
	rgb_to_floats(&data->planes[i].colour);
	data->plane_count++;
}
