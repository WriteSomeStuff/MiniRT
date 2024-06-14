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

float	sum(t_vec vector)
{
	return (vector.x + vector.y + vector.z);
}

static void	clamp(t_vec *colour)
{
	// colour->vec3 *= 4;
	colour->x = pow(colour->x, 1 / 2.2);
	colour->y = pow(colour->y, 1 / 2.2);
	colour->z = pow(colour->z, 1 / 2.2);
	if (colour->x > 1.0f)
	{
		colour->vec3 /= colour->x;
	}
	if (colour->y > 1.0f)
	{
		colour->vec3 /= colour->y;
	}
	if (colour->z > 1.0f)
	{
		colour->vec3 /= colour->z;
	}
}

static void	setup(t_data *data, t_ray *ray, uint32_t x, uint32_t y)
{
	ray->col->absorption = data->pix[y][x].absorption;
	ray->col->reflectivity = data->pix[y][x].reflectivity;
	ray->col->colour = data->pix[y][x].obj_clr;
	ray->origin = data->pix[y][x].location;
	ray->col->surface_norm = data->pix[y][x].surface_norm;
	ray->col->type = INVALID;
}

static void	bounce(t_data *data, t_ray *ray, uint32_t id)
{
	ray->direction = random_vector(data, id);
	// print_vector(new_dir);
	ray->direction.vec3 += ray->col->surface_norm.vec3;
	ray->direction = norm_vec(ray->direction);
	// new_dir.vec3 *= ray->col->absorption;
	// new_dir.vec3 += reflect(ray->direction, ray->col->surface_norm).vec3 * ray->col->reflectivity;
	// ray->direction = norm_vec(new_dir);
	if (dot(ray->direction, ray->col->surface_norm) < 0)
		ray->direction.vec3 *= -1;
	find_closest_object(data, ray->col, ray);
	draw_collision(ray->col);
}

// static void	specular()
// {

// }

void	trace(t_data *data, t_ray *ray, uint32_t x, uint32_t y)
{
	uint32_t	bounces;
	uint32_t	rays;

	rays = 0;
	bounces = 0;
	while (rays < NUM_RAYS)
	{
		setup(data, ray, x, y);
		bounces = 0;
		while (bounces < MAX_BOUNCES && sum(ray->col->colour) > THRESHHOLD && ray->col->type != LIGHT)
		{
			bounce(data, ray, y % data->num_threads);
			bounces++;
			ray->origin = ray->col->location;
			ray->col->colour.vec3 *= 0.9f;
		}
		if (ray->col->type == LIGHT)
			data->pix[y][x].samples.vec3 += ray->col->colour.vec3;
		rays++;
	}
	data->pix[y][x].pix_clr.vec3 = data->pix[y][x].samples.vec3 / (float)(NUM_RAYS * data->iterations);
	data->pix[y][x].pix_clr = combine_colours(data->pix[y][x].pix_clr, data->pix[y][x].ambient);
	clamp(&data->pix[y][x].pix_clr);
}
