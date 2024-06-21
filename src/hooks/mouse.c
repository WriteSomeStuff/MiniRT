/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/23 13:53:09 by vincent       #+#    #+#                 */
/*   Updated: 2024/06/20 21:41:28 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	rt_close(void *param)
{
	t_data *data;

	data = (t_data *)param;
	pthread_mutex_lock(&data->mutex);
	data->go = false;
	pthread_mutex_unlock(&data->mutex);
	wait_for_threads(data);
	exit_success(data);
}

void	rt_resize(int32_t x, int32_t y, void *param)
{
	t_data *data;

	data = (t_data *)param;
	if (mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_LEFT) == false)
	{
		pthread_mutex_lock(&data->mutex);
		data->go = false;
		pthread_mutex_unlock(&data->mutex);
		wait_for_threads(data);
		if (x > WINDOW_MAX_WIDTH)
			x = WINDOW_MAX_WIDTH;
		if (y > WINDOW_MAX_WIDTH)
			y = WINDOW_MAX_WIDTH;
		mlx_set_window_size(data->mlx, x, y);
		data->window->width = (uint32_t)x;
		data->window->height = (uint32_t)y;
		data->window->aspect_ratio = (float)y / x;
		mlx_resize_image(data->scene, x, y);
		mlx_resize_image(data->highlight, x, y);
		cast_rays(data);
		redraw(data);
	}
}

void	rt_scroll(double xdelta, double ydelta, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	(void)xdelta;
	if (ydelta != 0)
	{
		ydelta *= -10;
		if (ydelta + data->cam->fov < 0)
			data->cam->fov = 0;
		else if (ydelta + data->cam->fov > 180)
			data->cam->fov = 180;
		else
			data->cam->fov += ydelta;
		data->cam->fov_correction = tan(degree_to_radian(data->cam->fov) / 2);
		/* 	This seems bugged	*/
		cast_rays(data);
		draw(data);
	}
}

