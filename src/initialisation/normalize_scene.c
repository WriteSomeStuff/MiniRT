/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   normalize_scene.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/04 13:35:16 by vincent       #+#    #+#                 */
/*   Updated: 2024/08/02 14:55:08 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	rotate_cones(t_cone *c, t_quat rotation)
{
	puts("BB");
	while (c->object != INVALID)
	{
		puts("AA");
		rotate(&c->apex, rotation);
		rotate(&c->orientation, rotation);
		// what else?
		c++;
	}
}

static void	rotate_cylinders(t_cylinder *c, t_quat rotation)
{
	while (c->object != INVALID)
	{
		rotate(&c->center, rotation);
		rotate(&c->base, rotation);
		rotate(&c->top, rotation);
		rotate(&c->orientation, rotation);
		c++;
	}
}

static void	rotate_discs(t_disc *d, t_quat rotation)
{
	while (d->object != INVALID)
	{
		rotate(&d->center, rotation);
		rotate(&d->orientation, rotation);
		d->rev_norm.vec3 = d->orientation.vec3 * -1;
		d++;
	}
}

static void	rotate_planes(t_plane *p, t_quat rotation)
{
	while (p->object != INVALID)
	{
		rotate(&p->location, rotation);
		rotate(&p->orientation, rotation);
		p->rev_norm.vec3 = p->orientation.vec3 * -1;
		p++;
	}
}

static void	rotate_spheres(t_sphere *s, t_quat rotation)
{
	while (s->object != INVALID)
	{
		rotate(&s->center, rotation);
		s++;
	}
}

void	normalize_scene(t_data *data)
{
	t_vec	turn;
	t_quat	rotation;
	float	ang;

	data->selected = -1;
	translate_objects(data, data->cam->viewpoint);
	turn = cross(data->cam->orientation, vec(0, 0, 1));
	ang = angle(vec(0, 0, 1), data->cam->orientation);
	if (fabs(data->cam->orientation.z + 1.0f) < OFFSET)
	{
		turn = vec(0, 1, 0);
		ang = degree_to_radian(180);
	}
	turn = normalize_vector(turn);
	rotation = quat(ang, turn);
	if (rotation.real == 0)
		return ;
	rotate_cones(data->cones, rotation);
	rotate_cylinders(data->cyls, rotation);
	rotate_discs(data->discs, rotation);
	rotate_planes(data->planes, rotation);
	rotate_spheres(data->spheres, rotation);
	data->cam->orientation = vec(0, 0, 1);
}
