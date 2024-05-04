/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   normalize_scene.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/04 13:35:16 by vincent       #+#    #+#                 */
/*   Updated: 2024/05/04 14:19:09 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	rotate_cylinders(t_cylinder *c, t_vec t, float theta)
{
	while (c->object != INVALID)
	{
		rotate(&c->center, quat(theta ,t.x, t.y, t.z));
		rotate(&c->base, quat(theta ,t.x, t.y, t.z));
		rotate(&c->top, quat(theta ,t.x, t.y, t.z));
		rotate(&c->orientation, quat(theta ,t.x, t.y, t.z));
		c++;
	}
}

static void	rotate_lights(t_light *l, t_vec t, float theta)
{
	rotate(&l->source, quat(theta, t.x, t.y, t.z));
}

static void	rotate_planes(t_plane *p, t_vec t, float theta)
{
	while (p->object != INVALID)
	{
		rotate(&p->location, quat(theta, t.x, t.y, t.z));
		rotate(&p->orientation, quat(theta, t.x, t.y, t.z));
		p++;
	}
}

static void	rotate_spheres(t_sphere *s, t_vec t, float theta)
{
	while (s->object != INVALID)
	{
		rotate(&s->center, quat(theta ,t.x, t.y, t.z));
		// rotate(&s->orientation, quat(theta ,t.x, t.y, t.z));
		s++;
	}
}

void	normalize_scene(t_data *data)
{
	t_vec	turn;
	float	theta;

	translate_objects(data, data->cam->viewpoint);
	theta = angle(vec(0, 0, 1), data->cam->orientation);
	turn = cross(data->cam->orientation, vec(0, 0, 1));
	rotate_cylinders(data->cyls, turn, theta);
	rotate_lights(data->light, turn, theta);
	rotate_planes(data->planes, turn, theta);
	rotate_spheres(data->spheres, turn, theta);
	data->cam->orientation = vec(0, 0, 1);
	data->cam->viewpoint = vec(0, 0, 0);
}
