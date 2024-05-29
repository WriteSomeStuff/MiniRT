/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bounce.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/26 10:55:16 by vincent       #+#    #+#                 */
/*   Updated: 2024/05/29 12:26:45 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	sum(t_vec vector)
{
	return (vector.x + vector.y + vector.z);
}

static void	setup(t_data *data, t_ray *ray, uint32_t x, uint32_t y)
{
	ray->col->absorption = data->pix[y][x].absorption;
	ray->col->colour.vec3 = data->pix[y][x].obj_clr.vec3 * data->pix[y][x].absorption;
	ray->origin = data->pix[y][x].location;
	ray->col->surface_norm = data->pix[y][x].surface_norm;
}

static void	bounce(t_data *data, t_ray *ray, uint32_t id)
{
	ray->direction = random_vector(data, id);
	if (dot(ray->direction, ray->col->surface_norm) < 0)
		ray->direction.vec3 *= -1;
	find_closest_object(data, ray->col, ray);
	draw_collision(ray->col, ray->col->absorption);
}

void	multi_bounce(t_data *data, t_ray *ray, uint32_t x, uint32_t y)
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
		data->pix[y][x].diffuse.vec3 += ray->col->colour.vec3;
		rays++;
	}
	data->pix[y][x].diffuse.vec3 /= NUM_RAYS;
}
