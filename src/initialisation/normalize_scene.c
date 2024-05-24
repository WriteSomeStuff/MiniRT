/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   normalize_scene.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/04 13:35:16 by vincent       #+#    #+#                 */
/*   Updated: 2024/05/24 14:12:11 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

static void	rotate_planes(t_plane *p, t_quat rotation)
{
	while (p->object != INVALID)
	{
		rotate(&p->location, rotation);
		rotate(&p->orientation, rotation);
		p++;
	}
}

static void	rotate_spheres(t_sphere *s, t_quat rotation)
{
	while (s->object != INVALID)
	{
		rotate(&s->center, rotation);
		// rotate(&s->orientation, quat(theta ,t.x, t.y, t.z));
		s++;
	}
}

void	normalize_scene(t_data *data)
{
	t_vec	t;
	t_quat	turn;

	translate_objects(data, data->cam->viewpoint);
	t = cross(data->cam->orientation, vec(0, 0, 1));
	t = normalize_vector(t);
	turn = quat(angle(vec(0, 0, 1), data->cam->orientation), t.x, t.y, t.z);
	if (turn.real == 0)
		return ;
	rotate_cylinders(data->cyls, turn);
	rotate_planes(data->planes, turn);
	rotate_spheres(data->spheres, turn);
	data->cam->orientation = vec(0, 0, 1);
}
