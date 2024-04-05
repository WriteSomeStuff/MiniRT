/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 17:46:38 by cschabra      #+#    #+#                 */
/*   Updated: 2024/04/05 15:53:10 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	ft_bzero(&data, sizeof(t_data));
	initialise_window(&data);
	read_file(&data, argv[1]);
	draw_something(&data, 0, 0);

	mlx_loop_hook(data.mlx, ft_hook, &data);
	mlx_mouse_hook(data.mlx, rt_select, &data);
	mlx_loop(data.mlx);
	clean_up(&data);
	return (0);
}
