/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   normalize_scene.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/04 13:35:16 by vincent       #+#    #+#                 */
/*   Updated: 2024/08/16 13:10:35 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
