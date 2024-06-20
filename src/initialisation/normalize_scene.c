/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   normalize_scene.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/04 13:35:16 by vincent       #+#    #+#                 */
/*   Updated: 2024/06/20 19:47:21 by vincent       ########   odam.nl         */
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
		p->rev_norm.vec3 = p->orientation.vec3 * -1;
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
	t_vec	turn;
	t_quat	rotation;

	data->selected = -1;
	translate_objects(data, data->cam->viewpoint);
	if ((int)radian_to_degree(angle(vec(0, 0, 1), data->cam->orientation) == 180))
		turn = vec(0, 1, 0);
	else
	{
		turn = cross(data->cam->orientation, vec(0, 0, 1));
		turn = normalize_vector(turn);
	}
	rotation = quat(angle(vec(0, 0, 1), data->cam->orientation), turn);
	if (rotation.real == 0)
		return ;
	rotate_cylinders(data->cyls, rotation);
	rotate_planes(data->planes, rotation);
	rotate_spheres(data->spheres, rotation);
	data->cam->orientation = vec(0, 0, 1);
}
