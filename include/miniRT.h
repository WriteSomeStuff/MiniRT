/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 17:47:28 by cschabra      #+#    #+#                 */
/*   Updated: 2024/02/28 17:50:03 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "get_next_line_rt.h"
# include <MLX42/MLX42.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>

# define WIDTH 512
# define HEIGHT 512
# define PI 3.14159265359
# define FOREVER 1

typedef enum s_token
{
	AMBIENT,
	CAMERA,
	CYLINDER,
	LIGHT,
	PLANE,
	SPHERE,
	INVALID
}	t_token;
typedef struct s_input
{
	char			**info;
	t_token			token;
	struct s_input	*next;
}	t_input;

typedef union s_vec
{
	double	v[3];

	struct
	{
		double	x;
		double	y;
		double	z;
	};
}	t_vec;

typedef struct s_sphere
{
	t_vec		center;
	uint32_t	radius;
	uint32_t	colour;
}	t_sphere;

typedef struct s_cylinder
{
	t_vec		center;
	uint32_t	radius;
	uint32_t	height;
	uint32_t	colour;
}	t_cylinder;

typedef struct s_light
{
	t_vec		source;
	double		luminosity;
	uint32_t	colour;
}	t_light;

typedef struct s_plane
{
	t_vec		location;
	t_vec		orientation;
	uint32_t	colour;
}	t_plane;

typedef struct s_camera
{
	t_vec		viewpoint;
	t_vec		orientation;
	uint32_t	fov;
}	t_camera;

typedef struct s_data
{
	mlx_image_t	*image;
	mlx_t		*mlx;
	t_input		*input;
	int32_t		fd;
	void		(*f[6])(t_data *, char **);
}	t_data;

uint32_t	ft_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
// void		draw_line(t_data *data, t_complex start, t_complex end);

/*	Initialisation	*/

void		init_ambient(t_data *data);
void		init_camera(t_data *data);
void		init_cylinder(t_data *data);
void		init_light(t_data *data);
void		init_plane(t_data *data);
void		init_sphere(t_data *data);

/*	Errors & cleanup	*/

void		clean_up(t_data *data);
void		clear_list(t_input **input);
void		exit_error(t_data *data, char *msg);

/*	Initialisation	*/

void		read_file(t_data *data, char *location);

/*	Utilities	*/

void		*rt_malloc(t_data *data, size_t size);
void		*rt_calloc(t_data *data, size_t size);

void		check_split(t_data *data, char **info, int32_t num);
bool		is_white_space(char c);
void		verify_info(t_data *data, char **info);

#endif

// void	draw_rectangle(t_data *data, uint32_t wide, uint32_t high, \
//	t_complex center);
// void	draw_cube(t_data *data, t_complex center);
// void	draw_background(t_data *data);

// typedef union s_quat
// {
// 	double	q[4];
// 	struct
// 	{
// 		double	real;
// 		double	x;
// 		double	y;
// 		double	z;
// 	};
// }	t_quat;

// typedef struct s_complex
// {
// 	int32_t	x;
// 	int32_t	y;
// }	t_complex;

/* typedef struct s_window
{
	uint32_t	width;
	uint32_t	height;
}	t_window; */
