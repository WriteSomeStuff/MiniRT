/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 17:46:38 by cschabra      #+#    #+#                 */
/*   Updated: 2024/03/19 18:17:19 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#define RADIUS 16

uint32_t	ft_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	lights_out(t_data *data)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(data->image, x, y, ft_pixel(0, 0, 0, 0xFF));
			x++;
		}
		y++;
	}
}

void	draw_something(t_data *data)
{
	float	x;
	float	y;
	float	dot;
	float	amb;
	t_ray	ray;
	t_hit	col;
	t_vec	surface_norm;
	t_vec	light_dir;
	t_vec	light;
	t_colour	light_colour;
	light_colour.rgba = data->light[0].colour;
	t_colour	sphere;
	sphere.rgba = data->spheres[0].colour;
	t_colour	ambiance;
	ambiance.rgba = data->ambient->colour;
	t_colour	combo;
	combo.rgba = combine_colours(light_colour, ambiance);
	
	light.x = 25000;
	light.y = 4;
	light.z = 0;

	puts("LIGHT");
	print_colour(light_colour);
	puts("combo");
	print_colour(combo);
	puts("SPHERE");
	print_colour(sphere);
	amb = data->ambient->luminosity;
	ray.origin.vec3 = data->cam->viewpoint.vec3;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray.direction = direction_to_xy(data, x, y);
			col = intersect_sphere(&ray, &data->spheres[0]);
			if (col.inside_object == true)
			{
				ft_putendl_fd("Warning: camera is inside an object", STDERR_FILENO);
				lights_out(data);
				return ;
			}
			if (col.hit == true)
			{
				surface_norm.vec3 = col.location.vec3 - data->spheres->center.vec3;
				surface_norm = normalize_vector(&surface_norm);
				light_dir.vec3 = light.vec3 - col.location.vec3;
				light_dir = normalize_vector(&light_dir);
				dot = dot_product(&light_dir, &surface_norm);
				if (dot < 0)
				{
					// mlx_put_pixel(data->image, x, y, ft_pixel(sphere[0] * amb * (ambiance[0] / 255), sphere[1] * amb * (ambiance[1] / 255), sphere[2] * amb * (ambiance[2] / 255), 255));
					mlx_put_pixel(data->image, x, y, reflection_result(sphere, ambiance, 1));
				}
				else
				{
					dot += amb * (1 - dot);
					mlx_put_pixel(data->image, x, y, reflection_result(sphere, combo, dot));
				}
			}
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
