/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collisions.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 16:50:47 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/03/26 17:35:58 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


static void	cylinder(t_data *data, t_hit *col, uint32_t x, uint32_t y)
{
	(void)data;
	(void)col;
	(void)x;
	(void)y;
}

static void	plane(t_data *data, t_hit *col, uint32_t x, uint32_t y)
{
	(void)data;
	(void)col;
	(void)x;
	(void)y;	
}

static void	sphere(t_data *data, t_hit *col, uint32_t x, uint32_t y)
{
	float	dot;
	t_sphere	*sphere;
	t_vec	ambsphere;
	t_vec	light_dir;
	t_vec	result;
	t_vec	clr;
	
	sphere = (t_sphere *)col->obj;
	sphere->tex = data->textures[0];
	set_vector(&col->surface_norm, &sphere->center, &col->location);
	set_vector(&light_dir, &col->location, &data->light->source);
	dot = dot_product(&light_dir, &col->surface_norm);
	clr = sphere_texture(sphere, &col->surface_norm);
	ambsphere = reflection_result(&clr, &data->ambient->colour, 1);
	if (dot < 0)
	{
		mlx_put_pixel(data->image, x, y, percentage_to_rgba(&ambsphere));
	}
	else
	{
		result = reflection_result(&clr, &data->light->colour, dot);
		result = combine_colours(&ambsphere, &result);
		percentage_to_rgba(&result);
		mlx_put_pixel(data->image, x, y, percentage_to_rgba(&result));
	}
}

void	draw_collision(t_data *data, t_hit *col, uint32_t x, uint32_t y)
{
	if (col->type == CYLINDER)
		cylinder(data, col, x, y);
	else if (col->type == PLANE)
		plane(data, col, x, y);
	else if (col->type == SPHERE)
		sphere(data, col, x, y);
}
