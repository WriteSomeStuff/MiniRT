/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 17:46:38 by cschabra      #+#    #+#                 */
/*   Updated: 2024/03/24 17:53:04 by vincent       ########   odam.nl         */
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
	w->aspect_ratio = (float)data->mlx->width / data->mlx->height;
	data->window = w;
}

static void	parse_single_rgb(t_data *data, t_vec *res, char *rgb)
{
	char	**split;

	split = ft_split(rgb, ',');
	res->r = a_to_float(data, split[0]);
	res->g = a_to_float(data, split[1]);
	res->b = a_to_float(data, split[2]);
	rgb_to_floats(res);
	free_2d((void ***)&split);
}

t_texture	parse_textures(t_data *data, char *location)
{
	char		*line;
	t_texture	tex;
	
	data->fd = open(location, O_RDONLY);
	line = get_next_line_rt(data, data->fd);
	tex.width = ft_atoi(line);
	free(line);
	line = get_next_line_rt(data, data->fd);
	tex.height = ft_atoi(line);
	free(line);
	tex.px = rt_calloc(data, (tex.height + 1) * sizeof(t_vec *));
	for (uint32_t i = 0; i < tex.height; i++)
	{
		tex.px[i] = rt_malloc(data, tex.width * sizeof(t_vec));
	}
	for (uint32_t j = 0; j < tex.height; j++)
	{
		line = get_next_line_rt(data, data->fd);
		if (line == NULL)
			break ;
		char **split = ft_split(line, ' ');
		for (uint32_t i = 0; i < tex.width; i++)
		{
			parse_single_rgb(data, &tex.px[j][i], split[i]);
		}
		free_2d((void ***)&split);
	}
	close(data->fd);
	return (tex);
}

int32_t	main(int32_t argc, char **argv)
{
	t_data		data;
	// uint8_t		pixel[3];

	if (argc != 2)
	{
		ft_putendl_fd("Error: incorrect argument count", STDERR_FILENO);
		return (1);
	}
	ft_bzero(&data, sizeof(t_data));
	// data.textures = rt_calloc(&data, 2 * sizeof(t_texture));
	data.textures = rt_calloc(&data, sizeof(t_texture));
	data.textures[0] = parse_textures(&data, "scenes/earth.txt");
	// data.textures[1] = parse_textures(&data, "scenes/night_earth.txt");
	initialise_window(&data);
	read_file(&data, argv[1]);
	// for (uint32_t j = 0; j < data.textures->height; j++)
	// {
	// 	for (uint32_t i = 0; i < data.textures->width; i++)
	// 	{
	// 		pixel[0] = (uint8_t)(data.textures->px[j][i].r * 255);
	// 		pixel[1] = (uint8_t)(data.textures->px[j][i].g * 255);
	// 		pixel[2] = (uint8_t)(data.textures->px[j][i].b * 255);
	// 		mlx_put_pixel(data.image, i, j, ft_pixel(pixel[0], pixel[1], pixel[2], 0xff));
	// 	}
	// }
	draw_something(&data);

	mlx_loop_hook(data.mlx, ft_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}
