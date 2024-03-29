/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 17:00:29 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/03/29 17:32:06 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

t_vec	plane_texture(t_plane *plane, t_vec *loc)
{
	t_vec	dir;
	uint32_t	x;
	uint32_t	y;

	if (plane->tex == NULL)
		return (plane->colour);
	dir.vec3 = loc->vec3 - plane->location.vec3;
	x = (uint32_t)(fabs(dir.z) * 100) % 360;
	y = (uint32_t)(fabs(dir.y) * 100) % 360;
	printf("x: %d, y: %d\n", x, y);
	return (pixel_to_clrvec(plane->tex, x, y));
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