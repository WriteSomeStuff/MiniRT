/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 17:46:38 by cschabra      #+#    #+#                 */
/*   Updated: 2024/03/15 17:35:01 by vvan-der      ########   odam.nl         */
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
	float	x;
	float	y;
	t_ray	ray;
	t_hit	col;
	// t_hit	col2;

	ray.origin = data->cam->viewpoint;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray.direction = direction_to_xy(data, x, y);
			col = intersect_sphere(&ray, data->spheres);
			if (col.hit == true)
				mlx_put_pixel(data->image, x, y, ft_pixel(100, 0, 255, 255));
			else
				mlx_put_pixel(data->image, x, y, ft_pixel(0, 0, 0, 0xFF));
			x++;
		}
		y++;
	}
}

void	ft_hook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	// if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
	// 	data->image->instances[0].y -= 5;
	// if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
	// 	data->image->instances[0].y += 5;
	// if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	// 	data->image->instances[0].x -= 5;
	// if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	// 	data->image->instances[0].x += 5;
}

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
	w->x = data->mlx->width;
	w->y = data->mlx->height;
	w->aspect_ratio = (float)data->mlx->width / data->mlx->height;
	data->window = w;
}

/* int32_t	main(int32_t argc, char **argv)
{

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
	(void)argv;
	ft_bzero(&data, sizeof(t_data));
	initialise_window(&data);
	read_file(&data, argv[1]);
	draw_something(&data);

	mlx_loop_hook(data.mlx, ft_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}

/* int32_t	main(int32_t argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_putendl_fd("Error: incorrect argument count", STDERR_FILENO);
		return (1);
	}
	(void)argc;
	(void)argv;
	ft_bzero(&data, sizeof(t_data));
	// initialise_window(&data);
	// read_file(&data, argv[1]);
	// t_ray ray;
	t_vec t;
 	for (int x = 0; x < 500; x++)
	{
		for (int y = 0; y < 500; y++)
		{
			for (int z = 0; z < 500; z++)
			{
				ray.direction.x = x;
				ray.direction.y = y;
				ray.direction.z = z;
				ray.direction = normalize_vector(&ray.direction);
			}
		}
	}
	for (int x = 0; x < 500; x++)
	{
		for (int y = 0; y < 500; y++)
		{
			for (int z = 0; z < 500; z++)
			{
				float inv_sqrt = (float)q_sqrt((float)x * x + y * y + z * z);
				t.x *= x * inv_sqrt;
				t.y *= y * inv_sqrt;
				t.z *= z * inv_sqrt;
			}
		}
	}
	// puts("Ordinary method");
	// print_vector(ray.direction);
	// puts("Quake magic");
	// print_vector(t);
	// t_hit hit = intersect_sphere(&ray, data.spheres);
	// if (hit.hit == true)
	// {
	// 	printf("hit at distance: %lf, location: ", hit.distance);
	// 	print_vector(hit.location);
	// }
	// else
	// 	puts("NO HIT");
	// clean_up(&data);
	return (0);
} */
