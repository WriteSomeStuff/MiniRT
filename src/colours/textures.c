/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 17:00:29 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/05/28 14:52:13 by vvan-der      ########   odam.nl         */
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

bool	b_or_w(float x, float y, float modulus)
{
	if ((fabs(fmod(x, modulus)) <= modulus / 2 && fabs(fmod(y, modulus)) <= modulus / 2) ||
		(fabs(fmod(x, modulus)) > modulus / 2 && fabs(fmod(y, modulus)) > modulus / 2))
		return (false);
	return (true);
}

/* bool	checkerboard_tex(t_sphere *sphere, t_vec *loc)
{
	t_vec		sn;
	float		x = 0.0;
	float		y = 0.0;
	// float		z = 0.0;
	uint32_t	factor = 3;
	float		modulus = sphere->radius;

	sn.vec3 = loc->vec3 - (sphere->center.vec3 - sphere->radius);
	x = sn.x * factor;
	y = sn.y * factor;
	return (b_or_w(x, y, modulus));
} */

bool	checkerboard_tex(t_data *data, t_sphere *sphere, t_hit *col)
{
	t_vec	ray;

	ray.vec3 = sphere->center.vec3 - data->cam->viewpoint.vec3;
	ray = normalize_vector(ray);
	float th = radian_to_degree(angle(col->surface_norm, ray));
	printf("%f\n", th);
	if ((int)th % 2 == 0)
		return (true);
	return (false);
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
	int32_t	x;
	int32_t	y;

	if (plane->tex == NULL)
		return (plane->colour);
	ang = angle(plane->orientation, vec(0, 0, 1));
	dir.vec3 = loc.vec3 - plane->location.vec3;
	dir = norm_vec(dir);
	t_vec or = plane->orientation;
	or.vec3 *= -1;
	rotate(&loc, quat(ang, cross(or, dir)));
	x = loc.x - plane->location.x;
	if (x < 0)
	{
		x *= -1;
		x = plane->tex->width - x % plane->tex->width;
	}
	else
		x = x % plane->tex->width;
	y = loc.y - plane->location.y;
	if (y < 0)
	{
		y *= -1;
		y = plane->tex->height - y % plane->tex->height;
	}
	else
		y = y % plane->tex->height;
	return (pixel_to_clrvec(plane->tex, x * 4, y * 4));
}

t_vec	sphere_texture(t_sphere *sphere, t_vec *sn)
{
	float	x;
	float	y;

	if (sphere->tex == NULL)
		return (sphere->colour);
	x = sphere->tex->width / 2 + ((sn->x / 2) * (sphere->tex->width / 2));
	y = sphere->tex->height - (sphere->tex->height / 2 + (sn->y * (sphere->tex->height / 2)));
	return (pixel_to_clrvec(sphere->tex, (int)x * 4, (int)y * 4));
}
