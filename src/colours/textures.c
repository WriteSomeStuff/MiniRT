/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 17:00:29 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/06/01 20:26:07 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// void	translate(t_sphere *sphere, float *x, float *y)
// {
// 	(void)sphere;
// 	*x = 100 + ((*x) * 100);
// 	*y = 100 - ((*y) * 100);
// 	printf("x: %f, y: %f\n", *x, *y);
// }

// bool	b_or_w(float x, float y, float modulus)
// {
// 	if ((fabs(fmod(x, modulus)) <= modulus / 2 && fabs(fmod(y, modulus)) <= modulus / 2) ||
// 		(fabs(fmod(x, modulus)) > modulus / 2 && fabs(fmod(y, modulus)) > modulus / 2))
// 		return (false);
// 	return (true);
// }

t_vec	checkerboard_tex(uint32_t x, uint32_t y)
{
	if (x % 20 < 10 && y % 20 >= 10)
		return (vec(0, 0, 0));
	else if (x % 20 >= 10 && y % 20 < 10)
		return (vec(0, 0, 0));
	else
		return (vec(1, 1, 1));	
}

static t_vec	pixel_to_clrvec(mlx_texture_t *t, int x, int y)
{
	t_vec		clr;

	clr.r = t->pixels[y * t->width + x];
	clr.g = t->pixels[y * t->width + x + 1];
	clr.b = t->pixels[y * t->width + x + 2];
	rgb_to_floats(&clr);
	return (clr);
}

t_vec	cylinder_texture(t_cylinder *cyl, t_vec *surface)
{
	t_vec	dir;
	float	x;
	float	y;

	if (cyl->tex == NULL)
		return (cyl->colour);
	set_vector(&dir, &cyl->center, surface);
	x = cyl->tex->width / 2 + ((dir.x / 2) * (cyl->tex->width / 2));
	y = cyl->tex->height - (cyl->tex->height / 2 + (dir.y * (cyl->tex->height / 2)));
	return (pixel_to_clrvec(cyl->tex, (int)x * 4, (int)y * 4));
}

t_vec	plane_texture(t_plane *plane, t_vec loc)
{
	t_vec	dir;
	float	ang;
	float	x;
	float	y;

	if (plane->tex == NULL)
		return (plane->colour);
	// print_vector(loc);
	ang = angle(plane->orientation, vec(0, 0, 1));
	// printf("angle: %f\n", ang);
	dir = norm_vec(cross(plane->orientation, vec(0, 0, 1)));
	// puts("direction to rotate around: ");
	// print_vector(dir);
	rotate(&loc, quat(ang, dir));
	// print_vector(loc);
	// exit(0);
	x = (plane->location.x - loc.x) * plane->tex->width / 5;
	y = (plane->location.y - loc.y) * plane->tex->height / 5;
	// x = (plane->location.x - loc.x);
	// y = (plane->location.y - loc.y);
	if (x < 0)
	{
		x *= -1;
		x = fmod(x, plane->tex->width);
		x = plane->tex->width - x;
	}
	else
		x = fmod(x, plane->tex->width);
	if (y < 0)
	{
		y *= -1;
		y = fmod(y, plane->tex->height);
		y = plane->tex->height - y;
	}
	else
		y = fmod(y, plane->tex->height);
	// printf("x: %f, y: %f\n", x, y);
	// return (checkerboard_tex((uint32_t)x, (uint32_t)y));
	return (pixel_to_clrvec(plane->tex, (int)x * 4, (int)y * 4));
}

t_vec	sphere_texture(t_sphere *sphere, t_vec loc)
{
	float	x;
	float	y;

	if (sphere->tex == NULL)
		return (sphere->colour);
	x = sphere->tex->width / 2 + ((loc.x / 2) * (sphere->tex->width / 2));
	y = sphere->tex->height - (sphere->tex->height / 2 + (loc.y * (sphere->tex->height / 2)));
	// return (checkerboard_tex((uint32_t)(x * 20), (uint32_t)(y * 20)));
	return (pixel_to_clrvec(sphere->tex, (int)x * 4, (int)y * 4));
}
