/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collisions.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 16:50:47 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/06/13 12:35:44 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	get_light(t_data *data, t_hit *col, t_light *lights)
{
	t_vec	colour;
	t_vec	tmp;
	t_ray	to_light;
	t_hit	light_col;
	float	distance;

	to_light.origin = col->location;
	to_light.col = &light_col;
	colour = vec(0, 0, 0);
	while (lights != NULL)
	{
		ft_bzero(&to_light.col, sizeof(t_hit));
		to_light.direction.vec3 = lights->location.vec3 - col->location.vec3;
		distance = vector_length(col->location, lights->location);
		to_light.direction = norm_vec(to_light.direction);
		find_closest_object(data, &light_col, &to_light);
		if (distance < light_col.distance)
		{
			tmp.vec3 = lights->colour.vec3 * dot(col->surface_norm, to_light.direction) \
				/ (float)pow(col->total_traveled + distance, 2);
			combine_colours(colour, tmp);
		}
		lights++;
	}
	return (colour);
}

static t_vec	cylinder(t_hit *col)
{
	t_cylinder	*cyl;
	float		product;
	t_vec		to_center;
	t_vec		to_new;

	cyl = (t_cylinder *)col->obj;
	if (col->caps == false)
	{
		to_center.vec3 = col->location.vec3 - cyl->center.vec3;
		product = dot(to_center, cyl->orientation);
		to_new.vec3 = cyl->center.vec3 + product * cyl->orientation.vec3;
		set_vector(&col->surface_norm, &to_new, &col->location);
	}
	if (col->inside_obj == true)
		col->surface_norm.vec3 *= -1;
	return (cylinder_texture(cyl, &col->location));
}

static t_vec	plane(t_hit *col)
{
	t_plane	*plane;

	plane = (t_plane *)col->obj;
	col->obj_num = plane->instance;
	return (plane_texture(plane, col->location));
}

static t_vec	sphere(t_hit *col)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)col->obj;
	set_vector(&col->surface_norm, &sphere->center, &col->location);
	col->obj_num = sphere->instance;
	if (col->inside_obj == true)
		col->surface_norm.vec3 *= -1;
	return (sphere_texture(sphere, col->surface_norm));
}

void	draw_collision(t_data *data, t_hit *col)
{
	static t_vec	(*ptr[4])(t_hit *) = {&cylinder, &plane, &sphere, &sphere};
	t_vec	colour;

	if (col->hit == false)
	{
		col->colour = vec(0, 0, 0);
		return ;
	}
	colour = get_light(data, col, data->lights);
	colour = reflection_result(colour, col->colour, 1);
	col->colour = combine_colours(colour, ptr[col->type](col));
	col->location.vec3 += OFFSET * col->surface_norm.vec3;
}
