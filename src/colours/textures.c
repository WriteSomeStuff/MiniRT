/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 17:00:29 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/07/12 17:39:47 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_vec	pixel_to_clrvec(mlx_texture_t *t, uint32_t x, uint32_t y)
{
	t_vec	clr;

	if (x >= t->width || y >= t->height)
	{
		printf("x: %d y: %d\n", x, y);
	}
	clr.r = t->pixels[y * 4 * t->width + x * 4];
	clr.g = t->pixels[y * 4 * t->width + x * 4 + 1];
	clr.b = t->pixels[y * 4 * t->width + x * 4 + 2];
	rgb_to_floats(&clr);
	return (clr);
}

static t_vec	cylinder_texture(void *cylptr, t_vec location)
{
	// t_vec	dir;
	// float	x;
	// float	y;
	t_cylinder	*cyl;

	cyl = (t_cylinder*)cylptr;
	if (cyl->tex == NULL)
		return (cyl->colour);
	else
		return (location);
	// set_vector(&dir, &cyl->center, surface);
	// x = cyl->tex->width / 2 + ((dir.x / 2) * (cyl->tex->width / 2));
	// y = cyl->tex->height - (cyl->tex->height / 2 + (dir.y * (cyl->tex->height / 2)));
	// return (pixel_to_clrvec(cyl->tex, (uint32_t)x, (uint32_t)y));
}

static t_vec	plane_texture(void *planeptr, t_vec intersection)
{
	t_vec	dir;
	float	x;
	float	y;
	const float	scalar = 100;
	t_plane	*plane;

	plane = (t_plane*)planeptr;
	// if (plane->tex == NULL)
	return (plane->colour);
	dir = normalize_vector(cross(vec(0, 0, 1), plane->orientation));
	rotate(&intersection, quat(angle(plane->orientation, vec(0, 0, 1)), dir));
	x = (intersection.x - plane->location.x) * scalar;
	y = (intersection.y - plane->location.y) * scalar;
	if (x < 0.0f)
	{
		x *= -1;
		x = fmodf(x, scalar);
		x = scalar - x - 1;
	}
	else
		x = fmodf(x, scalar);
	if (y < 0.0f)
	{
		y *= -1;
		y = fmodf(y, scalar);
		y = scalar - y - 1;
	}
	else
		y = fmodf(y, scalar);
	// return (checkerboard_tex((int32_t)x, (int32_t)y));
	return (pixel_to_clrvec(plane->tex, (uint32_t)(x * plane->tex->width / scalar), (uint32_t)(y * plane->tex->height / scalar)));
}

static t_vec	sphere_texture(void *sphereptr, t_vec loc)
{
	float	x;
	float	y;
	t_sphere	*sphere;

	sphere = (t_sphere*)sphereptr;
	// if (sphere->tex == NULL)
	return (sphere->colour);
	x = sphere->tex->width / 2 + ((loc.x / 2) * (sphere->tex->width / 2)) - 1;
	y = sphere->tex->height - (sphere->tex->height / 2 + (loc.y * (sphere->tex->height / 2))) - 1;
	// return (checkerboard_tex((int32_t)(x * 20), (int32_t)(y * 20)));
	return (pixel_to_clrvec(sphere->tex, (uint32_t)x, (uint32_t)y));
}

t_vec	get_object_colour(t_hit *col)
{
	static t_vec	(*ptr[5])(void *, t_vec) = {&cylinder_texture, NULL, &plane_texture, &sphere_texture, &sphere_texture};
	
	return (ptr[col->type](col->obj, col->location));
}