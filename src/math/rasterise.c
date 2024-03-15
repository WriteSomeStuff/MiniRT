/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rasterise.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/14 14:42:12 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/03/15 17:35:01 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// t_vec	reflection_direction(t_data *data, const t_vec *incoming, const t_vec *surface_angle)
// {
// 	t_vec	bounce_direction;

// 	bounce_direction = dot_product(incoming, surface_angle);
// 	bounce_direction = 
// 	bounce_direction = scale_vector()
// }

t_vec	direction_to_xy(t_data *data, float x, float y)
{
	t_vec	t;

	t.x = 1 - 2 * ((x + 0.5f) / data->mlx->height);
	t.y = (2 * ((y + 0.5f) / data->mlx->width) - 1) * data->window->aspect_ratio;
	t.z = -1;
	t.x *= tan(degree_to_radian((float)data->cam->fov) / 2);
	t.y *= tan(degree_to_radian((float)data->cam->fov) / 2);
	return (normalize_vector(&t));
}
