/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotate_objects.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/16 13:10:20 by cschabra      #+#    #+#                 */
/*   Updated: 2024/08/16 13:10:57 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	rotate_cones(t_cone *c, t_quat rotation)
{
	while (c->object != INVALID)
	{
		rotate(&c->apex, rotation);
		rotate(&c->base, rotation);
		rotate(&c->orientation, rotation);
		c++;
	}
}

void	rotate_cylinders(t_cylinder *c, t_quat rotation)
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

void	rotate_discs(t_disc *d, t_quat rotation)
{
	while (d->object != INVALID)
	{
		rotate(&d->center, rotation);
		rotate(&d->orientation, rotation);
		d->rev_norm.vec3 = d->orientation.vec3 * -1;
		d++;
	}
}

void	rotate_planes(t_plane *p, t_quat rotation)
{
	while (p->object != INVALID)
	{
		rotate(&p->location, rotation);
		rotate(&p->orientation, rotation);
		p->rev_norm.vec3 = p->orientation.vec3 * -1;
		p++;
	}
}

void	rotate_spheres(t_sphere *s, t_quat rotation)
{
	while (s->object != INVALID)
	{
		rotate(&s->center, rotation);
		rotate(&s->orientation, rotation);
		s->rotated += rotation.real;
		s++;
	}
}
