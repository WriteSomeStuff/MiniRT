/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 17:46:38 by cschabra      #+#    #+#                 */
/*   Updated: 2024/08/19 17:12:08 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	initialise_window(t_data *data)
{
	t_window	*w;

	w = rt_calloc(data, sizeof(t_window));
	data->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", false);
	if (data->mlx == NULL)
		exit_error(data, ": mlx failed to initialise");
	data->scene = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (data->scene == NULL)
		exit_error(data, ": image failed to load");
	if (mlx_image_to_window(data->mlx, data->scene, 0, 0) == -1)
		exit_error(data, ": failed to load window");
	w->width = data->mlx->width;
	w->height = data->mlx->height;
	w->aspect_ratio = (float)data->mlx->height / data->mlx->width;
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
	mlx_scroll_hook(data.mlx, &rt_scroll, &data);
	mlx_loop(data.mlx);
}
