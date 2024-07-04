/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 17:46:38 by cschabra      #+#    #+#                 */
/*   Updated: 2024/07/04 15:38:53 by vincent       ########   odam.nl         */
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
	data->scene = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (data->scene == NULL)
	{
		exit_error(data, ": image failed to load");
	}
	data->highlight = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (data->highlight == NULL)
	{
		exit_error(data, ": image failed to load");
	}
	if (mlx_image_to_window(data->mlx, data->scene, 0, 0) == -1)
	{
		exit_error(data, ": failed to load window");
	}
	w->width = data->mlx->width;
	w->height = data->mlx->height;
	w->aspect_ratio = (float)data->mlx->height / data->mlx->width;
	w->sizechanged = true;
	data->window = w;
}

int32_t	main(int32_t argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_putendl_fd("Error: incorrect argument count", STDERR_FILENO);
		return (1);
	}
	ft_bzero(&data, sizeof(t_data));
	initialise_window(&data);
	read_file(&data, argv[1]);
	normalize_scene(&data);
	cast_rays(&data);
	draw(&data);

	mlx_close_hook(data.mlx, &rt_close, &data);
	mlx_key_hook(data.mlx, &rt_keys, &data);
	mlx_mouse_hook(data.mlx, &rt_select, &data);
	mlx_loop_hook(data.mlx, &rt_resize, &data);
	mlx_scroll_hook(data.mlx, &rt_scroll, &data);
	mlx_loop(data.mlx);
	clean_up(&data);
	return (0);
}
