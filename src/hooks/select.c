/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   select.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/19 16:25:08 by vincent       #+#    #+#                 */
/*   Updated: 2024/06/26 17:46:31 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	un_highlight(t_data *data)
{
	int32_t	x;
	int32_t	y;

	data->selected = -1;
	y = 0;
	while (y < data->window->height)
	{
		x = 0;
		while (x < data->window->width)
		{
			mlx_put_pixel(data->highlight, x, y, 0x0);
			x++;
		}
		y++;
	}
}

static bool	check_object(t_data *data, int16_t num, int32_t x, int32_t y)
{
	bool	draw_pixel;

	draw_pixel = false;
	if (data->pix[y][x].obj_num != num)
	{
		if (x < data->window->width - 2 && data->pix[y][x + 2].obj_num == num)
			draw_pixel = true;
		if (x > 1 && data->pix[y][x - 2].obj_num == num)
			draw_pixel = true;
		if (y < data->window->height - 2 && data->pix[y + 2][x].obj_num == num)
			draw_pixel = true;
		if (y > 1 && data->pix[y - 2][x].obj_num == num)
			draw_pixel = true;		
	}
	return (draw_pixel);
}

static void	highlight_object(t_data *data, int16_t num)
{
	int32_t	x;
	int32_t	y;

	y = 0;
	if (data->selected != -1 || num == -1)
	{
		un_highlight(data);
		return ;
	}
	data->selected = num;
	while (y < data->window->height)
	{
		x = 0;
		while (x < data->window->width)
		{
			if (check_object(data, num, x, y) == true)
				mlx_put_pixel(data->highlight, x, y, 0xffffffff);
			x++;
		}
		y++;
	}
}

void	rt_select(mouse_key_t btn, action_t act, modifier_key_t m, void *p)
{
	t_data		*data;
	int32_t		x;
	int32_t		y;
	// int32_t		width;
	// int32_t		height;

	(void)m;
	data = (t_data *)p;
	if (btn == MLX_MOUSE_BUTTON_LEFT && act == MLX_RELEASE)
	{
		mlx_get_mouse_pos(data->mlx, &x, &y);
		
		// printf("x: %u, y: %u\n", x, y);
		highlight_object(data, data->pix[y][x].obj_num);
		mlx_image_to_window(data->mlx, data->highlight, 0, 0);
	}
}
