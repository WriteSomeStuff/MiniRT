/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   trace.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/26 10:55:16 by vincent       #+#    #+#                 */
/*   Updated: 2024/05/31 19:29:19 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	setup(t_data *data, t_ray *ray, int32_t x, int32_t y)
{
	ray->col->glossy_bounce = is_glossy(data, y % data->num_threads, \
		data->pix[y][x].glossiness);
	ray->direction = data->pix[y][x].incoming;
	ray->col->specular = data->pix[y][x].specular;
	ray->col->colour = lerp(data->pix[y][x].obj_clr, vec(1, 1, 1), \
		ray->col->glossy_bounce);
	ray->origin = data->pix[y][x].location;
	ray->col->surface_norm = data->pix[y][x].surface_norm;
	ray->col->inside_obj = false;
	ray->col->type = INVALID;
}

static void	bounce(t_data *data, t_ray *ray, uint32_t id)
{
	t_vec	diffuse_direction;
	t_vec	specular_direction;

	diffuse_direction = random_vector(data, id, ray->col->surface_norm);
	diffuse_direction = normalize_vector(lerp(diffuse_direction, \
		ray->col->surface_norm, 0.5f));
	if (ray->col->glossy_bounce == true)
	{
		specular_direction = reflect(ray->direction, ray->col->surface_norm);
		if (dot(specular_direction, ray->col->surface_norm) < 0)
		{
			specular_direction = inverted(specular_direction);
		}
		ray->direction = normalize_vector(lerp(diffuse_direction, \
			specular_direction, ray->col->specular));
	}
	else
	{
		ray->direction = diffuse_direction;
	}
	find_closest_object(data, ray->col, ray, id);
	draw_collision(ray->col, ray->direction);
}

void	trace(t_data *data, t_ray *ray, int32_t x, int32_t y)
{
	uint32_t	bounces;
	uint32_t	rays;

	rays = 0;
	while (rays < NUM_RAYS)
	{
		setup(data, ray, x, y);
		bounces = 0;
		while (bounces < MAX_BOUNCES && sum(ray->col->colour) > THRESHHOLD && \
			ray->col->type != LIGHT)
		{
			bounce(data, ray, y % data->num_threads);
			bounces++;
			ray->origin = ray->col->location;
		}
		if (ray->col->type == LIGHT)
			data->pix[y][x].samples.vec3 += ray->col->colour.vec3;
		rays++;
	}
	data->pix[y][x].pix_clr.vec3 = (data->pix[y][x].samples.vec3 / \
		(float)(NUM_RAYS * data->iterations));
	gamma_adjust(&data->pix[y][x].pix_clr);
	data->pix[y][x].pix_clr = combine_colours(data->pix[y][x].pix_clr, \
		data->pix[y][x].ambient);
}
