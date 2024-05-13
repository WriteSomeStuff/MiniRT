/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/23 13:53:09 by vincent       #+#    #+#                 */
/*   Updated: 2024/05/13 15:09:52 by vvan-der      ########   odam.nl         */
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
		draw_something(data, 0, 0);
		// recalculate rays instead of ^ 
	}
}

static void	highlight_object(t_data *data, int16_t num)
{
	static bool	highlighted = false;
	uint32_t	x;
	uint32_t	y;
	long		clr;

	y = 0;
	if (highlighted == false)
	{
		clr = 0xffffffff;
		highlighted = true;
		while (y < data->window->height)
		{
			x = 0;
			while (x < data->window->width)
			{
				if (data->pix[y][x].obj_num != num)
				{
					if (x < data->window->width - 2 && data->pix[y][x + 2].obj_num == num)
					{
						mlx_put_pixel(data->highlight, x, y, clr);
					}
					if (x > 1 && data->pix[y][x - 2].obj_num == num)
					{
						mlx_put_pixel(data->highlight, x, y, clr);
					}
					if (y < data->window->height - 2 && data->pix[y + 2][x].obj_num == num)
					{
						mlx_put_pixel(data->highlight, x, y, clr);
					}
					if (y > 1 && data->pix[y - 2][x].obj_num == num)
					{
						mlx_put_pixel(data->highlight, x, y, clr);
					}
				}
				x++;
			}
			y++;
		}
	}
	else
	{
		clr = 0x0;
		highlighted = false;
		while (y < data->window->height)
		{
			x = 0;
			while (x < data->window->width)
			{
				mlx_put_pixel(data->highlight, x, y, clr);
				x++;
			}
			y++;
		}
	}
	mlx_image_to_window(data->mlx, data->highlight, 0, 0);
}

void	rt_resize(int32_t width, int32_t height, void *param)
{
	t_data	*data;

	printf("w: %d, h: %d\n", width, height);
	data = (t_data *)param;	
	data->window->width = width;
	data->window->height = height;
	data->window->aspect_ratio = (float)height / width;
	draw_something(data, 0, 0);
}

void	rt_select(mouse_key_t btn, action_t act, modifier_key_t m, void *p)
{
	t_data		*data;
	int32_t		x;
	int32_t		y;

	(void)m;
	data = (t_data *)p;
	if (btn == MLX_MOUSE_BUTTON_LEFT && act == MLX_RELEASE)
	{
		mlx_get_mouse_pos(data->mlx, &x, &y);
		// if (selected == -2)
		// 	unselect(data);
		highlight_object(data, data->pix[y][x].obj_num);
	}
}
