/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/23 13:53:09 by vincent       #+#    #+#                 */
/*   Updated: 2024/07/03 19:48:15 by vincent       ########   odam.nl         */
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
	static int time = 0;

	data = (t_data *)param;
	// if (mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_LEFT) == true)
	// {
	pthread_mutex_lock(&data->mutex);
	data->go = false;
	pthread_mutex_unlock(&data->mutex);
	// for (int32_t x = 0; x < data->window->width; x++)
	// {
	// 	mlx_image_to_window(data->mlx, data->highlight, x, y);
	// }
	// time = mlx_get_time();
	// if (mlx_get_time() - time > 0.1)
	// {
	// 	puts("TRIGGERED");
		if ((data->window->width != x || data->window->height != y) && time == 0)
		{
			// time = 1;
			if (x > WINDOW_MAX_WIDTH)
				x = WINDOW_MAX_WIDTH;
			if (y > WINDOW_MAX_WIDTH)
				y = WINDOW_MAX_WIDTH;
			wait_for_threads(data);
			// puts("uuu");
			data->window->width = x;
			data->window->height = y;
			data->window->aspect_ratio = (float)y / x;
			mlx_set_window_size(data->mlx, x, y);
			mlx_resize_image(data->scene, x, y);
			mlx_resize_image(data->highlight, x, y);
			printf("x: %d, y: %d\n", x, y);
			// reset_pixel_array(data, data->pix, data->window->width, data->window->height);
			cast_rays(data);
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

