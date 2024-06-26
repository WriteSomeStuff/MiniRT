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

static void	setup(t_data *data, t_ray *ray, int32_t x, int32_t y)
{
	ray->col->absorption = data->pix[y][x].absorption;
	ray->col->reflectivity = data->pix[y][x].reflectivity;
	ray->col->colour = data->pix[y][x].obj_clr;
	ray->origin = data->pix[y][x].location;
	ray->col->surface_norm = data->pix[y][x].surface_norm;
	ray->col->inside_obj = false;
	ray->col->type = INVALID;
}

static void	diffuse_bounce(t_data *data, t_ray *ray, uint32_t id)
{
	ray->direction = random_vector(data, id);
	ray->direction.vec3 += ray->col->surface_norm.vec3;
	ray->direction = norm_vec(ray->direction);
	if (dot(ray->direction, ray->col->surface_norm) < 0)
		ray->direction.vec3 *= -1;
	find_closest_object(data, ray->col, ray);
	draw_collision(ray->col, ray->col->absorption, 0);
}

float	max(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

/* static t_vec3	specular_bounce(t_data *data, t_ray *ray, int32_t x, int32_t y)
{
	uint32_t	bounces;
	const float		shininess = 2;
	float		shiny;

	bounces = 0;
	shiny = ray->col->reflectivity;
	while (bounces < MAX_BOUNCES)
	{
		setup(data, ray, x, y);
		ray->direction = reflect(ray->direction, ray->col->surface_norm);
		find_closest_object(data, ray->col, ray);
		draw_collision(ray->col, ray->col->absorption, ray->col->reflectivity);
		bounces++;
		if (ray->col->hit == false || ray->col->type == LIGHT || bounces == MAX_BOUNCES)
			break ;
		ray->origin = ray->col->location;
	}
	if (ray->col->type == LIGHT)
	{
		t_vec to_light;
		t_sphere *sphere;

		sphere = (t_sphere *)ray->col->obj;
		to_light.vec3 = sphere->center.vec3 - ray->col->location.vec3;
		to_light = normalize_vector(to_light);

		shiny *= pow(max(dot(ray->direction, to_light), 0.0f), shininess);
		return (ray->col->colour.vec3 * shiny);
	}
	return (vec(0, 0, 0).vec3);
} */

// specular = pow(dot(ligtdir, viewdir), shininess);

static t_vec	specular_bounce(t_data *data, t_ray *ray, int32_t x, int32_t y)
{
	uint32_t	bounces;
	t_vec		to_center;
	t_sphere	*light;

	bounces = 0;
	setup(data, ray, x, y);
	ray->col->colour.vec3 *= data->pix[y][x].reflectivity;
	while (bounces < MAX_BOUNCES && sum(ray->col->colour) > THRESHHOLD && ray->col->type != LIGHT)
	{
		ray->direction = reflect(ray->direction, ray->col->surface_norm);
		find_closest_object(data, ray->col, ray);
		draw_collision(ray->col, 0, ray->col->reflectivity);
		bounces++;
	}
	if (ray->col->type == LIGHT)
	{
		light = (t_sphere *)ray->col->obj;
		to_center.vec3 = light->center.vec3 - ray->col->location.vec3;
		to_center = norm_vec(to_center);
		ray->col->colour.vec3 *= 2.0f * dot(ray->direction, to_center) - 1.0f;
		ray->col->colour.x = max(ray->col->colour.x, 0.0);
		ray->col->colour.y = max(ray->col->colour.y, 0.0);
		ray->col->colour.z = max(ray->col->colour.z, 0.0);
		return (ray->col->colour);
	}
	return (vec(0, 0, 0));
}

// every single bounce calculate the specular, add the specular * absorption to the diffuse * reflectivity.
void	trace(t_data *data, t_ray *ray, int32_t x, int32_t y)
{
	uint32_t	bounces;
	uint32_t	rays;
	t_vec		specular_clr;

	rays = 0;
	specular_clr = specular_bounce(data, ray, x, y);
	while (rays < NUM_RAYS)
	{
		setup(data, ray, x, y);
		ray->col->colour.vec3 *= data->pix[y][x].absorption;
		bounces = 0;
		while (bounces < MAX_BOUNCES && sum(ray->col->colour) > THRESHHOLD && ray->col->type != LIGHT)
		{
			diffuse_bounce(data, ray, y % data->num_threads);
			bounces++;
			ray->origin = ray->col->location;
			// ray->col->colour.vec3 *= 0.9f;
		}
		// if (y % data->num_threads == 0)
		// 	printf("%u\n", bounces);
		if (ray->col->type == LIGHT)
		{
			data->pix[y][x].samples.vec3 += ray->col->colour.vec3;
		}
		rays++;
	}
	data->pix[y][x].pix_clr.vec3 = (data->pix[y][x].samples.vec3 / (float)(NUM_RAYS * data->iterations));
	// if (x == data->window->height / 1.5 && (int)data->pix[y][x].reflectivity == 1 && y % data->num_threads == 0 && ray->col->type == LIGHT)
	// {
	// 	puts("diffuse:");
	// 	print_vector(data->pix[y][x].samples);
	// 	puts("speculoso:");
	// 	print_vector(tmp_clr);
	// 	printf("bounces: %u\n", bounces);
	// }
	// data->pix[y][x].pix_clr.x = pow(data->pix[y][x].pix_clr.x, 1 / 2.2);
	// data->pix[y][x].pix_clr.y = pow(data->pix[y][x].pix_clr.y, 1 / 2.2);
	// data->pix[y][x].pix_clr.z = pow(data->pix[y][x].pix_clr.z, 1 / 2.2);
	// data->pix[y][x].pix_clr = combine_colours(data->pix[y][x].pix_clr, specular_clr);
	data->pix[y][x].pix_clr.vec3 += specular_clr.vec3;
	clamp(&data->pix[y][x].pix_clr);
	data->pix[y][x].pix_clr = combine_colours(data->pix[y][x].pix_clr, data->pix[y][x].ambient);
}
