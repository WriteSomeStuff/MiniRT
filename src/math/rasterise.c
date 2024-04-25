/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rasterise.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/14 14:42:12 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/04/25 12:27:06 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	direction_to_xy(t_data *data, float x, float y)
{
	t_vec	t;

	t.x = (2 * ((x + 0.5f) / data->mlx->width) - 1);
	t.y = (1 - (2 * ((y + 0.5f) / data->mlx->height))) * data->window->aspect_ratio;
	t.z = 1;
	t.x *= data->cam->fov_correction;
	t.y *= data->cam->fov_correction;
	return (normalize_vector(t));
}

// t_vec	direction_to_xy(t_data *data, float x, float y)
// {
// 	t_vec	t;

// 	t.vec3 = data->cam->orientation.vec3;
// 	t.x += (2 * ((x + 0.5f) / data->mlx->width) - 1) * data->cam->fov_correction;
// 	t.y += (1 - (2 * ((y + 0.5f) / data->mlx->height))) * data->window->aspect_ratio * data->cam->fov_correction;
// 	// t.vec3 *= data->cam->fov_correction;
// 	// t.x *= data->cam->fov_correction;
// 	// t.y *= data->cam->fov_correction;
// 	return (normalize_vector(&t));
// }