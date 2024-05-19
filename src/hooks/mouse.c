/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/23 13:53:09 by vincent       #+#    #+#                 */
/*   Updated: 2024/05/19 16:25:17 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* static void	img_to_win(t_data *data)
{
	for (uint32_t y = 0; y < data->window->height; y++)
	{
		for (uint32_t x = 0; x < data->window->width; x++)
		{
			mlx_image_to_window(data->mlx, data->highlight, x, y);
		}
	}
} */

void	rt_scroll(double xdelta, double ydelta, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	(void)xdelta;
	if (ydelta != 0)
	{
		ydelta *= -5;
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

