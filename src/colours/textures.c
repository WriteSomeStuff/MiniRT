/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 17:00:29 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/08/15 18:00:57 by vincent       ########   odam.nl         */
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

static t_vec	cone_tex(void *coneptr, t_vec location)
{
	t_cone	*cone;

	(void)location;
	cone = (t_cone *)coneptr;
	return (cone->colour);
}

static t_vec	cylinder_tex(void *cylptr, t_vec location)
{
	t_cylinder	*cyl;

	(void)location;
	cyl = (t_cylinder *)cylptr;
	return (cyl->colour);
}

static t_vec	plane_tex(void *planeptr, t_vec intersection)
{
	t_plane	*plane;

	(void)intersection;
	plane = (t_plane *)planeptr;
	return (plane->colour);
}

static t_vec	sphere_tex(void *sphereptr, t_vec sn)
{
	float		x;
	float		y;
	t_sphere	*sphere;

	sphere = (t_sphere *)sphereptr;
	if (sphere->tex == NULL)
	{
		return (sphere->colour);
	}
	rotate(&sn, quat(sphere->rotated, sphere->orientation));
	x = atan2(sn.z, sn.x) / (2 * PI) + 0.5f;
	y = acos(sn.y) / PI;
	x *= sphere->tex->width - 1;
	y *= sphere->tex->height - 1;
	return (pixel_to_clrvec(sphere->tex, (uint32_t)x, (uint32_t)y));
}
	// return (checkerboard_tex((int32_t)(x * 20), (int32_t)(y * 20)));

t_vec	get_object_colour(t_hit *col)
{
	static t_vec	(*ptr[6])(void *, t_vec) = {&cone_tex, &cylinder_tex, \
		NULL, &plane_tex, &sphere_tex, &sphere_tex};

	return (ptr[col->type](col->obj, col->surface_norm));
}
