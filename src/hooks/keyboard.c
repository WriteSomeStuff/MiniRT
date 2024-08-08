/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyboard.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/21 17:25:12 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/08/08 17:57:26 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	reset_pixel_array(t_data *data, t_pixel **pixels, uint32_t width, \
	uint32_t height)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			pixels[y][x].ambient.vec3 *= 0;
			pixels[y][x].obj_clr.vec3 *= 0;
			pixels[y][x].samples.vec3 *= 0;
			pixels[y][x].pix_clr.vec3 *= 0;
			pixels[y][x].location.vec3 *= 0;
			pixels[y][x].surface_norm.vec3 *= 0;
			pixels[y][x].obj_num = -1;
			pixels[y][x].specular = 0;
			mlx_put_pixel(data->scene, x, y, 0xff);
			x++;
		}
		y++;
	}
	data->iterations = 0;
}

static void	move(t_data *data, t_vec translation)
{
	translate_objects(data, translation);
	redraw(data);
}

static void	turn_camera(t_data *data, keys_t key)
{
	if (key == MLX_KEY_LEFT)
		rotate(&data->cam->orientation, quat(degree_to_radian(-15), \
			vec(0, 1, 0)));
	else if (key == MLX_KEY_RIGHT)
		rotate(&data->cam->orientation, quat(degree_to_radian(15), \
			vec(0, 1, 0)));
	else if (key == MLX_KEY_UP)
		rotate(&data->cam->orientation, quat(degree_to_radian(-15), \
			vec(1, 0, 0)));
	else if (key == MLX_KEY_DOWN)
		rotate(&data->cam->orientation, quat(degree_to_radian(15), \
			vec(1, 0, 0)));
}

void	rt_keys(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		pthread_mutex_lock(&data->mutex);
		data->go = false;
		pthread_mutex_unlock(&data->mutex);
		wait_for_threads(data);
		exit_success(data);
	}
	if (keydata.key >= MLX_KEY_RIGHT && keydata.key <= MLX_KEY_UP && \
		keydata.action == MLX_RELEASE)
		turn_camera(data, keydata.key);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		move(data, vec(0, 0, 1));
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		move(data, vec(0, 0, -1));
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		move(data, vec(-1, 0, 0));
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		move(data, vec(1, 0, 0));
	redraw(data);
}

void	redraw(t_data *data)
{
	pthread_mutex_lock(&data->mutex);
	data->go = false;
	pthread_mutex_unlock(&data->mutex);
	wait_for_threads(data);
	reset_pixel_array(data, data->pix, data->window->width, \
		data->window->height);
	cast_rays(data);
	normalize_scene(data);
	draw(data);
}
