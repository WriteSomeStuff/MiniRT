/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rasterise.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/14 14:42:12 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/04/03 10:41:50 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	direction_to_xy(t_data *data, float x, float y)
{
	t_vec	t;

	t.x = (2 * ((x + 0.5f) / data->mlx->width) - 1) * data->window->aspect_ratio;
	t.y = 1 - 2 * ((y + 0.5f) / data->mlx->height);
	t.z = 1;
	// printf("tan: %f\n", tan(degree_to_radian((float)data->cam->fov) / 2));
	t.x *= tan(degree_to_radian((float)data->cam->fov) / 2);
	t.y *= tan(degree_to_radian((float)data->cam->fov) / 2);
	return (normalize_vector(&t));
}
