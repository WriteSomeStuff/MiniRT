/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/23 13:53:09 by vincent       #+#    #+#                 */
/*   Updated: 2024/07/04 14:48:12 by vincent       ########   odam.nl         */
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

void	rt_resize(void *param)
{
	t_data *data;

	data = (t_data *)param;
	// if (mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_LEFT) == false)
	// {
	if (data->mlx->width != data->window->width || data->mlx->height != data->window->height)
	{
		pthread_mutex_lock(&data->mutex);
		data->go = false;
		pthread_mutex_unlock(&data->mutex);
		wait_for_threads(data);
		reset_pixel_array(data, data->pix, data->window->width, data->window->height);
		data->window->width = data->mlx->width;
		data->window->height = data->mlx->height;
		if (data->mlx->width > WINDOW_MAX_WIDTH)
		{
			data->window->width = WINDOW_MAX_WIDTH;
			mlx_set_window_size(data->mlx, data->window->width, data->window->height);
		}
		if (data->mlx->height > WINDOW_MAX_WIDTH)
		{
			data->window->height = WINDOW_MAX_WIDTH;
			mlx_set_window_size(data->mlx, data->window->width, data->window->height);
		}
		data->window->aspect_ratio = (float)data->window->height / data->window->width;
		printf("x: %d, y: %d\n", data->window->width, data->window->height);
		cast_rays(data);
		mlx_resize_image(data->scene, data->window->width, data->window->height);
		mlx_resize_image(data->highlight, data->window->width, data->window->height);
		normalize_scene(data);
		draw(data);
	}
	// }
}

void	rt_scroll(double xdelta, double ydelta, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	(void)xdelta;
	if (ydelta < 0)
		ydelta = 10;
	else
		ydelta = -10;
	if (ydelta + data->cam->fov < 0)
		data->cam->fov = 0;
	else if (ydelta + data->cam->fov > 180)
		data->cam->fov = 180;
	else
		data->cam->fov += ydelta;
	data->cam->fov_correction = tan(degree_to_radian(data->cam->fov) / 2);
	cast_rays(data);
	redraw(data);
}

