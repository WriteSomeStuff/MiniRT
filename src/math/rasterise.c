/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rasterise.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/14 14:42:12 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/04/04 17:19:01 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	direction_to_xy(t_data *data, float x, float y)
{
	t_vec	t;
	t_vec	cam;
	t_vec	res;

	cam.x = 0;
	cam.y = 0;
	cam.z = 0;
	t.x = (2 * ((x + 0.5f) / data->mlx->width) - 1) * data->window->aspect_ratio;
	t.y = 2 * ((y + 0.5f) / data->mlx->height) - 1;
	t.z = 1;
	t.x *= tan(degree_to_radian((float)data->cam->fov) / 2);
	t.y *= tan(degree_to_radian((float)data->cam->fov) / 2);
	res = normalize_vector(&t);
	// printf("Length: %f\n", len);
	t.x *= res.x * res.z;
	t.y *= res.y * res.z;
	// puts("CAM");
	// print_vector(cam);
	// set_vector(&res, &cam, &t);
	// puts("RES");
	// print_vector(res);
	return (normalize_vector(&t));
}
