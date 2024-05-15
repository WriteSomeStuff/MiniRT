/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyboard.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/21 17:25:12 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/05/14 22:46:54 by vincent       ########   odam.nl         */
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

void	handle_press(t_data *data, t_vec v, int32_t which)
{
	// if (data->selected != -1 && which == 1)
	// {
	// 	// rotation
	// }
	// else if (data->selected != -1 && which == 2)
	// 	// translation
	if (which == 1)
	{
		data->cam->orientation = v;
		normalize_scene(data);
	}
	else
		translate_objects(data, v);
	draw_something(data, 0, 0);	
}

void	rt_keys(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		exit_success(data);
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_RELEASE)
		handle_press(data, normalize_vector(vec(0, 0.25, 1)), 1);
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_RELEASE)
		handle_press(data, normalize_vector(vec(0, -0.25, 1)), 1);
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		handle_press(data, normalize_vector(vec(-0.25, 0, 1)), 1);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		handle_press(data, normalize_vector(vec(0.25, 0, 1)), 1);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		handle_press(data, vec(0, 0, 0.25), 2);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		handle_press(data, vec(0, 0, -0.25), 2);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		handle_press(data, vec(-0.25, 0, 0), 2);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		handle_press(data, vec(0.25, 0, 0), 2);
}
