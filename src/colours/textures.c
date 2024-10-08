/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 17:00:29 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/08/16 13:03:10 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_vec	pixel_to_clrvec(mlx_texture_t *t, uint32_t x, uint32_t y)
{
	t_vec	clr;

	if (x > t->width || y > t->height)
	{
		printf("x: %u y: %u\n", x, y);
	}
	clr.r = t->pixels[y * 4 * t->width + x * 4];
	clr.g = t->pixels[y * 4 * t->width + x * 4 + 1];
	clr.b = t->pixels[y * 4 * t->width + x * 4 + 2];
	rgb_to_floats(&clr);
	return (clr);
}

static t_vec	plane_tex(void *planeptr, t_hit *col)
{
	t_plane	*plane;
	t_vec	location;
	float	x;
	float	y;

	plane = (t_plane *)planeptr;
	if (plane->tex == NULL)
		return (plane->colour);
	location = col->location;
	rotate(&location, quat(angle(plane->orientation, \
		vec(0, 0, 1)), vec(0, 1, 0)));
	location.vec3 -= plane->location.vec3;
	x = (location.x / 25) * plane->tex->width;
	y = (location.y / 25) * plane->tex->height;
	if (x < 0)
		x = plane->tex->width - fmod(x * -1, plane->tex->width) - 1;
	else
		x = fmod(x, plane->tex->width);
	if (y < 0)
		y = fmod(y * -1, plane->tex->height);
	else
		y = plane->tex->height - fmod(y, plane->tex->height) - 1;
	return (pixel_to_clrvec(plane->tex, (uint32_t)x, (uint32_t)y));
}

static t_vec	sphere_tex(void *sphereptr, t_hit *col)
{
	float		x;
	float		y;
	t_sphere	*sphere;
	t_vec		sn;

	sphere = (t_sphere *)sphereptr;
	if (sphere->tex == NULL)
		return (sphere->colour);
	sn = col->surface_norm;
	rotate(&sn, quat(sphere->rotated, sphere->orientation));
	x = atan2(sn.z, sn.x) / (2 * PI) + 0.5f;
	y = acos(sn.y) / PI;
	x *= sphere->tex->width - 1;
	y *= sphere->tex->height - 1;
	return (pixel_to_clrvec(sphere->tex, (uint32_t)x, (uint32_t)y));
}

t_vec	get_object_colour(t_hit *col)
{
	static t_vec	(*ptr[6])(void *, t_hit *) = {&cone_tex, &cylinder_tex, \
		&disc_tex, &plane_tex, &sphere_tex, &sphere_tex};

	return (ptr[col->type](col->obj, col));
}
