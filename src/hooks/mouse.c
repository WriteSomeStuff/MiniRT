/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/23 13:53:09 by vincent       #+#    #+#                 */
/*   Updated: 2024/03/31 23:12:15 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	highlight_sphere(t_data *data, int16_t num)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < data->window->height)
	{
		x = 0;
		while (x < data->window->width)
		{
			if (data->map[y][x] != num)
			{
				if (x < data->window->width - 2 && data->map[y][x + 2] == num)
				{
					// printf("num: %d, map: %d\n", num, data->map[y][x + 1]);
					mlx_put_pixel(data->image, x, y, 0xFFFFFFFF);
				}
				if (x > 1 && data->map[y][x - 2] == num)
				{
					// printf("num: %d, map: %d\n", num, data->map[y][x - 2]);
					mlx_put_pixel(data->image, x, y, 0xFFFFFFFF);
				}
				if (y < data->window->height - 2 && data->map[y + 2][x] == num)
				{
					mlx_put_pixel(data->image, x, y, 0xFFFFFFFF);
				}
				if (y > 1 && data->map[y - 2][x] == num)
				{
					mlx_put_pixel(data->image, x, y, 0xFFFFFFFF);
				}
			}
			x++;
		}
		y++;
	}
}

void	rt_resize(int32_t width, int32_t height, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	data->window->width = width;
	data->window->height = height;
	data->window->aspect_ratio = (float)height / width;
	draw_something(data, 0, 0);
}

void	rt_select(mouse_key_t btn, action_t act, modifier_key_t m, void *p)
{
	t_data		*data;
	static bool	selected = false;
	int32_t		x;
	int32_t		y;

	(void)m;
	data = (t_data *)p;
	if (btn == MLX_MOUSE_BUTTON_LEFT && act == MLX_RELEASE)
	{
		if (selected == false)
		{
			mlx_get_mouse_pos(data->mlx, &x, &y);
			if (data->map[y][x] == SPHERE)
				highlight_sphere(data, SPHERE);
			selected = true;
		}
		else
		{
			draw_something(data, 0, 0);
			selected = false;
		}
	}
}
