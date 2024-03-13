/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 17:46:38 by cschabra      #+#    #+#                 */
/*   Updated: 2024/03/13 18:46:56 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#define RADIUS 16

uint32_t	ft_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
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
				mlx_put_pixel(data->image, x, y, ft_pixel(100, 0, 255, 255));
			else
				mlx_put_pixel(data->image, x, y, ft_pixel(0, 0, 0, 0xFF));
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

void	initialise_window(t_data *data)
{
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
}

/* int32_t	main(int32_t argc, char **argv)
{

	mlx_loop_hook(data.mlx, ft_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
} */

int32_t	main(int32_t argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_putendl_fd("Error: incorrect argument count", STDERR_FILENO);
		return (1);
	}
	ft_bzero(&data, sizeof(t_data));
	// initialise_window(&data);
	read_file(&data, argv[1]);
	t_ray ray;

	ray.origin = data.cam->viewpoint;
	ray.direction.x = 0;
	ray.direction.y = 0;
	ray.direction.z = 1;
	ray.direction = normalize_vector(&ray.origin, &ray.direction);
	t_hit hit = intersect_sphere(&ray, data.spheres);
	if (hit.hit == true)
	{
		printf("hit at distance: %lf, location: ", hit.distance);
		print_vector(hit.location);
	}
	else
		puts("NO HIT");
	// clean_up(&data);
	return (0);
}
