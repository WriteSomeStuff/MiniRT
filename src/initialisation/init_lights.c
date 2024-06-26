/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_lights.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/28 16:08:02 by cschabra      #+#    #+#                 */
/*   Updated: 2024/06/26 18:31:00 by vvan-der      ########   odam.nl         */
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

// Luminosity is calculated and added into the colour, maybe delete variable?
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

void	obj_ambiance(t_data *d, t_cylinder *c, t_plane *p, t_sphere *s)
{
	t_input	*in;

	in = d->input;
	while (in != NULL)
	{
		if (in->token == CYLINDER)
		{
			c->amb_colour = ambient_colour(c->colour, d->ambient);
			c++;
		}
		else if (in->token == PLANE)
		{
			p->amb_colour = ambient_colour(p->colour, d->ambient);
			p++;
		}
		else if (in->token == SPHERE)
		{
			s->amb_colour = ambient_colour(s->colour, d->ambient);
			s++;
		}
		in = in->next;
	}
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
	// data->spheres[i].colour.vec3 *= 5;
	if (info[3] != NULL)
		data->spheres[i].radius = a_to_float(data, info[3]) / 2.0f;
	data->spheres[i].object = LIGHT;
	data->spheres[i].instance = object_count(data);
	check_rgb_values(data, &data->spheres[i].colour.vec3);
	rgb_to_floats(&data->spheres[i].colour);
	data->sphere_count++;
}
