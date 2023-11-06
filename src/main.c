/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 17:46:38 by cschabra      #+#    #+#                 */
/*   Updated: 2023/11/06 18:47:07 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#define WIDTH 512
#define HEIGHT 512
#define RADIUS 16

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_something(t_data *data)
{
	double	x;
	double	y;
	double	d;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			d = sqrt(pow(x - (WIDTH / 2 - 1), 2) + pow(y - (HEIGHT / 2 - 1), 2));
			if (d <= pow(RADIUS, 2))
				mlx_put_pixel(data->image, x, y, (uint32_t)ft_pixel(100, 0, 255, 255));
			else
				mlx_put_pixel(data->image, x, y, (uint32_t)ft_pixel(0, 0, 0, 0xFF));
			y++;
		}
		x++;
	}
}

void	ft_hook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
		data->image->instances[0].y -= 5;
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		data->image->instances[0].y += 5;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->image->instances[0].x -= 5;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->image->instances[0].x += 5;
}

void	initialize_data(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (data->mlx == NULL)
	{
		printf("%s\n", mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (data->image == NULL)
	{
		// clean_up(data, msg?);
		mlx_close_window(data->mlx);
		printf("%s\n", mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
	{
		// clean_up(data, msg?);
		mlx_close_window(data->mlx);
		printf("%s\n", mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
}

int32_t	main(int32_t argc, char **argv)
{
	t_data	data;

	(void) argc;
	(void) argv;
	initialize_data(&data);
	draw_something(&data);
	mlx_loop_hook(data.mlx, ft_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
