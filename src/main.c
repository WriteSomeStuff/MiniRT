/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 17:46:38 by cschabra      #+#    #+#                 */
/*   Updated: 2024/04/08 18:19:04 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	test();

void	initialise_window(t_data *data)
{
	t_window	*w;

	w = rt_calloc(data, sizeof(t_window));
	data->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (data->mlx == NULL)
	{
		exit_error(data, ": mlx failed to initialise");
	}
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (data->image == NULL)
	{
		exit_error(data, ": image failed to load");
	}
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
	{
		exit_error(data, ": failed to load window");
	}
	w->width = data->mlx->width;
	w->height = data->mlx->height;
	printf("width: %d, height: %d\n", w->width, w->height);
	w->aspect_ratio = (float)data->mlx->height / data->mlx->width;
	data->window = w;
}

int32_t	main(int32_t argc, char **argv)
{
	t_data		data;

	if (argc != 2)
	{
		ft_putendl_fd("Error: incorrect argument count", STDERR_FILENO);
		return (1);
	}
	// t_vec	point;
	// t_quat	angle;

	// point.x = 0;
	// point.y = 0;
	// point.z = 1;
	// angle.x = 1;
	// angle.y = 1;
	// angle.z = 1;
	// angle = normalize_vector(&angle);
	rotate_point();
	exit(0);
	ft_bzero(&data, sizeof(t_data));
	initialise_window(&data);
	read_file(&data, argv[1]);
	draw_something(&data, 0, 0);

	mlx_loop_hook(data.mlx, ft_hook, &data);
	mlx_mouse_hook(data.mlx, rt_select, &data);
	mlx_resize_hook(data.mlx, &rt_resize, (void *)&data);
	mlx_loop(data.mlx);
	clean_up(&data);
	return (0);
}


// void	rotate_point(t_vec *pt, const t_vec *ang)
// {
// 	t_quat	point;
// 	t_quat	angle;
// 	t_vec	new;

// 	point = vector_to_quat(pt);
// 	angle = vector_to_quat(ang);
// 	point = rotate(&point, &angle);
// 	new = quat_to_vector(&point);
// 	print_vector(new);
// 	printf("length: %f\n", vector_length(NULL, &new));
// }