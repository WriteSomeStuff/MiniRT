/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collisions.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 16:50:47 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/04/11 16:52:12 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	checkerboard_tex(t_sphere *sphere, t_vec *loc);

static uint32_t	pixel_colour(t_data *data, t_vec *clr, float product)
{
	t_vec	amb;

	amb = reflection_result(clr, &data->ambient->colour, 1);
	if (product < 0)
	{
		return (percentage_to_rgba(&amb));
	}
	else
	{
		*clr = reflection_result(clr, &data->light->colour, product);
		*clr = combine_colours(&amb, clr);
		percentage_to_rgba(clr);
		return (percentage_to_rgba(clr));
	}
}

static void	cylinder(t_data *data, t_hit *col, uint32_t x, uint32_t y)
{
	t_cylinder	*cyl;
	t_vec		light_dir;
	t_vec		clr;
	float		product;
	t_vec		to_center;
	t_vec		to_new;

	cyl = (t_cylinder *)col->obj;
	to_center.vec3 = col->location.vec3 - cyl->center.vec3;
	product = dot(&to_center, &cyl->orientation);
	// if (fabs(product) > fabs(vector_length(&cyl->center, &cyl->base)))
	// {
	// 	mlx_put_pixel(data->image, x, y, 0x000000ff);
	// 	return ;
	// }
	to_new.vec3 = cyl->center.vec3 + product * cyl->orientation.vec3;
	set_vector(&col->surface_norm, &to_new, &col->location);
	set_vector(&light_dir, &col->location, &data->light->source);
	product = dot(&light_dir, &col->surface_norm);
	clr = cylinder_texture(cyl, &col->location);
	mlx_put_pixel(data->image, x, y, pixel_colour(data, &clr, product));
	data->map[y][x] = cyl->instance;
}

// Function to rotate a normalized vector by 90 degrees
t_vec rotate_90_degrees(t_vec v)
{
    t_vec result;
	float rotation_matrix[3][3] = {{0, -1, 0},
                                   {1,  0, 0},
                                   {0,  0, 1}};

    result.x = rotation_matrix[0][0] * v.x + rotation_matrix[0][1] * v.y + rotation_matrix[0][2] * v.z;
    result.y = rotation_matrix[1][0] * v.x + rotation_matrix[1][1] * v.y + rotation_matrix[1][2] * v.z;
    result.z = rotation_matrix[2][0] * v.x + rotation_matrix[2][1] * v.y + rotation_matrix[2][2] * v.z;

    return result;
}

static void	plane(t_data *data, t_hit *col, uint32_t x, uint32_t y)
{
	float	product;
	t_plane	*plane;
	t_vec	light_dir;
	t_vec	clr;
	t_vec	dummy;

	dummy.x = 0;
	dummy.y = 0;
	dummy.z = 0;

	plane = (t_plane *)col->obj;
	t_vec	ray_dir;
	ray_dir.vec3 = col->location.vec3 - data->cam->viewpoint.vec3;
	ray_dir = normalize_vector(&ray_dir);
	// t_vec	plane2;

	col->surface_norm = rotate_90_degrees(plane->orientation);
	if (dot(&ray_dir, &plane->orientation) > 0)
		col->surface_norm.vec3 *= -1;
	// set_vector(&plane2, &plane->location, &col->location);
	// col->surface_norm = cross_product(&plane2, &plane->orientation);
	// print_vector(col->surface_norm);
	// else
	// 	col->surface_norm = cross_product(&plane->location, &col->location);
	set_vector(&light_dir, &col->location, &data->light->source);
	product = dot(&light_dir, &col->surface_norm);
	// printf("dot: %f\n", product);
	clr = plane_texture(plane, &col->surface_norm);
	mlx_put_pixel(data->image, x, y, pixel_colour(data, &clr, product));
	data->map[y][x] = plane->instance;
}

static void	sphere(t_data *data, t_hit *col, uint32_t x, uint32_t y)
{
	float	product;
	t_sphere	*sphere;
	t_vec	light_dir;
	t_vec	clr;
	
	sphere = (t_sphere *)col->obj;
	set_vector(&col->surface_norm, &sphere->center, &col->location);
	set_vector(&light_dir, &col->location, &data->light->source);
	product = dot(&light_dir, &col->surface_norm);
	// if (checkerboard_tex(sphere, &col->location) == true)
	// 	mlx_put_pixel(data->image, x, y, 0xffffffff);
	// else
	// 	mlx_put_pixel(data->image, x, y, 0x0);
	// return ;
	clr = sphere_texture(sphere, &col->surface_norm);
	mlx_put_pixel(data->image, x, y, pixel_colour(data, &clr, product));
	data->map[y][x] = sphere->instance;
}

void	draw_collision(t_data *data, t_hit *col, uint32_t x, uint32_t y)
{
	static void	(*ptr[3])(t_data *, t_hit *, uint32_t, uint32_t) = \
		{&cylinder, &plane, &sphere};

	ptr[col->type](data, col, x, y);
}
