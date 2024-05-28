/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyboard.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/21 17:25:12 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/05/28 14:27:22 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* void	handle_pressed_object(t_data * data)
{
	t_vec	t;
	t_quat	turn;

	t = cross(data->cam->orientation, vec(0, 0, 1));
	print_vector(t);
	t = normalize_vector(t);
	turn = quat(angle(vec(0, 0, 1), data->cam->orientation), t.x, t.y, t.z);
	
} */

static void	move(t_data *data, t_vec v)
{
	translate_objects(data, v);
	draw(data);
}

static void	turn_camera(t_data *data, keys_t key)
{
	if (key == MLX_KEY_LEFT)
	{
		rotate(&data->cam->orientation, quat(degree_to_radian(-15), vec(0, 1, 0)));
	}
	if (key == MLX_KEY_RIGHT)
	{
		rotate(&data->cam->orientation, quat(degree_to_radian(15), vec(0, 1, 0)));
	}
	if (key == MLX_KEY_UP)
	{
		rotate(&data->cam->orientation, quat(degree_to_radian(-15), vec(1, 0, 0)));
	}
	if (key == MLX_KEY_DOWN)
	{
		rotate(&data->cam->orientation, quat(degree_to_radian(15), vec(1, 0, 0)));
	}
	normalize_scene(data);
	draw(data);
}

void	rt_keys(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		exit_success(data);
	if (keydata.key >= MLX_KEY_RIGHT && keydata.key <= MLX_KEY_UP && \
		keydata.action == MLX_RELEASE)
		turn_camera(data, keydata.key);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		move(data, vec(0, 0, 0.25));
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		move(data, vec(0, 0, -0.25));
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		move(data, vec(-0.25, 0, 0));
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		move(data, vec(0.25, 0, 0));
}
