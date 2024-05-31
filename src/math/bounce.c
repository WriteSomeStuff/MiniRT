/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bounce.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/26 10:55:16 by vincent       #+#    #+#                 */
/*   Updated: 2024/05/30 18:13:03 by vincent       ########   odam.nl         */
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
	ray->col->reflectivity = data->pix[y][x].reflectivity;
	ray->col->colour = data->pix[y][x].obj_clr;
	ray->origin = data->pix[y][x].location;
	// if (x == 540 && y == 540)
	// 	print_vector(ray->origin);
	ray->col->surface_norm = data->pix[y][x].surface_norm;
}

static void	bounce(t_data *data, t_ray *ray, uint32_t id)
{
	t_vec	new_dir;

	new_dir.vec3 = random_vector(data, id).vec3 * ray->col->absorption;
	new_dir.vec3 += reflect(ray->direction, ray->col->surface_norm).vec3 * ray->col->reflectivity;
	ray->direction = norm_vec(new_dir);
	if (dot(ray->direction, ray->col->surface_norm) < 0)
		ray->direction.vec3 *= -1;
	find_closest_object(data, ray->col, ray);
	draw_collision(ray->col, ray->col->absorption, ray->col->reflectivity);
}

void	trace(t_data *data, t_ray *ray, uint32_t x, uint32_t y)
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
		data->pix[y][x].pix_clr.vec3 += ray->col->colour.vec3;
		rays++;
	}
	data->pix[y][x].pix_clr.vec3 /= NUM_RAYS;
}
