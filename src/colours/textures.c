/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 17:00:29 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/07/30 13:13:09 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_vec	pixel_to_clrvec(mlx_texture_t *t, uint32_t x, uint32_t y)
{
	t_vec	clr;

	if (x >= t->width || y >= t->height)
	{
		printf("x: %u y: %u\n", x, y);
	}
	clr.r = t->pixels[y * 4 * t->width + x * 4];
	clr.g = t->pixels[y * 4 * t->width + x * 4 + 1];
	clr.b = t->pixels[y * 4 * t->width + x * 4 + 2];
	rgb_to_floats(&clr);
	return (clr);
}

static t_vec	cylinder_texture(void *cylptr, t_vec location)
{
	t_cylinder	*cyl;

	(void)location;
	cyl = (t_cylinder *)cylptr;
	return (cyl->colour);
}

static t_vec	plane_texture(void *planeptr, t_vec intersection)
{
	t_plane	*plane;

	(void)intersection;
	plane = (t_plane *)planeptr;
	return (plane->colour);
}

static t_vec	sphere_texture(void *sphereptr, t_vec loc)
{
	float		x;
	float		y;
	t_sphere	*sphere;

	sphere = (t_sphere *)sphereptr;
	if (sphere->tex == NULL)
		return (sphere->colour);
	x = sphere->tex->width / 2 + ((loc.x / 2) * (sphere->tex->width / 2)) - 1;
	y = sphere->tex->height - (sphere->tex->height / \
		2 + (loc.y * (sphere->tex->height / 2))) - 1;
	return (pixel_to_clrvec(sphere->tex, (uint32_t)x, (uint32_t)y));
}
	// return (checkerboard_tex((int32_t)(x * 20), (int32_t)(y * 20)));

t_vec	get_object_colour(t_hit *col)
{
	static t_vec	(*ptr[5])(void *, t_vec) = {&cylinder_texture, NULL, \
		&plane_texture, &sphere_texture, &sphere_texture};

	return (ptr[col->type](col->obj, col->location));
}
